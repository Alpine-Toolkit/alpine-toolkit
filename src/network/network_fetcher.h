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
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "network_reply.h"

/**************************************************************************************************/

class NetworkFetcher : public QObject
{
  Q_OBJECT

public:
  NetworkFetcher();

  void set_user_agent(const QByteArray & user_agent) {
    m_user_agent = user_agent;
  }

  NetworkReply * get_url(const QString & url);

private slots:
  void reply_finished();
  void on_authentication_request_slot(QNetworkReply * reply, QAuthenticator * authenticator);

// signals:
//   void finished();
//   void error(const QString & errorString);

private:
  QNetworkAccessManager * m_network_manager;
  QByteArray m_user_agent;
};

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __NETWORK_FETCHER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
