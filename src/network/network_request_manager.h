// -*- mode: c++ -*-

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

#ifndef __NETWORK_REQUEST_MANAGER_H__
#define __NETWORK_REQUEST_MANAGER_H__

/**************************************************************************************************/

#include "network/network_request.h"
#include "network/network_reply.h"

#include <QAuthenticator>
#include <QHash>
#include <QList>
#include <QMap>
#include <QMutex>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QTimer>

/**************************************************************************************************/

/* The QaNetworkRequestManager class manages a list of asynchronous requests.
 *
 * Note: QNetworkAccessManager queues the requests it receives. The
 * number of requests executed in parallel is dependent on the
 * protocol. Currently, for the HTTP protocol on desktop platforms, 6
 * requests are executed in parallel for one host/port combination.
 */
class QaNetworkRequestManager : public QObject
{
  Q_OBJECT

public:
  QaNetworkRequestManager();
  ~QaNetworkRequestManager();

  void set_user_agent(const QByteArray & user_agent);
  // void set_connection_identifier();

  virtual QNetworkRequest make_request(const QaNetworkRequestPtr & request) const;

public slots:
  void add_request(const QaNetworkRequestPtr & request);
  void cancel_request(const QaNetworkRequestPtr & request);

protected:
  void timerEvent(QTimerEvent * event); // Fixme: protected ???

private:
  QaNetworkReply * make_reply(const QaNetworkRequestPtr & request);
  void handle_reply(QaNetworkReply * reply);

private slots:
  void get_next_request();
  void on_reply_finished();
  void on_authentication_request_slot(QNetworkReply * reply, QAuthenticator * authenticator);

private:
  QNetworkAccessManager m_network_manager;
  QByteArray m_user_agent;
  bool m_enabled;
  QBasicTimer m_timer;
  QMutex m_queue_mutex;
  QList<QaNetworkRequestPtr> m_queue;
  QHash<QaNetworkRequestPtr, QaNetworkReply *> m_invmap;
};

/**************************************************************************************************/

#endif /* __NETWORK_REQUEST_MANAGER_H__ */
