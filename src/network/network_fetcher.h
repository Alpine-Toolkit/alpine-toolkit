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
#include <QMutexLocker>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QSize>
#include <QTimer>

#include "network_reply.h"

/**************************************************************************************************/

class NetworkFetcher : public QObject
{
  Q_OBJECT

public:
  NetworkFetcher();
  ~NetworkFetcher();

  void set_user_agent(const QByteArray & user_agent);
  // void set_connection_identifier();

public slots:
  void add_request(const QUrl & url);
  void cancel_request(const QUrl & url);

signals:
  void request_finished(const QUrl & url); // & ???
  void request_error(const QUrl &, const QString & errorString);

protected:
  void timerEvent(QTimerEvent * event);

private:
  NetworkReply * get(const QUrl & url);
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
  QList<QUrl> m_queue;
  QHash<QUrl, NetworkReply *> m_invmap;
};

/**************************************************************************************************/

#endif /* __NETWORK_FETCHER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
