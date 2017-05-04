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

#include "bleaudb/bleaudb_database.h"

#include <QFile>
#include <QJsonDocument>
#include <QtDebug>

/***************************************************************************************************/

class TestBleauDatabase: public QObject
{
  Q_OBJECT

private slots:
  void constructor();
};

void TestBleauDatabase::constructor()
{
  {
    QcSchema & place_schema = BBleauPlaceSchema::instance();
  }
  {
    QcSchema & place_schema = BBleauPlace::schema();
  }

  QString sqlite_path("bleau.sqlite"); // Fixme:
  QFile file(sqlite_path);
  if (file.exists())
    file.remove();
  BleauDatabase bleau_database(sqlite_path);
  BleauSchema & bleau_schema = bleau_database.schema();
  QcDatabaseTable & place_table = bleau_schema.place();
  QcDatabaseTable & boulder_table = bleau_schema.boulder();
  QcDatabaseTable & circuit_table = bleau_schema.circuit();
  QcDatabaseTable & massif_table = bleau_schema.massif();

  QVariantHash place_variant_hash;
  place_variant_hash["category"] = "point d'eau";
  place_variant_hash["coordinate"] = QVariant::fromValue(QGeoCoordinate(2.72, 48.41));
  place_variant_hash["name"] = "Fontaine d'Avon";

  BBleauPlace place(place_variant_hash);
  // QSqlQuery query = place_table.complete_insert(place.to_variant_list_sql());
  // int rowid = query.lastInsertId().toInt();
  // place.set_rowid(rowid);

  bleau_schema.add(place); // generic
  BBleauPlace place_bis = place;
  place_bis.set_rowid(-1); // reset !
  bleau_schema.add<BBleauPlace>(place_bis);

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

  BBleauMassif massif(massif_variant_hash);
  // massif_table.complete_insert(massif.to_variant_list_sql()); // rowid is not updated
  bleau_schema.add(massif);

  QVariantHash boulder_variant_hash;
  boulder_variant_hash["comment"] = "mur";
  // boulder_variant_hash["coordinate"] = ;
  boulder_variant_hash["grade"] = "5-";
  boulder_variant_hash["name"] = "";
  boulder_variant_hash["number"] = 1;

  BBleauBoulder boulder(boulder_variant_hash);
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

  BBleauCircuit circuit(circuit_variant_hash);
  circuit.set_massif_sql(massif.rowid());
  // circuit_table.complete_insert(circuit.to_variant_list_sql()); // rowid is not updated
  bleau_schema.add(circuit);

  qInfo() << QJsonDocument(circuit.to_json());

  BBleauPlace reloaded_place(place_table.select_by_id(place.rowid()));
  qInfo() << reloaded_place.rowid() << reloaded_place << place;
  QVERIFY(reloaded_place == place);

  QSharedPointer<BBleauPlace> reloaded_place_bis = bleau_schema.query_by_id<BBleauPlace>(place.rowid());
  qInfo() << reloaded_place_bis->rowid() << reloaded_place;
  QVERIFY(*reloaded_place_bis == place);

  QSharedPointer<BBleauCircuit> reloaded_circuit = bleau_schema.query_by_id<BBleauCircuit>(circuit.rowid());
  qInfo() << *reloaded_circuit;
  QSharedPointer<BBleauMassif> reloaded_massif = reloaded_circuit->massif();
  qInfo() << *reloaded_massif;
}

/***************************************************************************************************/

QTEST_MAIN(TestBleauDatabase)
#include "test_bleau_database.moc"

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
