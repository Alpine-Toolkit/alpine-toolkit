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

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QDebug>

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

NetworkFetcher::NetworkFetcher()
  : QObject(),
    m_network_manager(new QNetworkAccessManager(this)),
    m_user_agent("")
{
  connect(m_network_manager,
	  SIGNAL(authenticationRequired(QNetworkReply*, QAuthenticator*)),
	  this,
	  SLOT(on_authentication_request_slot(QNetworkReply*, QAuthenticator*)));

  // connect(m_network_manager, SIGNAL(finished(QNetworkReply*)),
  // 	  this, SLOT(replyFinished(QNetworkReply*)));
}

// NetworkFetcher::~NetworkFetcher()
// {}

NetworkReply *
NetworkFetcher::get_url(const QString & url_string)
{
  QUrl url = QUrl(url_string);
  qInfo() << "Get" << url;

  QNetworkRequest request;
  request.setRawHeader("User-Agent", m_user_agent);
  request.setUrl(url);

  QNetworkReply * q_network_reply = m_network_manager->get(request);
  if (q_network_reply->error() != QNetworkReply::NoError)
    qWarning() << __FUNCTION__ << q_network_reply->errorString();

  NetworkReply * reply = new NetworkReply(q_network_reply);

  connect(reply, SIGNAL(finished()),
	  this, SLOT(reply_finished()),
	  Qt::QueuedConnection);

  return reply;
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
NetworkFetcher::reply_finished()
{
  qInfo() << "NetworkFetcher::finished";

  NetworkReply *reply = qobject_cast<NetworkReply *>(sender());
  if (!reply) { // Fixme: when ?
    qWarning() << "reply is null";
    return;
  }

  // emit signal according to the reply status
  if (reply->error() == NetworkReply::NoError) {
    qInfo() << "NetworkFetcher::handle_reply emit tile_finished";
    // emit finished(...);
  } else {
    qInfo() << "NetworkFetcher::handle_reply emit tile_error" << reply->error_string();
    // emit error(..., reply->error_string());
  }

  reply->deleteLater();
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
