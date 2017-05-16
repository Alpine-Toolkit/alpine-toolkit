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

#ifndef __NETWORK_REPLY_H__
#define __NETWORK_REPLY_H__

/**************************************************************************************************/

#include <QNetworkReply>
#include <QPointer>

#include "network_ressource_request.h"

/**************************************************************************************************/

/* The NetworkReply class contains a request identifier and a QNetworkReply instance.
 *
 */
class NetworkReply : public QObject
{
  Q_OBJECT

public:
  enum Error { // Fixme: check
    NoError,
    CommunicationError,
    UnknownError
  };

public:
  explicit NetworkReply(const NetworkRessourceRequest & request, QNetworkReply * reply); // Fixme: reply.request()
  // NetworkReply(Error error, const QString & error_string);
  ~NetworkReply();

  NetworkRessourceRequest request() const { return m_request; }
  QNetworkReply * network_reply() const { return m_reply; }

  bool is_finished() const { return m_is_finished; }

  Error error() const { return m_error; };
  QString error_string() const { return m_error_string; };

  const QByteArray & payload() const { return m_payload; };

  void abort();

signals:
  void download_progress(const NetworkRessourceRequest & request, qint64 percent);
  void finished();
  void error(Error error, const QString & error_string = QString());

protected:
  void set_finished(bool finished);
  void set_error(Error error, const QString & error_string);

private:
  Q_DISABLE_COPY(NetworkReply);
  void release();

private slots:
  void _download_progress(qint64 bytes_received, qint64 bytes_total);
  void reply_finished();
  void reply_error(QNetworkReply::NetworkError error);

private:
  NetworkRessourceRequest m_request;
  QPointer<QNetworkReply> m_reply;
  bool m_is_finished;
  Error m_error;
  QString m_error_string;
  QByteArray m_payload;
};

/**************************************************************************************************/

#endif /* __NETWORK_REPLY_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
