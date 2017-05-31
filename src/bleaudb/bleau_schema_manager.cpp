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

#include "bleau_schema_manager.h"

#include "bleau_sqlite_database.h"

#include <QByteArray>
#include <QFile>
#include <QJsonArray>
#include <QtDebug>

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

BleauSchemaManager::BleauSchemaManager()
  : SchemaManager(),
    m_circuits(),
    m_massifs(),
    m_places()
{}

BleauSchemaManager::BleauSchemaManager(const QString & json_path)
  : BleauSchemaManager()
{
  load_json(json_path);
}

BleauSchemaManager::BleauSchemaManager(const QJsonDocument & json_document)
 : BleauSchemaManager()
{
  load_json_document(json_document);
}

/*
BleauSchemaManager::BleauSchemaManager(const BleauSchemaManager & other)
  : QObject(),
    m_places(other.m_places),
    m_massifs(other.m_massifs),
    m_circuits(other.m_circuits)
{}
*/

BleauSchemaManager::~BleauSchemaManager()
{}

// BleauSchemaManager &
// BleauSchemaManager::operator=(const BleauSchemaManager & other)
// {
//   if (this != &other) {
//     m_places = other.m_places;
//     m_massifs = other.m_massifs;
//     m_circuits = other.m_circuits;
//   }

//   return *this;
// }

void
BleauSchemaManager::add_place(const BleauPlacePtr & place)
{
  m_places.insert(place->name(), place);
  // emit placesChanged();
}

void
BleauSchemaManager::add_massif(const BleauMassifPtr & massif)
{
  m_massifs.insert(massif->name(), massif);
  // emit massifsChanged();
}

void
BleauSchemaManager::add_circuit(const BleauCircuitPtr & circuit)
{
  m_circuits.append(circuit);
  // m_circuits.insert(circuit->name(), circuit);
  // emit circuitsChanged();
}

void
BleauSchemaManager::load_json_document(const QJsonDocument & json_document)
{
  QJsonObject root = json_document.object();

  QJsonArray json_places = root[QLatin1String("places")].toArray();
  for (const auto & json_value : json_places) {
    BleauPlacePtr place(json_value.toObject());
    add_place(place);
  }

  QJsonArray json_massifs = root[QLatin1String("massifs")].toArray();
  for (const auto & json_value : json_massifs) {
    BleauMassifPtr massif(json_value.toObject());
    // qInfo() << massif;
    add_massif(massif);
  }

  QJsonArray json_circuits = root[QLatin1String("circuits")].toArray();
  for (const auto & json_value : json_circuits) {
    QJsonObject json_object = json_value.toObject();
    BleauCircuitPtr circuit(json_object);
    // Fixme: massif name vs id
    QString massif_name = json_object[QLatin1String("massif")].toString();
    BleauMassifPtr & massif = m_massifs[massif_name];
    circuit.set_massif(massif);

    QJsonArray json_boulders = json_object[QLatin1String("boulders")].toArray();
    for (const auto & json_value : json_boulders) {
      BleauBoulderPtr boulder(json_value.toObject());
      boulder.set_circuit(circuit);
      // qInfo() << boulder;
      // Fixme: boulder is detroyed, weak ref !!!
      m_boulders << boulder;
    }

    // qInfo() << circuit;
    add_circuit(circuit);
  }
}

QJsonDocument
BleauSchemaManager::to_json_document() // const
{
  QJsonObject root;

  {
    QJsonArray json_places;
    for (const auto & place : m_places)
      json_places << place->to_json();
    root[QLatin1String("places")] = json_places;
  }
  {
    QJsonArray json_massifs;
    for (const auto & massif : m_massifs)
      json_massifs << massif->to_json();
    root[QLatin1String("massifs")] = json_massifs;
  }
  {
    QJsonArray json_circuits;
    for (const auto & circuit : m_circuits) {
      QJsonObject json_object = circuit->to_json();
      // Fixme: massif name vs id
      json_object[QLatin1String("massif")] = circuit->massif()->name();
      QJsonArray json_boulders;
      for (const auto & boulder : circuit->boulders())
        json_boulders << boulder.data()->to_json();
      json_object[QLatin1String("boulders")] = json_boulders;
      json_circuits << json_object;
    }
    root[QLatin1String("circuit")] = json_circuits;
  }

  return QJsonDocument(root);
}

void
BleauSchemaManager::to_sql(const QString & sqlite_path)
{
  // Fixme: if file exists ???

  BleauSqliteDatabase bleau_sqlite_database(sqlite_path);
  BleauSchema & bleau_schema = bleau_sqlite_database.schema();

  for (const auto & place : m_places)
    bleau_schema.add_ptr(place);

  // Fixme: transaction
  // Fixme: mass add
  // Fixme: fails !!!

  // Save massif > circuit > boulder
  // for (const auto & massif : m_massifs)
  //   bleau_schema.add_ptr(massif);
}

/**************************************************************************************************/

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
