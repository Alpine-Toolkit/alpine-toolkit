// -*- mode: c++ -*-

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

#ifndef __BLEAU_SCHEMA_MANAGER_H__
#define __BLEAU_SCHEMA_MANAGER_H__

/**************************************************************************************************/

#include "bleaudb/bleau_schema.h"
#include "orm/schema_manager.h"

#include<QHash>
#include<QJsonDocument>
#include<QObject>
#include<QString>

/**************************************************************************************************/

class BleauSchemaManager : public SchemaManager
{
  Q_OBJECT
  // Q_PROPERTY(BleauPlaceList places READ places WRITE set_places NOTIFY placesChanged)
  // Q_PROPERTY(BleauPlaceList places READ places)
  // Q_PROPERTY(QList<BleauPlace> places READ places WRITE set_places NOTIFY placesChanged)
  // Q_PROPERTY(QList<BleauMassif> massifs READ massifs WRITE set_massifs NOTIFY massifsChanged)
  // Q_PROPERTY(QList<BleauCircuit> circuits READ circuits WRITE set_circuits NOTIFY circuitsChanged)

public:
  typedef QHash<QString, BleauPlacePtr> PlaceHash;
  typedef QHash<QString, BleauMassifPtr> MassifHash;
  // typedef QHash<QString, BleauCircuitPtr> CircuitHash;
  typedef QList<BleauCircuitPtr> CircuitList;

public:
  BleauSchemaManager(); // QObject * parent = nullptr
  BleauSchemaManager(const QString & json_path);
  BleauSchemaManager(const QJsonDocument & json_document);
  // BleauSchemaManager(const class BleauSchemaManager & other);
  ~BleauSchemaManager();

  // BleauSchemaManager & operator=(const BleauSchemaManager & other);

  void load_json_document(const QJsonDocument & json_document);
  QJsonDocument to_json_document() const;

  void to_sql(const QString & sqlite_path);

  CircuitList & circuits() { return m_circuits; }
  void add_circuit(const BleauCircuitPtr & circuit);

  MassifHash & massifs() { return m_massifs; }
  void add_massif(const BleauMassifPtr & massif);

  PlaceHash & places() { return m_places; }
  void add_place(const BleauPlacePtr & place);

// signals:
//   void placesChanged();
//   void massifsChanged();
//   void circuitsChanged();

private:
  CircuitList m_circuits;
  MassifHash m_massifs;
  PlaceHash m_places;
  QList<BleauBoulderPtr> m_boulders; // Fixme: weak ref
};

/**************************************************************************************************/

// QC_END_NAMESPACE

#endif /* __BLEAU_SCHEMA_MANAGER_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
