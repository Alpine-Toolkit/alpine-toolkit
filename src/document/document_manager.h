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

#ifndef __DOCUMENT_MANAGER_H__
#define __DOCUMENT_MANAGER_H__

/**************************************************************************************************/

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

class DocumentManager;

class DocumentServerRequest : public QObject
{
  Q_OBJECT

public:
  DocumentServerRequest(const QNetworkRequest & request); // parent
  ~DocumentServerRequest();

  const QUrl url() const { return m_request.url(); }
  const QNetworkRequest & request() const { return m_request; }

  void set_reply(DocumentManager * client, QNetworkReply * network_reply);

  DocumentManager * client() const { return m_client; }
  QNetworkReply * network_reply() const { return m_network_reply; }

  void handle_reply(const QJsonDocument * json_data); // Fixme: const
  void handle_network_error();

private:
  QJsonDocument * reply_to_json() const;
  static bool check_json_response(const QJsonDocument * json_data);

private slots:
  void finished();
  // Fixme: void error(Error error, const QString & error_string = QString());

private:
  QNetworkRequest m_request;
  QPointer<QNetworkReply> m_network_reply;
  QPointer<DocumentManager> m_client;
};

/**************************************************************************************************/

class DocumentManager : public QObject
{
  Q_OBJECT

public:
  DocumentManager(const QString & api_url, int port = -1);
  ~DocumentManager();

  void get_document_list();

signals:
  // void received_document_list(const QJsonDocument * json_document);
  void received_document_list();

private:
  QUrl make_api_url(const QString & url) const;
  QNetworkRequest create_network_api_request(const QUrl & url) const;
  QNetworkRequest create_network_api_request(const QString & endpoint) const;
  void get(DocumentServerRequest * request);

public:
  void handle_document_list_reply(const QJsonDocument * json_data);

private:
  QString m_api_url;
  int m_port;
  QNetworkAccessManager m_network_manager;
};

/**************************************************************************************************/

#endif /* __DOCUMENT_MANAGER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
