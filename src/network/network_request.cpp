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
#include "alpine_toolkit.h"

#include <QtDebug>

/**************************************************************************************************/

QaNetworkRequest::QaNetworkRequest()
  : QObject(),
    m_url()
{}

QaNetworkRequest::QaNetworkRequest(const QUrl & url)
  : QObject(),
    m_url(url)
{}

QaNetworkRequest::QaNetworkRequest(const QaNetworkRequest & other)
  : QObject(),
    m_url(other.m_url)
{}

QaNetworkRequest::~QaNetworkRequest()
{
  qATInfo() << "~QaNetworkRequest";
}

QaNetworkRequest &
QaNetworkRequest::operator=(const QaNetworkRequest & other)
{
  if (this != &other) {
    m_url = other.m_url;
  }

  return *this;
}

bool
QaNetworkRequest::operator==(const QaNetworkRequest & rhs) const
{
  return m_url == rhs.m_url;
}

QNetworkRequest
QaNetworkRequest::network_request() const
{
  return QNetworkRequest(m_url);
}

/*
unsigned int
qHash(const QaNetworkRequest & request)
{
  unsigned int result = qHash(request.url());
  qATInfo() << "QaNetworkRequest hash" << result;
  return result;
}
*/

QDebug
operator<<(QDebug debug, const QaNetworkRequest & request)
{
  debug << QLatin1String("QaNetworkRequest") << request.url().url();
  return debug;
}

/**************************************************************************************************/

QaGetNetworkRequest::QaGetNetworkRequest()
  : QaNetworkRequest()
{}

QaGetNetworkRequest::QaGetNetworkRequest(const QUrl & url)
  : QaNetworkRequest(url)
{}

QaGetNetworkRequest::QaGetNetworkRequest(const QaGetNetworkRequest & other)
  : QaNetworkRequest(other)
{}

QaGetNetworkRequest::~QaGetNetworkRequest()
{
  qATInfo() << "~QaGetNetworkRequest";
}

QaGetNetworkRequest &
QaGetNetworkRequest::operator=(const QaGetNetworkRequest & other)
{
  if (this != &other) {
    QaNetworkRequest::operator=(other);
  }

  return *this;
}

bool
QaGetNetworkRequest::operator==(const QaGetNetworkRequest & rhs) const
{
  return QaNetworkRequest::operator==(rhs);
}

QDebug
operator<<(QDebug debug, const QaGetNetworkRequest & request)
{
  debug << QLatin1String("QaGetNetworkRequest") << request.url().url();
  return debug;
}

/**************************************************************************************************/

QaPostNetworkRequest::QaPostNetworkRequest()
  : QaNetworkRequest(),
    m_data()
{}

QaPostNetworkRequest::QaPostNetworkRequest(const QUrl & url, const QByteArray & data)
  : QaNetworkRequest(url),
    m_data(data)
{}

QaPostNetworkRequest::QaPostNetworkRequest(const QUrl & url, const QJsonDocument & document)
  : QaNetworkRequest(url)
{
  set_data(document);
}

QaPostNetworkRequest::QaPostNetworkRequest(const QaPostNetworkRequest & other)
  : QaNetworkRequest(other),
    m_data(other.m_data)
{}

QaPostNetworkRequest::~QaPostNetworkRequest()
{
  qATInfo() << "~QaPostNetworkRequest";
}

QaPostNetworkRequest &
QaPostNetworkRequest::operator=(const QaPostNetworkRequest & other)
{
  if (this != &other) {
    QaNetworkRequest::operator=(other);
    m_data = other.m_data;
  }

  return *this;
}

bool
QaPostNetworkRequest::operator==(const QaPostNetworkRequest & rhs) const
{
  return QaNetworkRequest::operator==(rhs) and m_data == rhs.m_data;
}

void
QaPostNetworkRequest::set_data(const QJsonDocument & document)
{
  // Fixme: set header
  m_data = document.toJson(QJsonDocument::Compact);
}

QDebug
operator<<(QDebug debug, const QaPostNetworkRequest & request)
{
  debug << QLatin1String("QaPostNetworkRequest") << request.url().url();
  return debug;
}
