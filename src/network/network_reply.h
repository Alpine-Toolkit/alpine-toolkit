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

#ifndef __NETWORK_REPLY_H__
#define __NETWORK_REPLY_H__

/**************************************************************************************************/

#include <QNetworkReply>
#include <QPointer>

/**************************************************************************************************/

class NetworkReply : public QObject
{
  Q_OBJECT

public:
  enum Error { // Fixme: check
    NoError,
    CommunicationError,
    ParseError,
    UnknownError
  };

public:
  explicit NetworkReply(QNetworkReply * reply);
  // NetworkReply(Error error, const QString & error_string);
  ~NetworkReply();

  bool is_finished() const;
  Error error() const;
  QString error_string() const;
  QNetworkReply * network_reply() const;

  void abort();

signals:
  void finished();
  void error(Error error, const QString & error_string = QString());

protected:
  void set_error(Error error, const QString & error_string);
  void set_finished(bool finished);

private:
  Q_DISABLE_COPY(NetworkReply);

private slots:
  void network_reply_finished();
  void network_reply_error(QNetworkReply::NetworkError error);

private:
  Error m_error;
  QString m_error_string;
  bool m_is_finished;
  QPointer<QNetworkReply> m_reply;
};

/**************************************************************************************************/

#endif /* __NETWORK_REPLY_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
