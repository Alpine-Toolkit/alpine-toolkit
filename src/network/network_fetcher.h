// -*- mode: c++ -*-

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

#ifndef __NETWORK_FETCHER_H__
#define __NETWORK_FETCHER_H__

/**************************************************************************************************/

#include <QAuthenticator>
#include <QHash>
#include <QList>
#include <QMap>
#include <QMutex>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QTimer>

#include "network_ressource_request.h"
#include "network_reply.h"

/**************************************************************************************************/

// Fixme: check code against qtcarto

/* The NetworkFetcher class manages a list of asynchronous requests.
 *
 * Note: QNetworkAccessManager queues the requests it receives. The
 * number of requests executed in parallel is dependent on the
 * protocol. Currently, for the HTTP protocol on desktop platforms, 6
 * requests are executed in parallel for one host/port combination.
 */
class NetworkFetcher : public QObject
{
  Q_OBJECT

public:
  NetworkFetcher();
  ~NetworkFetcher();

  void set_user_agent(const QByteArray & user_agent);
  // void set_connection_identifier();

public slots:
  void add_request(const NetworkRessourceRequest & request);
  void cancel_request(const NetworkRessourceRequest & request);

signals:
  void download_progress(const NetworkRessourceRequest & request, qint64 percent);
  void request_finished(const NetworkRessourceRequest & request, const QByteArray & payload); // & ???
  void request_error(const NetworkRessourceRequest & request, const QString & error_string);

protected:
  void timerEvent(QTimerEvent * event);

private:
  NetworkReply * get(const NetworkRessourceRequest & request);
  void handle_reply(NetworkReply * reply);

private slots:
  void get_next_request();
  void reply_finished();
  void on_authentication_request_slot(QNetworkReply * reply, QAuthenticator * authenticator);

private:
  QNetworkAccessManager * m_network_manager;
  QByteArray m_user_agent;
  bool m_enabled;
  QBasicTimer m_timer;
  QMutex m_queue_mutex;
  QList<NetworkRessourceRequest> m_queue;
  QHash<NetworkRessourceRequest, NetworkReply *> m_invmap;
};

/**************************************************************************************************/

#endif /* __NETWORK_FETCHER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
