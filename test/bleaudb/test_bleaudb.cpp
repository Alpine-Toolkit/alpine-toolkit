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

#include <QtTest/QtTest>

/**************************************************************************************************/

#include "bleaudb/bleaudb_json_loader.h"

/***************************************************************************************************/

class TestQcBleauDB: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestQcBleauDB::constructor()
{
  QString json_path("data/bleau.json"); // Fixme:
  // QcBleauDbJsonLoader bleaudb_json_loader(path);
  BleauDB bleaudb;
  load_json_bleaudb(json_path, bleaudb);

  for (const BleauPlace & place : bleaudb.places())
    qInfo() << place.name() << place.coordinate();

  for (const BleauMassif & massif : bleaudb.massifs())
    qInfo() << massif.name();

  // for (const BleauCircuit & circuit : bleaudb.circuits()) {
  //   qInfo() << circuit.number();
  //   for (const BleauBoulder & boulder : circuit.boulders())
  //     qInfo() << boulder.name();
  // }
}

/***************************************************************************************************/

QTEST_MAIN(TestQcBleauDB)
#include "test_bleaudb.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
