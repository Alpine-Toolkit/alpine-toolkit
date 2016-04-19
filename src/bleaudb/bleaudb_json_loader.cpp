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

#include <stdexcept>

#include "bleaudb_json_loader.h"

#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QGeoCoordinate
load_coordinate(QJsonObject json_object)
{
  QJsonObject json_coordinate = json_object[QStringLiteral("coordinate")].toObject();
  double longitude = json_coordinate[QStringLiteral("longitude")].toDouble();
  double latitude = json_coordinate[QStringLiteral("latitude")].toDouble();
  return QGeoCoordinate(latitude, longitude);
}

// QcBleauDbJsonLoader::QcBleauDbJsonLoader(const QString & json_path, BleauDB & bleaudb)
void
load_json_bleaudb(const QString & json_path, BleauDB & bleaudb)
{
  QFile json_file(json_path);

  if (!json_file.open(QIODevice::ReadOnly))
    throw std::invalid_argument("Couldn't open file.");

  QByteArray json_data = json_file.readAll();
  QJsonDocument json_document(QJsonDocument::fromJson(json_data));
  QJsonObject root = json_document.object();

  QString COMMENT("comment");
  QString GRADE("grade");
  QString NAME("name");
  QString NOTE("note");
  QString NUMBER("number");

  QJsonArray json_places = root[QStringLiteral("places")].toArray();
  for (const QJsonValue & json_value : json_places) {
    QJsonObject json_object = json_value.toObject();
    BleauPlace place;
    place.set_coordinate(load_coordinate(json_object));
    place.set_name(json_object[NAME].toString());
    place.set_category(json_object[QStringLiteral("category")].toString());
    place.set_note(json_object[NOTE].toString());
    bleaudb.add_place(place);
  }

  QJsonArray json_massifs = root[QStringLiteral("massifs")].toArray();
  for (const QJsonValue & json_value : json_massifs) {
    QJsonObject json_object = json_value.toObject();
    BleauMassif massif;
    massif.set_coordinate(load_coordinate(json_object));
    massif.set_name(json_object[NAME].toString());
    massif.set_access(json_object[QStringLiteral("access")].toString());
    massif.set_alternative_name(json_object[QStringLiteral("alternative_name")].toString());
    massif.set_chaos_type(json_object[QStringLiteral("chaos_type")].toString());
    massif.set_note(json_object[NOTE].toString());
    massif.set_parcelles(json_object[QStringLiteral("parcelles")].toString());
    massif.set_rdv(json_object[QStringLiteral("rdv")].toString());
    massif.set_secteur(json_object[QStringLiteral("secteur")].toString());
    massif.set_velo(json_object[QStringLiteral("velo")].toString());
    bleaudb.add_massif(massif);
  }

  QJsonArray json_circuits = root[QStringLiteral("circuits")].toArray();
  for (const QJsonValue & json_value : json_circuits) {
    QJsonObject json_object = json_value.toObject();
    BleauCircuit circuit;
    QString massif_name = json_object[QStringLiteral("massif")].toString();
    BleauMassif & massif = bleaudb.massifs()[massif_name];
    circuit.set_coordinate(load_coordinate(json_object));
    circuit.set_colour(json_object[QStringLiteral("colour")].toString());
    circuit.set_creation_date(json_object[QStringLiteral("creation_date")].toInt());
    circuit.set_gestion(json_object[QStringLiteral("gestion")].toString());
    circuit.set_grade(json_object[GRADE].toString());
    circuit.set_massif(&massif);
    circuit.set_note(json_object[NOTE].toString());
    circuit.set_number(json_object[NUMBER].toInt());
    circuit.set_opener(json_object[QStringLiteral("opener")].toString());
    circuit.set_refection_date(json_object[QStringLiteral("refection_date")].toInt());
    circuit.set_refection_note(json_object[QStringLiteral("refection_note")].toString());
    circuit.set_status(json_object[QStringLiteral("status")].toString());
    // circuit.set_topos(json_object[QStringLiteral("topos")].toString()); // Fixme:

    QJsonArray json_boulders = json_object[QStringLiteral("boulders")].toArray();
    for (const QJsonValue & json_value : json_boulders) {
      QJsonObject json_object = json_value.toObject();
      BleauBoulder boulder;
      boulder.set_coordinate(load_coordinate(json_object));
      boulder.set_name(json_object[NAME].toString());
      boulder.set_comment(json_object[COMMENT].toString());
      boulder.set_grade(json_object[GRADE].toString());
      boulder.set_number(json_object[NUMBER].toString());
      circuit.add_boulder(boulder);
    }

    bleaudb.add_circuit(circuit);
  }
}

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
