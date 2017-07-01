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

#include "network_request.h"

#include <QtDebug>

/**************************************************************************************************/

QcNetworkRequest::QcNetworkRequest()
  : QObject(),
    m_url()
{}

QcNetworkRequest::QcNetworkRequest(const QUrl & url)
  : QObject(),
    m_url(url)
{}

QcNetworkRequest::QcNetworkRequest(const QcNetworkRequest & other)
  : QObject(),
    m_url(other.m_url)
{}

QcNetworkRequest::~QcNetworkRequest()
{
  qInfo() << "~QcNetworkRequest";
}

QcNetworkRequest &
QcNetworkRequest::operator=(const QcNetworkRequest & other)
{
  if (this != &other) {
    m_url = other.m_url;
  }

  return *this;
}

bool
QcNetworkRequest::operator==(const QcNetworkRequest & rhs) const
{
  return m_url == rhs.m_url;
}

QNetworkRequest
QcNetworkRequest::network_request() const
{
  return QNetworkRequest(m_url);
}

/*
unsigned int
qHash(const QcNetworkRequest & request)
{
  unsigned int result = qHash(request.url());
  qInfo() << "QcNetworkRequest hash" << result;
  return result;
}
*/

QDebug
operator<<(QDebug debug, const QcNetworkRequest & request)
{
  debug << QLatin1String("QcNetworkRequest") << request.url().url();
  return debug;
}

/**************************************************************************************************/

QcGetNetworkRequest::QcGetNetworkRequest()
  : QcNetworkRequest()
{}

QcGetNetworkRequest::QcGetNetworkRequest(const QUrl & url)
  : QcNetworkRequest(url)
{}

QcGetNetworkRequest::QcGetNetworkRequest(const QcGetNetworkRequest & other)
  : QcNetworkRequest(other)
{}

QcGetNetworkRequest::~QcGetNetworkRequest()
{
  qInfo() << "~QcGetNetworkRequest";
}

QcGetNetworkRequest &
QcGetNetworkRequest::operator=(const QcGetNetworkRequest & other)
{
  if (this != &other) {
    QcNetworkRequest::operator=(other);
  }

  return *this;
}

bool
QcGetNetworkRequest::operator==(const QcGetNetworkRequest & rhs) const
{
  return QcNetworkRequest::operator==(rhs);
}

QDebug
operator<<(QDebug debug, const QcGetNetworkRequest & request)
{
  debug << QLatin1String("QcGetNetworkRequest") << request.url().url();
  return debug;
}

/**************************************************************************************************/

QcPostNetworkRequest::QcPostNetworkRequest()
  : QcNetworkRequest(),
    m_data()
{}

QcPostNetworkRequest::QcPostNetworkRequest(const QUrl & url, const QByteArray & data)
  : QcNetworkRequest(url),
    m_data(data)
{}

QcPostNetworkRequest::QcPostNetworkRequest(const QcPostNetworkRequest & other)
  : QcNetworkRequest(other),
    m_data(other.m_data)
{}

QcPostNetworkRequest::~QcPostNetworkRequest()
{
  qInfo() << "~QcPostNetworkRequest";
}

QcPostNetworkRequest &
QcPostNetworkRequest::operator=(const QcPostNetworkRequest & other)
{
  if (this != &other) {
    QcNetworkRequest::operator=(other);
    m_data = other.m_data;
  }

  return *this;
}

bool
QcPostNetworkRequest::operator==(const QcPostNetworkRequest & rhs) const
{
  return QcNetworkRequest::operator==(rhs) and m_data == rhs.m_data;
}

QDebug
operator<<(QDebug debug, const QcPostNetworkRequest & request)
{
  debug << QLatin1String("QcPostNetworkRequest") << request.url().url();
  return debug;
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
