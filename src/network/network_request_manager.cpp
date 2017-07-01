/***************************************************************************************************
 **
 ** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 **
 ** Copyright (C) 2017 Fabrice Salvaire
 ** Contact: http://www.fabrice-salvaire.fr
 **
 ** This file is part of the QtCarto library.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 ** $ALPINE_TOOLKIT_END_LICENSE$
 **
 ***************************************************************************************************/

/**************************************************************************************************/

#include "network_request_manager.h"

#include <QDebug>
#include <QMutexLocker>
#include <QtCore/QTimerEvent>

/**************************************************************************************************/

QcNetworkRequestManager::QcNetworkRequestManager()
  : QObject(),
    m_network_manager(this),
    m_user_agent(""),
    m_enabled(true)
{
  connect(&m_network_manager, &QNetworkAccessManager::authenticationRequired,
	  this, &QcNetworkRequestManager::on_authentication_request_slot);

  // signal when a reply has finished
  // connect(m_network_manager, SIGNAL(finished(QNetworkReply*)),
  // 	  this, SLOT(replyFinished(QNetworkReply*)));
}

QcNetworkRequestManager::~QcNetworkRequestManager()
{}

void
QcNetworkRequestManager::set_user_agent(const QByteArray & user_agent)
{
  m_user_agent = user_agent;
}

void
QcNetworkRequestManager::on_authentication_request_slot(QNetworkReply * reply,
                                                        QAuthenticator * authenticator)
{
  // Fixme: this code do nothing
  Q_UNUSED(reply);
  qInfo() << "on_authentication_request_slot";
  authenticator->setUser("");
  authenticator->setPassword("");
}

void
QcNetworkRequestManager::add_request(const QcNetworkRequestPtr & request)
{
  QMutexLocker mutex_locker(&m_queue_mutex);

  // add to a list
  m_queue += request;

  // Start timer to fetch ressource from queue
  if (m_enabled and not m_queue.isEmpty() and not m_timer.isActive())
    m_timer.start(0, this);
}

void
QcNetworkRequestManager::cancel_request(const QcNetworkRequestPtr & request)
{
  QMutexLocker mutex_locker(&m_queue_mutex);

  QcNetworkReply * reply = m_invmap.value(request, nullptr);
  if (reply) { // else url wasn't requested
    m_invmap.remove(request);
    reply->abort();
    if (reply->is_finished())
      reply->deleteLater(); // else done in handle_reply
  }
  m_queue.removeAll(request);
}

void
QcNetworkRequestManager::timerEvent(QTimerEvent * event)
{
  qInfo() << "QcNetworkRequestManager::timerEvent";
  if (event->timerId() != m_timer.timerId()) // Fixme: when ???
    QObject::timerEvent(event);
  else if (m_queue.isEmpty())
    m_timer.stop();
  else
    get_next_request();
}

void
QcNetworkRequestManager::get_next_request()
{
  QMutexLocker mutex_locker(&m_queue_mutex);

  if (not m_enabled or m_queue.isEmpty())
    return;

  QcNetworkRequestPtr request = m_queue.takeFirst();

  qInfo() << "QcNetworkRequestManager::get_next_request" << request->url();
  QcNetworkReply *reply = make_reply(request);

  // If the request is already finished then handle it
  // Else connect the finished signal
  if (reply->is_finished()) {
    handle_reply(reply);
  } else {
    connect(reply, &QcNetworkReply::finished,
            this, &QcNetworkRequestManager::on_reply_finished,
            Qt::QueuedConnection);
    // connect(reply, &QcNetworkReply::download_progress, this, &QcNetworkRequestManager::download_progress);
    m_invmap.insert(request, reply);
  }

  if (m_queue.isEmpty())
    m_timer.stop();
}

QcNetworkReply *
QcNetworkRequestManager::make_reply(const QcNetworkRequestPtr & request)
{
  qInfo() << "make_reply" << request->url();

  // Create request
  QNetworkRequest network_request = request->network_request();
  network_request.setRawHeader("User-Agent", m_user_agent);
  // network_request.setPriority();

  // Send request to network manager
  QNetworkReply * network_reply = nullptr;
  QcNetworkRequest::RequestType request_type = request->type();
  if (request_type == QcNetworkRequest::RequestType::Get)
    network_reply = m_network_manager.get(network_request);
  else if (request_type == QcNetworkRequest::RequestType::Post) {
    QcPostNetworkRequest * post_request = dynamic_cast<QcPostNetworkRequest *>(request.data());
    network_reply = m_network_manager.post(network_request, post_request->data());
  }
  // put(const QNetworkRequest &request, const QByteArray &data)
  // deleteResource(const QNetworkRequest &request)

  // Fixme: when ???
  if (network_reply->error() != QNetworkReply::NoError)
    qWarning() << __FUNCTION__ << network_reply->errorString();

  // Fixme: ???
  // network_reply.setOriginatingObject(&request); // request must be an unique instance : a pointer !

  return new QcNetworkReply(request, network_reply); // Fixme: smart ?
}

void
QcNetworkRequestManager::on_reply_finished()
{
  QMutexLocker mutex_locker(&m_queue_mutex);

  QcNetworkReply * reply = qobject_cast<QcNetworkReply *>(sender());
  if (not reply) { // Fixme: when ???
    qWarning() << "QcNetworkRequestManager::reply_finished reply is null";
    return;
  }

  const QcNetworkRequestPtr & request = reply->request();
  qInfo() << "QcNetworkRequestManager::on_reply_finished" << request->url();
  if (m_invmap.contains(request)) { // cancelled request
    m_invmap.remove(request);
    handle_reply(reply);
  } else {
    qWarning() << "QcNetworkRequestManager::reply_finished m_invmap doesn't have url";
    reply->deleteLater(); // Fixme: cancelled ???
  }
}

void
QcNetworkRequestManager::handle_reply(QcNetworkReply * reply)
{
  const QcNetworkRequestPtr & request = reply->request();
  qInfo() << "QcNetworkRequestManager::handle_reply" << request->url();

  if (m_enabled) {
    // emit signal according to the reply status
    if (reply->error() == QcNetworkReply::NoError) {
      qInfo() << "QcNetworkRequestManager::handle_reply emit tile_finished";
      emit request_finished(request, reply->payload());
    } else {
      qInfo() << "QcNetworkRequestManager::handle_reply emit tile_error" << reply->error_string();
      emit request_error(request, reply->error_string());
    }
  }

  reply->deleteLater();
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
