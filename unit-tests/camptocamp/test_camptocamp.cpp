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

#include <QMetaType>
#include <QSignalSpy>
#include <QtDebug>
#include <QtTest/QtTest>

#include <iostream>

/**************************************************************************************************/

#include "camptocamp/camptocamp_api_cache.h"
#include "camptocamp/camptocamp_client.h"
#include "camptocamp/camptocamp_document.h"
#include "camptocamp/camptocamp_media_cache.h"

#include "login.h"

/***************************************************************************************************/

class MyC2cClient : public C2cClient
{
  Q_OBJECT

public:
  MyC2cClient(const QString & api_url = c2c::OFFICIAL_API_URL,
              const QString & media_url = c2c::OFFICIAL_MEDIA_URL,
              int port = -1)
    : C2cClient(api_url, media_url, port)
  {
    connect(this, &C2cClient::received_health_status,
            this, &MyC2cClient::received_health_status_hook);
    connect(this, &C2cClient::received_document,
            this, &MyC2cClient::received_document_hook);
    connect(this, &C2cClient::received_search,
            this, &MyC2cClient::received_search_hook);

    // connect(this, SIGNAL(received_health_status),
    //         this, SLOT(received_health_status_hook));
    // connect(this, SIGNAL(received_document),
    //         this, SLOT(received_document_hook));
  }

signals:
  void received_response();

public slots:
  void received_health_status_hook(const QJsonDocument * json_document) {
    qInfo() << "Received health status" << json_document->toJson(QJsonDocument::Indented);
    emit received_response();
  }

  void received_document_hook(const QJsonDocument * json_document) {
    C2cDocument document(json_document->object());
    C2cDocument * casted_document = document.cast();
    qInfo() << "Received document" << *casted_document; // << json_document->toJson(QJsonDocument::Indented);
    emit received_response();
  }

  void received_search_hook(const QJsonDocument * json_document) {
    C2cSearchResult search_result(json_document);
    for (const auto & route : search_result.routes())
      qInfo() << route.id() << route.title(QStringLiteral("fr")) << route.activities();

    emit received_response();
  }
};

/***************************************************************************************************/

class TestC2cClient: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void
TestC2cClient::constructor()
{
  // C2cLogin login(username, password);
  // qInfo() << login;
  MyC2cClient client;
  // client.login(login);
  // {
  //   QSignalSpy spy(&client, &C2cClient::logged);
  //   QVERIFY(spy.wait(5000)); // ms
  // }

  // {
  //   client.health();
  //   // Fixme: QSignalSpy: Unable to handle parameter 'json_document'
  //   // of type 'const QJsonDocument*' of method
  //   // 'received_health_status', use qRegisterMetaType to register it.
  //   // QSignalSpy spy(&client, &C2cClient::received_health_status);
  //   QSignalSpy spy(&client, &MyC2cClient::received_response);
  //   QVERIFY(spy.wait(5000)); // ms
  // }

  // {
  //   client.route(570170);
  //   // QSignalSpy spy(&client, &C2cClient::received_document);
  //   QSignalSpy spy(&client, &MyC2cClient::received_response);
  //   QVERIFY(spy.wait(5000)); // ms
  // }

  {
    C2cSearchSettings search_settings;
    search_settings.set_route(true);
    search_settings.add_string_filter("act", "rock_climbing");
    QStringList string_list;
    string_list << "single" << "multi";
    search_settings.add_string_list_filter("crtyp", string_list);
    search_settings.add_int_pair_filter("rmaxa", 0, 1000);
    client.search("sonia calanque", search_settings);
    // QSignalSpy spy(&client, &C2cClient::received_document);
    QSignalSpy spy(&client, &MyC2cClient::received_response);
    QVERIFY(spy.wait(5000)); // ms
  }
}

/***************************************************************************************************/

class TestC2cCache: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestC2cCache::constructor()
{
  QString sqlite_path = "c2c-cache.sqlite3";
  C2cApiCache cache(sqlite_path);

  qInfo() << cache.login();

  QString username = "fabricesalvaire";
  QString password = "YafL6U3N";
  C2cLogin login(username, password);
  cache.save_login(login);
  qInfo() << cache.login();
}

/***************************************************************************************************/

QTEST_MAIN(TestC2cClient)
// QTEST_MAIN(TestC2cCache)
#include "test_camptocamp.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
