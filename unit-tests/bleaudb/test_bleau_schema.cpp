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

#include "bleaudb/bleau_schema.h"
#include "bleaudb/bleau_sqlite_database.h"

#include <QFile>
#include <QJsonDocument>
#include <QtDebug>

/***************************************************************************************************/

class TestBleauSchema: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestBleauSchema::constructor()
{
  {
    // -Wunused-variable
    QoSchema & place_schema = BleauPlaceSchema::instance();
  }
  {
    // -Wunused-variable
    QoSchema & place_schema = BleauPlace::schema();
  }

  QString sqlite_path("bleau.sqlite"); // Fixme:
  QFile file(sqlite_path);
  if (file.exists())
    file.remove();
  BleauSqliteDatabase bleau_sqlite_database(sqlite_path);
  BleauSchema & bleau_schema = bleau_sqlite_database.schema();
  QoDatabaseTable & place_table = bleau_schema.place();
  QoDatabaseTable & boulder_table = bleau_schema.boulder();
  // QoDatabaseTable & circuit_table = bleau_schema.circuit();
  // QoDatabaseTable & massif_table = bleau_schema.massif();

  QVariantHash place_variant_hash;
  place_variant_hash["category"] = "point d'eau";
  place_variant_hash["coordinate"] = QVariant::fromValue(QGeoCoordinate(2.72, 48.41));
  place_variant_hash["name"] = "Fontaine d'Avon";

  BleauPlace place(place_variant_hash);
  bleau_schema.add(place);

  BleauPlace place_bis = place;
  //!!! place_bis.detach();
  bleau_schema.add<BleauPlace>(place_bis);

  QVariantHash massif_variant_hash;
  massif_variant_hash["acces"] = "...";
  // massif_variant_hash["alternative_name"] = "";
  massif_variant_hash["chaos_type"] = "E/D";
  massif_variant_hash["coordinate"] = QVariant::fromValue(QGeoCoordinate(2.51, 48.37));
  massif_variant_hash["name"] = "91_1"; // Fixme: string !!!
  // massif_variant_hash["note"] = "";
  massif_variant_hash["parcelles"] = "135 141 TP";
  massif_variant_hash["rdv"] = "...";
  massif_variant_hash["secteur"] = "Trois Pignons";
  massif_variant_hash["velo"] = "...";

  // BleauMassif massif(massif_variant_hash);
  QSharedPointer<BleauMassif> massif(new BleauMassif(massif_variant_hash));
  bleau_schema.add(*massif);

  QVariantHash boulder_variant_hash;
  boulder_variant_hash["comment"] = "mur";
  // boulder_variant_hash["coordinate"] = ;
  boulder_variant_hash["grade"] = "5-";
  boulder_variant_hash["name"] = "";
  boulder_variant_hash["number"] = 1;

  BleauBoulder boulder(boulder_variant_hash);
  boulder_table.complete_insert(boulder.to_variant_list_sql());

  QVariantHash circuit_variant_hash;
  circuit_variant_hash["colour"] ="rouge";
  circuit_variant_hash["coordinate"] = QVariant::fromValue(QGeoCoordinate(2.51, 48.37));
  circuit_variant_hash["creation_date"] = QDateTime();
  circuit_variant_hash["gestion"] =  "ONF77";
  circuit_variant_hash["grade"] = "TD-";
  circuit_variant_hash["massif"] = "91_1";
  // circuit_variant_hash["note"] = "";
  circuit_variant_hash["number"] = 1;
  circuit_variant_hash["opener"] = "...";
  circuit_variant_hash["refection_date"] = 2011;
  // circuit_variant_hash["refection_note"] = "";
  circuit_variant_hash["status"] = "liste SNE";
  QStringList string_list ;
  string_list << "http://foo" << "http://bar";
  circuit_variant_hash["topos"] = string_list;

  // BleauCircuit circuit(circuit_variant_hash);
  // circuit.set_massif(massif);
  // qInfo() << QJsonDocument(circuit.to_json());
  // bleau_schema.add(circuit);

  BleauPlace reloaded_place(place_table.select_by_id(place.id()));
  qInfo() << reloaded_place.id() << reloaded_place << place;
  QVERIFY(reloaded_place == place);

  // QSharedPointer<BleauPlace> reloaded_place_bis = bleau_schema.query_by_id<BleauPlace>(place.id());
  // qInfo() << reloaded_place_bis->id() << reloaded_place;
  // QVERIFY(*reloaded_place_bis == place);

  // QSharedPointer<BleauCircuit> reloaded_circuit = bleau_schema.query_by_id<BleauCircuit>(circuit.id());
  // qInfo() << *reloaded_circuit;
  // QSharedPointer<BleauMassif> reloaded_massif = reloaded_circuit->massif();
  // qInfo() << *reloaded_massif;
}

/***************************************************************************************************/

QTEST_MAIN(TestBleauSchema)
#include "test_bleau_schema.moc"
