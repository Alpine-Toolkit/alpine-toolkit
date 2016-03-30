/***************************************************************************************************
 **
 ** $QTCARTO_BEGIN_LICENSE:GPL3$
 **
 ** Copyright (C) 2016 Fabrice Salvaire
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
 ** $QTCARTO_END_LICENSE$
 **
 ***************************************************************************************************/

/**************************************************************************************************/

#include "network_fetcher.h"
#include "network_reply.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QtCore/QTimerEvent>

/**************************************************************************************************/

NetworkFetcher::NetworkFetcher()
  : QObject(),
    m_network_manager(new QNetworkAccessManager(this)),
    m_user_agent(""),
    m_enabled(true)
{
  connect(m_network_manager,
	  SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),
	  this,
	  SLOT(on_authentication_request_slot(QNetworkReply*, QAuthenticator*)));

  // connect(m_network_manager, SIGNAL(finished(QNetworkReply*)),
  // 	  this, SLOT(replyFinished(QNetworkReply*)));
}

NetworkFetcher::~NetworkFetcher()
{}

void
NetworkFetcher::set_user_agent(const QByteArray & user_agent)
{
  m_user_agent = user_agent;
}

void
NetworkFetcher::on_authentication_request_slot(QNetworkReply * reply,
					       QAuthenticator * authenticator)
{
  qInfo() << "on_authentication_request_slot";
  authenticator->setUser("");
  authenticator->setPassword("");
}

void
NetworkFetcher::add_request(const QUrl & url)
{
  QMutexLocker mutex_locker(&m_queue_mutex);

  m_queue += url;

  // Start timer to fetch tiles from queue
  if (m_enabled && !m_queue.isEmpty() && !m_timer.isActive()) {
    m_timer.start(0, this);
  }
}

void
NetworkFetcher::cancel_request(const QUrl & url)
{
  QMutexLocker mutex_locker(&m_queue_mutex);

  NetworkReply * reply = m_invmap.value(url, nullptr);
  if (reply) { // url wasn't requested
    m_invmap.remove(url);
    reply->abort();
    if (reply->is_finished())
      reply->deleteLater(); // else done in handle_reply
  }
  m_queue.removeAll(url);
}

void
NetworkFetcher::timerEvent(QTimerEvent * event)
{
  qInfo() << "NetworkFetcher::timerEvent";
  if (event->timerId() != m_timer.timerId()) { // Fixme: when ?
    QObject::timerEvent(event);
    return;
  } else if (m_queue.isEmpty()) {
    m_timer.stop();
    return;
  } else
    get_next_request();
}

void
NetworkFetcher::get_next_request()
{
  QMutexLocker mutex_locker(&m_queue_mutex);

  if (!m_enabled || m_queue.isEmpty())
    return;

  QUrl url = m_queue.takeFirst();

  qInfo() << "NetworkFetcher::get_next_request" << url;
  NetworkReply *reply = get(url);

  // If the request is already finished then handle it
  // Else connect the finished signal
  if (reply->is_finished()) {
    handle_reply(reply);
  } else {
    connect(reply, SIGNAL(finished()),
	    this, SLOT(reply_finished()),
	    Qt::QueuedConnection);
    m_invmap.insert(url, reply);
  }

  if (m_queue.isEmpty())
    m_timer.stop();
}

NetworkReply *
NetworkFetcher::get(const QUrl & url)
{
  qInfo() << "Get" << url;

  QNetworkRequest request;
  request.setRawHeader("User-Agent", m_user_agent);
  request.setUrl(url);
  // request.setPriority();

  QNetworkReply * q_network_reply = m_network_manager->get(request);
  if (q_network_reply->error() != QNetworkReply::NoError)
    qWarning() << __FUNCTION__ << q_network_reply->errorString();

  NetworkReply * reply = new NetworkReply(q_network_reply);

  return reply;
}

void
NetworkFetcher::reply_finished()
{
  QMutexLocker mutex_locker(&m_queue_mutex);

  NetworkReply *reply = qobject_cast<NetworkReply *>(sender());
  if (!reply) { // Fixme: when ?
    qWarning() << "NetworkFetcher::reply_finished reply is null";
    return;
  }

  QUrl url = reply->url();
  qInfo() << "NetworkFetcher::finished" << url;
  if (m_invmap.contains(url)) { // cancelled request
    m_invmap.remove(url);
    handle_reply(reply);
  } else {
    qWarning() << "NetworkFetcher::reply_finished m_invmap doesn't have url";
    reply->deleteLater();
  }
}

void
NetworkFetcher::handle_reply(NetworkReply * reply)
{
  QUrl url = reply->url();
  qInfo() << "NetworkFetcher::handle_reply" << url;

  if (m_enabled) {
    // emit signal according to the reply status
    if (reply->error() == NetworkReply::NoError) {
      qInfo() << "NetworkFetcher::handle_reply emit tile_finished";
      emit request_finished(url);
    } else {
      qInfo() << "NetworkFetcher::handle_reply emit tile_error" << reply->error_string();
      emit request_error(url, reply->error_string());
    }
  }

  reply->deleteLater();
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
