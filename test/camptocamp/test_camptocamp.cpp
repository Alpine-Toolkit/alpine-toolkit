/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
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

#include <QSignalSpy>
#include <QtDebug>
#include <QtTest/QtTest>

#include <iostream>

/**************************************************************************************************/

#include "camptocamp/camptocamp_client.h"
#include "camptocamp/camptocamp_cache.h"
#include "camptocamp/camptocamp_document.h"

#include "login.h"

/***************************************************************************************************/

class MyC2cClient : public C2cClient
{
  Q_OBJECT

public:
  MyC2cClient(const QString & api_url = c2c::OFFICIAL_API_URL, int port = -1)
    :  C2cClient(api_url, port)
  {}

public slots:
  void handle_received_document(const QJsonDocument * json_document) {
    // qInfo() << "Received document"; // << json_document->toJson(QJsonDocument::Indented);

    C2cSearchResult search_result(json_document);
    for (const auto & route : search_result.routes())
      qInfo() << route.title(QStringLiteral("fr"));
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
  C2cLogin login(username, password);
  qInfo() << login;
  MyC2cClient client;
  client.login(login);
  {
    QSignalSpy spy(&client, &C2cClient::logged);
    QVERIFY(spy.wait(5000)); // ms
  }

  {
    client.health();
    QSignalSpy spy(&client, &C2cClient::received_document);
    QVERIFY(spy.wait(5000)); // ms
  }

  {
    client.route(570170);
    QSignalSpy spy(&client, &C2cClient::received_document);
    QVERIFY(spy.wait(5000)); // ms
  }

  {
    connect(&client, &MyC2cClient::received_document,
            &client, &MyC2cClient::handle_received_document);
    client.search("sonia calanque", C2cSearchSettings());
    QSignalSpy spy(&client, &C2cClient::received_document);
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
  C2cCache cache(sqlite_path);

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
