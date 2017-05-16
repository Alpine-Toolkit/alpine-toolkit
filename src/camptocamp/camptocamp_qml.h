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

#ifndef __CAMPTOCAMP_QML_H__
#define __CAMPTOCAMP_QML_H__

/**************************************************************************************************/

#include "camptocamp/camptocamp_api_cache.h"
#include "camptocamp/camptocamp_client.h"
#include "camptocamp/camptocamp_document.h"
#include "camptocamp/camptocamp_media_cache.h"

#include <QHash>

/**************************************************************************************************/

class C2cQmlClient :public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool logged READ is_logged NOTIFY loginStatusChanged)
  Q_PROPERTY(QString username READ username WRITE set_username NOTIFY usernameChanged)
  Q_PROPERTY(QString password READ password WRITE set_password NOTIFY passwordChanged)
  Q_PROPERTY(C2cSearchResult* search_result READ search_result CONSTANT) // NOTIFY receivedSearch

public:
  C2cQmlClient(const QString & sqlite_path, const QString & media_path);

  Q_INVOKABLE void save_login();
  Q_INVOKABLE void login();
  Q_INVOKABLE void logout();

  // Q_INVOKABLE void health();

  Q_INVOKABLE void area(unsigned int document_id, bool use_cache = true);
  Q_INVOKABLE void image(unsigned int document_id, bool use_cache = true);
  Q_INVOKABLE void map(unsigned int document_id, bool use_cache = true);
  Q_INVOKABLE void outing(unsigned int document_id, bool use_cache = true);
  Q_INVOKABLE void user_profile(unsigned int user_id = 0, bool use_cache = true);
  Q_INVOKABLE void route(unsigned int document_id, bool use_cache = true);
  Q_INVOKABLE void xreport(unsigned int document_id, bool use_cache = true);
  Q_INVOKABLE void waypoint(unsigned int document_id, bool use_cache = true);

  Q_INVOKABLE C2cDocument * get_document(unsigned int document_id, bool use_cache = true);
  Q_INVOKABLE bool is_document_cached(unsigned int document_id);
  Q_INVOKABLE void save_document(unsigned int document_id);

  Q_INVOKABLE void search(const QString & search_string, const C2cSearchSettings & settings);
  C2cSearchResult * search_result() { return &m_search_result; } // Fixme: const ???

  Q_INVOKABLE void media(const QString & media, bool use_cache = true);
  Q_INVOKABLE QByteArray * get_media(const QString & media, bool use_cache = true);
  Q_INVOKABLE bool is_media_cached(const QString & media);
  Q_INVOKABLE void save_media(const QString & media);

private:
  const QString & username() const;
  void set_username(const QString & username);

  const QString & password() const;
  void set_password(const QString & password);

  bool is_logged() const {
    return m_client.is_logged();
  }

  void load_document(unsigned int document_id, bool use_cache, void (C2cClient::*loader)(unsigned int));

signals:
  void receivedDocument(unsigned int document_id);
  void receivedMedia(const QString & media);
  void receivedSearch(); // searchReceived ???

  void usernameChanged(); // const QString & username
  void passwordChanged(); // const QString & password
  void loginStatusChanged();
  // void logged();
  // void login_failed();

private slots:
  void on_logged();
  void on_loggin_failed();
  void on_received_document(const QJsonDocument * json_document);
  // void on_get_document_failed(const QJsonDocument * json_document);
  void on_received_media(const QString & media, QByteArray data);
  void on_received_search(const QJsonDocument * json_document);
  // void on_search_failed(const QJsonDocument * json_document);

private:
  C2cClient m_client;
  C2cApiCache m_api_cache;
  C2cMediaCache m_media_cache;
  C2cLogin m_login;
  QHash<unsigned int, C2cDocument *> m_documents; // Fixme: qpointer, use constrained cache
  QHash<QString, QByteArray *> m_medias; // Fixme: qpointer
  C2cSearchResult m_search_result;
};

/**************************************************************************************************/

#endif /* __CAMPTOCAMP_QML_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
