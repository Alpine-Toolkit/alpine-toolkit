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
#include "alpine_toolkit.h"

#include <QDebug>
#include <QMutexLocker>
#include <QtCore/QTimerEvent>

/**************************************************************************************************/

QaNetworkRequestManager::QaNetworkRequestManager()
  : QObject(),
    m_network_manager(this),
    m_user_agent(""),
    m_enabled(true)
{
  connect(&m_network_manager, &QNetworkAccessManager::authenticationRequired,
	  this, &QaNetworkRequestManager::on_authentication_request_slot);

  // Signal when a reply has finished
  // connect(m_network_manager, SIGNAL(finished(QNetworkReply*)),
  // 	  this, SLOT(replyFinished(QNetworkReply*)));
}

QaNetworkRequestManager::~QaNetworkRequestManager()
{}

void
QaNetworkRequestManager::set_user_agent(const QByteArray & user_agent)
{
  m_user_agent = user_agent;
}

void
QaNetworkRequestManager::on_authentication_request_slot(QNetworkReply * reply,
                                                        QAuthenticator * authenticator)
{
  // Fixme: this code do nothing
  Q_UNUSED(reply);
  qATInfo() << "on_authentication_request_slot";
  authenticator->setUser("");
  authenticator->setPassword("");
}

void
QaNetworkRequestManager::add_request(const QaNetworkRequestPtr & request)
{
  QMutexLocker mutex_locker(&m_queue_mutex);

  // add to a list
  m_queue += request;

  // Start timer to fetch ressource from queue
  if (m_enabled and not m_queue.isEmpty() and not m_timer.isActive())
    m_timer.start(0, this);
}

void
QaNetworkRequestManager::cancel_request(const QaNetworkRequestPtr & request)
{
  QMutexLocker mutex_locker(&m_queue_mutex);

  QaNetworkReply * reply = m_invmap.value(request, nullptr);
  if (reply) { // else url wasn't requested
    m_invmap.remove(request);
    reply->abort();
    if (reply->is_finished())
      reply->deleteLater(); // else done in handle_reply
  }
  m_queue.removeAll(request);
}

void
QaNetworkRequestManager::timerEvent(QTimerEvent * event)
{
  qATInfo() << "QaNetworkRequestManager::timerEvent";
  if (event->timerId() != m_timer.timerId()) // Fixme: when ???
    QObject::timerEvent(event);
  else if (m_queue.isEmpty())
    m_timer.stop();
  else
    get_next_request();
}

void
QaNetworkRequestManager::get_next_request()
{
  QMutexLocker mutex_locker(&m_queue_mutex);

  if (not m_enabled or m_queue.isEmpty())
    return;

  QaNetworkRequestPtr request = m_queue.takeFirst();

  qATInfo() << "QaNetworkRequestManager::get_next_request" << request->url();
  QaNetworkReply *reply = make_reply(request);

  // If the request is already finished then handle it
  // Else connect the finished signal
  if (reply->is_finished()) {
    handle_reply(reply);
  } else {
    connect(reply, &QaNetworkReply::finished,
            this, &QaNetworkRequestManager::on_reply_finished,
            Qt::QueuedConnection);
    m_invmap.insert(request, reply);
  }

  if (m_queue.isEmpty())
    m_timer.stop();
}

QNetworkRequest
QaNetworkRequestManager::make_request(const QaNetworkRequestPtr & request) const
{
  QNetworkRequest network_request = request->network_request();
  network_request.setRawHeader("User-Agent", m_user_agent);

  // custom network_request.setRawHeader(...) for authorization etc.
  // network_request.setPriority();

  return network_request;
}

QaNetworkReply *
QaNetworkRequestManager::make_reply(const QaNetworkRequestPtr & request)
{
  // Create request
  QNetworkRequest network_request = make_request(request);

  // Send request to network manager
  QNetworkReply * network_reply = nullptr;
  QaNetworkRequest::RequestType request_type = request->type();
  if (request_type == QaNetworkRequest::RequestType::Get) {
    qATInfo() << "QaNetworkRequestPtr::make_reply GET" << request->url();
    network_reply = m_network_manager.get(network_request);
  } else if (request_type == QaNetworkRequest::RequestType::Post) {
    auto post_request = request.dynamicCast<QaPostNetworkRequest>();
    qATInfo() << "QaNetworkRequestPtr::make_reply POST" << request->url() << "\n" << post_request->data();
    network_reply = m_network_manager.post(network_request, post_request->data());
  }
  // put(const QNetworkRequest &request, const QByteArray &data)
  // deleteResource(const QNetworkRequest &request)

  // Fixme: when ???
  if (network_reply->error() != QNetworkReply::NoError)
    qWarning() << __FUNCTION__ << network_reply->errorString();

  // Fixme: ???
  // network_reply.setOriginatingObject(&request); // request must be an unique instance : a pointer !

  return new QaNetworkReply(request, network_reply); // Fixme: deleted by deleteLater, smart ???
}

void
QaNetworkRequestManager::on_reply_finished()
{
  QMutexLocker mutex_locker(&m_queue_mutex);

  QaNetworkReply * reply = qobject_cast<QaNetworkReply *>(sender());
  if (not reply) { // Fixme: when ???
    qWarning() << "QaNetworkRequestManager::reply_finished reply is null";
    return;
  }

  const QaNetworkRequestPtr & request = reply->request();
  qATInfo() << "QaNetworkRequestManager::on_reply_finished" << request->url();
  if (m_invmap.contains(request)) { // else cancelled request
    m_invmap.remove(request);
   handle_reply(reply);
  } else {
    qWarning() << "QaNetworkRequestManager::reply_finished m_invmap doesn't have url";
    reply->deleteLater(); // Fixme: cancelled ???
  }
}

void
QaNetworkRequestManager::handle_reply(QaNetworkReply * reply)
{
  // Could retry the request

  reply->deleteLater();
}
