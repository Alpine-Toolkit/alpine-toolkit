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

#ifndef __NETWORK_REQUEST_H__
#define __NETWORK_REQUEST_H__

/**************************************************************************************************/

#include <QHash>
#include <QNetworkRequest>
#include <QObject>
#include <QSharedPointer>
#include <QUrl>

/**************************************************************************************************/

/* The QcNetworkRequest class defines a network ressource request.
 *
 */
class QcNetworkRequest : public QObject
{
  Q_OBJECT

public:
  enum class RequestType {
    Get,
    Post,
    Put,
    Delete,
  };

public:
  QcNetworkRequest();
  QcNetworkRequest(const QUrl & url);
  QcNetworkRequest(const QcNetworkRequest & other);
  virtual ~QcNetworkRequest();

  QcNetworkRequest & operator=(const QcNetworkRequest & other);

  QUrl url() const { return m_url; }
  void set_url(const QUrl & url) { m_url = url; }

  bool operator==(const QcNetworkRequest & rhs) const;

  virtual RequestType type() const = 0;

  QNetworkRequest network_request() const;

private:
  QUrl m_url;
};

typedef QSharedPointer<QcNetworkRequest> QcNetworkRequestPtr;

QDebug operator<<(QDebug, const QcNetworkRequest & request);

/**************************************************************************************************/

class QcGetNetworkRequest : public QcNetworkRequest
{
  Q_OBJECT

public:
  QcGetNetworkRequest();
  QcGetNetworkRequest(const QUrl & url);
  QcGetNetworkRequest(const QcGetNetworkRequest & other);
  ~QcGetNetworkRequest();

  QcGetNetworkRequest & operator=(const QcGetNetworkRequest & other);

  bool operator==(const QcGetNetworkRequest & rhs) const;

  RequestType type() const { return RequestType::Get; }
};

QDebug operator<<(QDebug, const QcGetNetworkRequest & request);

/**************************************************************************************************/

class QcPostNetworkRequest : public QcNetworkRequest
{
  Q_OBJECT

public:
  QcPostNetworkRequest();
  QcPostNetworkRequest(const QUrl & url, const QByteArray & data);
  QcPostNetworkRequest(const QcPostNetworkRequest & other);
  ~QcPostNetworkRequest();

  QcPostNetworkRequest & operator=(const QcPostNetworkRequest & other);

  bool operator==(const QcPostNetworkRequest & rhs) const;

  RequestType type() const { return RequestType::Post; }

  QByteArray data() const { return m_data; }
  void set_data(const QByteArray & data) { m_data = data; }

private:
  QByteArray m_data;
};

QDebug operator<<(QDebug, const QcPostNetworkRequest & request);

/**************************************************************************************************/

#endif /* __NETWORK_REQUEST_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
