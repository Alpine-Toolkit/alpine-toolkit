/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
  QString json_path("../resources/data/bleau.json");
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
