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

#include "bleaudb/bleau_schema_manager.h"

/***************************************************************************************************/

class TestQcBleauSchemaManager: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestQcBleauSchemaManager::constructor()
{
  QString json_path("../ressources/data/bleau.json");
  BleauSchemaManager bleau_schema_manager(json_path);

  bleau_schema_manager.to_json("bleau.json");

  QString sqlite_path("bleau.sqlite");
  bleau_schema_manager.to_sql(sqlite_path);

  // for (const auto & place : bleau_database.places())
  //   qInfo() << place->name() << place->coordinate();

  // for (const BleauMassif & massif : bleaudb.massifs())
  //   qInfo() << massif.name();

  // for (const BleauCircuit & circuit : bleaudb.circuits()) {
  //   qInfo() << circuit.number();
  //   for (const BleauBoulder & boulder : circuit.boulders())
  //     qInfo() << boulder.name();
  // }
}

/***************************************************************************************************/

QTEST_MAIN(TestQcBleauSchemaManager)
#include "test_bleau_schema_manager.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
