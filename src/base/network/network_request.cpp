/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
