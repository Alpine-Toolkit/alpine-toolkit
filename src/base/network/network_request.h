// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __NETWORK_REQUEST_H__
#define __NETWORK_REQUEST_H__

/**************************************************************************************************/

#include <QJsonDocument>
#include <QNetworkRequest>
#include <QObject>
#include <QSharedPointer>
#include <QUrl>

/**************************************************************************************************/

/* The QaNetworkRequest class defines a network resource request.
 *
 */
class QaNetworkRequest : public QObject
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
  QaNetworkRequest();
  QaNetworkRequest(const QUrl & url);
  QaNetworkRequest(const QaNetworkRequest & other);
  virtual ~QaNetworkRequest();

  QaNetworkRequest & operator=(const QaNetworkRequest & other);

  QUrl url() const { return m_url; }
  void set_url(const QUrl & url) { m_url = url; }

  bool operator==(const QaNetworkRequest & rhs) const;

  virtual RequestType type() const = 0;

  QNetworkRequest network_request() const;

public slots:
  virtual void on_error(const QString & error_string) = 0;
  virtual void on_data_received(const QByteArray & data) = 0;

private:
  QUrl m_url;
};

typedef QSharedPointer<QaNetworkRequest> QaNetworkRequestPtr;

QDebug operator<<(QDebug, const QaNetworkRequest & request);

/**************************************************************************************************/

class QaGetNetworkRequest : public QaNetworkRequest
{
  Q_OBJECT

public:
  QaGetNetworkRequest();
  QaGetNetworkRequest(const QUrl & url);
  QaGetNetworkRequest(const QaGetNetworkRequest & other);
  ~QaGetNetworkRequest();

  QaGetNetworkRequest & operator=(const QaGetNetworkRequest & other);

  bool operator==(const QaGetNetworkRequest & rhs) const;

  RequestType type() const { return RequestType::Get; }

// public slots:
//   virtual void on_data_received(const QByteArray & data) = 0;
};

QDebug operator<<(QDebug, const QaGetNetworkRequest & request);

/**************************************************************************************************/

class QaPostNetworkRequest : public QaNetworkRequest
{
  Q_OBJECT

public:
  QaPostNetworkRequest();
  QaPostNetworkRequest(const QUrl & url, const QByteArray & data);
  QaPostNetworkRequest(const QUrl & url, const QJsonDocument & document);
  QaPostNetworkRequest(const QaPostNetworkRequest & other);
  ~QaPostNetworkRequest();

  QaPostNetworkRequest & operator=(const QaPostNetworkRequest & other);

  bool operator==(const QaPostNetworkRequest & rhs) const;

  RequestType type() const { return RequestType::Post; }

  QByteArray data() const { return m_data; }
  void set_data(const QByteArray & data) { m_data = data; }
  void set_data(const QJsonDocument & document);

// public slots:
//   virtual void on_success() = 0;

private:
  QByteArray m_data;
};

QDebug operator<<(QDebug, const QaPostNetworkRequest & request);

/**************************************************************************************************/

#endif /* __NETWORK_REQUEST_H__ */
