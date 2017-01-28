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

/**************************************************************************************************/

#include "camptocamp/camptocamp.h"

/***************************************************************************************************/

class TestC2cClient: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestC2cClient::constructor()
{
  QString username = "fabricesalvaire";
  QString password = "YafL6U3N";
  C2cLogin login(username, password);
  qInfo() << login;
  C2cClient client(login);
  {
    QSignalSpy spy(&client, &C2cClient::logged);
    QVERIFY(spy.wait(5000)); // ms
  }

  {
    client.health();
    QSignalSpy spy(&client, &C2cClient::get_finished);
    QVERIFY(spy.wait(5000)); // ms
  }

  {
    client.route(570170);
    QSignalSpy spy(&client, &C2cClient::get_finished);
    QVERIFY(spy.wait(5000)); // ms
  }

  {
    client.search("sonia calanque", C2cSearchSettings());
    QSignalSpy spy(&client, &C2cClient::get_finished);
    QVERIFY(spy.wait(5000)); // ms
  }
}

/***************************************************************************************************/

QTEST_MAIN(TestC2cClient)
#include "test_camptocamp.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
