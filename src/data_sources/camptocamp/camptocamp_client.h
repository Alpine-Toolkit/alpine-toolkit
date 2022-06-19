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

#ifndef __CAMPTOCAMP_H__
#define __CAMPTOCAMP_H__

/**************************************************************************************************/

#include "camptocamp/camptocamp_constant.h"
#include "camptocamp/camptocamp_login.h"
#include "camptocamp/camptocamp_login_data.h"
#include "camptocamp/camptocamp_search_settings.h"
#include "network/network_request.h"
#include "network/network_request_manager.h"

#include <QDateTime>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSharedPointer>
#include <QString>
#include <QStringList>
#include <QUrl>

/**************************************************************************************************/

class C2cClient;

typedef QSharedPointer<QJsonDocument> QJsonDocumentPtr;

/**************************************************************************************************/

struct C2cApiRequestMixin
{
  static bool check_json_response(const QJsonDocumentPtr & json_document);
  static QJsonDocumentPtr to_json_document(const QByteArray & data);
};

/**************************************************************************************************/

class C2cApiGetRequest : public QaGetNetworkRequest, public C2cApiRequestMixin
{
  Q_OBJECT

public:
  C2cApiGetRequest(const QUrl & url);

signals:
  void finished(const QJsonDocumentPtr & json_document);
  void error(const QJsonDocumentPtr & json_document);

public slots:
  void on_error(const QString & error_string);
  void on_data_received(const QByteArray & data);
};

typedef QSharedPointer<C2cApiGetRequest> C2cApiGetRequestPtr;

/**************************************************************************************************/

class C2cApiPostRequest : public QaPostNetworkRequest, public C2cApiRequestMixin
{
  Q_OBJECT

public:
  C2cApiPostRequest(const QUrl & url, const QJsonDocument & document);

signals:
  void finished(const QJsonDocumentPtr & json_document);
  void error(const QJsonDocumentPtr & json_document);

public slots:
  void on_error(const QString & error_string);
  void on_data_received(const QByteArray & data);
};

typedef QSharedPointer<C2cApiPostRequest> C2cApiPostRequestPtr;

/**************************************************************************************************/

class C2cApiMediaRequest : public QaGetNetworkRequest
{
  Q_OBJECT

public:
  C2cApiMediaRequest(const QUrl & url);

  const QString & media() const { return m_media; }

signals:
  void finished(const QString & media, const QByteArray data);
  void error(const QString & media);

public slots:
  void on_error(const QString & error_string);
  void on_data_received(const QByteArray & data);

private:
  QString m_media;
};

typedef QSharedPointer<C2cApiMediaRequest> C2cApiMediaRequestPtr;

/**************************************************************************************************/

class C2cNetworkRequestManager : public QaNetworkRequestManager
{
public:
  C2cNetworkRequestManager(C2cClient * client);
  ~C2cNetworkRequestManager();

  QNetworkRequest make_request(const QaNetworkRequestPtr & request) const;

  void add_request(C2cApiGetRequest * request) {
    QaNetworkRequestManager::add_request(QaNetworkRequestPtr(request));
  }
  void add_request(C2cApiPostRequest * request) {
    QaNetworkRequestManager::add_request(QaNetworkRequestPtr(request));
  }
  void add_request(C2cApiMediaRequest * request) {
    QaNetworkRequestManager::add_request(QaNetworkRequestPtr(request));
  }
  // void cancel_request(const QaNetworkRequestPtr & request);

private:
  C2cClient * m_client;
};

/**************************************************************************************************/

class C2cClient : public QObject
{
  Q_OBJECT

public:
  C2cClient(const QString & api_url = c2c::OFFICIAL_API_URL,
            const QString & media_url = c2c::OFFICIAL_MEDIA_URL,
            int port = -1);

  void login(const C2cLogin & login, bool remember = true, bool discourse = true);
  void update_login();
  const C2cLogin & login_settings() const { return m_login; } // Fixme: name clash
  const C2cLoginData & login_data() const { return m_login_data; }
  bool is_logged() const { return m_login_data.is_valid(); }

  void health();

  void area(unsigned int document_id);
  void image(unsigned int document_id);
  void map(unsigned int document_id);
  void outing(unsigned int document_id);
  void user_profile(unsigned int user_id = 0);
  void route(unsigned int document_id);
  void xreport(unsigned int document_id);
  void waypoint(unsigned int document_id);

  void search(const QString & search_string, const C2cSearchSettings & settings);

  void post(const QJsonDocumentPtr & json_document);
  void update(const QJsonDocumentPtr & json_document, const QString & message = "");

  void media(const QString & path);

signals:
  void logged();
  void login_failed();
  void received_health_status(const QJsonDocumentPtr & json_document);
  void get_health_failed(const QJsonDocumentPtr & json_document);
  void received_search(const QJsonDocumentPtr & json_document);
  void search_failed(const QJsonDocumentPtr & json_document);
  void received_document(const QJsonDocumentPtr & json_document);
  void get_document_failed(const QJsonDocumentPtr & json_document);
  void received_media(const QString & media, const QByteArray data); // Fixme: const ???
  void get_media_failed(const QString & media);

private:
  QUrl make_api_url(const QString & url) const;
  QUrl make_api_url(const QStringList & strings) const;
  QUrl make_media_url(const QString & media) const;
  void get_document(const QString & document_type, unsigned int document_id);
  QUrl make_url_for_document(const QJsonDocumentPtr & json_document) const;

public:
  void on_login_reply(const QJsonDocumentPtr & json_data);
  void on_login_error(const QJsonDocumentPtr & json_data);

private:
  QString m_api_url;
  QString m_media_url;
  int m_port;
  C2cLogin m_login;
  C2cLoginData m_login_data;
  C2cNetworkRequestManager m_network_manager;
};

/**************************************************************************************************/

#endif /* __CAMPTOCAMP_H__ */
