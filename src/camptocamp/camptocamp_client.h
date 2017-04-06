// -*- mode: c++ -*-

/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
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
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __CAMPTOCAMP_H__
#define __CAMPTOCAMP_H__

/**************************************************************************************************/

#include "camptocamp_login.h"
#include "camptocamp_login_data.h"
#include "camptocamp_constant.h"
#include "camptocamp_search_settings.h"

#include <QDateTime>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPointer>
#include <QString>
#include <QStringList>
#include <QUrl>

/**************************************************************************************************/

class C2cClient;

class C2cRequest : public QObject
{
  Q_OBJECT

public:
  C2cRequest(const QNetworkRequest & request); // parent
  ~C2cRequest(); // Fixme: delete this and m_reply

  const QUrl url() const { return m_request.url(); }
  const QNetworkRequest & request() const { return m_request; }

  void set_reply(C2cClient * client, QNetworkReply * network_reply);

  C2cClient * client() const { return m_client; }
  QNetworkReply * network_reply() const { return m_network_reply; }

private slots:
  virtual void finished() = 0;
  // Fixme: void error(Error error, const QString & error_string = QString());

private:
  QNetworkRequest m_request;
  QPointer<QNetworkReply> m_network_reply;
  QPointer<C2cClient> m_client;
};

/**************************************************************************************************/

class C2cApiRequest : public C2cRequest
{
  Q_OBJECT

public:
  C2cApiRequest(const QNetworkRequest & request); // parent
  ~C2cApiRequest();

  virtual void handle_reply(const QJsonDocument * json_data) = 0; // Fixme: const
  virtual void handle_error(const QJsonDocument * json_data) = 0;
  virtual void handle_network_error() = 0;

private slots:
  void finished();
  // Fixme: void error(Error error, const QString & error_string = QString());

private:
  QJsonDocument * reply_to_json() const;
  static bool check_json_response(const QJsonDocument * json_data);
};

/**************************************************************************************************/

class C2cMediaRequest : public C2cRequest
{
  Q_OBJECT

public:
  C2cMediaRequest(const QNetworkRequest & request); // parent // const QString & media_url, const QString & media
  ~C2cMediaRequest();

  const QString & media() const { return m_media; }

private slots:
  void finished();
  // Fixme: void error(Error error, const QString & error_string = QString());

private:
  QString m_media;
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

  void post(const QJsonDocument * json_document);
  void update(const QJsonDocument * json_document, const QString & message = "");

  void media(const QString & path);

signals:
  void logged();
  void login_failed();
  void received_health_status(const QJsonDocument * json_document);
  void get_health_failed(const QJsonDocument * json_document);
  void received_search(const QJsonDocument * json_document);
  void search_failed(const QJsonDocument * json_document);
  void received_document(const QJsonDocument * json_document);
  void get_document_failed(const QJsonDocument * json_document);
  void received_media(const QString & media, const QByteArray data);
  void get_media_failed(const QString & media);

private:
  QUrl make_api_url(const QString & url) const;
  QUrl make_api_url(const QStringList & strings) const;
  QUrl make_media_url(const QString & media) const;
  QNetworkRequest create_network_api_request(const QUrl & url, bool token = false) const;
  QNetworkRequest create_network_api_request(const QStringList & strings, bool token = false) const;
  QNetworkRequest create_network_media_request(const QString & media) const;
  void get(C2cApiRequest * request);
  void get_document(const QString & document_type, unsigned int document_id);
  QUrl make_url_for_document(const QJsonDocument * json_document) const;
  void post(C2cApiRequest * request, const QJsonDocument * json_document, bool check_login = true);

public: // Fixme: wrong design
  void handle_login_reply(const QJsonDocument * json_data);
  void handle_login_error(const QJsonDocument * json_data);
  void handle_health_reply(const QJsonDocument * json_data);
  void handle_health_error(const QJsonDocument * json_data);
  void handle_search_reply(const QJsonDocument * json_data);
  void handle_search_error(const QJsonDocument * json_data);
  void handle_document_reply(const QJsonDocument * json_data);
  void handle_document_error(const QJsonDocument * json_data);
  void handle_media_reply(const QString & media, const QByteArray & data);
  void handle_media_error(const QString & media);

private:
  QString m_api_url;
  QString m_media_url;
  int m_port;
  C2cLogin m_login;
  C2cLoginData m_login_data;
  QNetworkAccessManager m_network_manager;
};

/**************************************************************************************************/

#endif /* __CAMPTOCAMP_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
