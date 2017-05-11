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

#ifndef __BLEAU_DATABASE_H__
#define __BLEAU_DATABASE_H__

/**************************************************************************************************/

#include "bleaudb/bleau_schema.h"

#include<QHash>
#include<QJsonDocument>
#include<QObject>
#include<QString>

/**************************************************************************************************/

class BleauDatabase : public QObject
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
  BleauDatabase(); // QObject * parent = nullptr
  BleauDatabase(const QString & json_path);
  BleauDatabase(const QJsonDocument & json_document);
  // BleauDatabase(const class BleauDatabase & other);
  ~BleauDatabase();

  // BleauDatabase & operator=(const BleauDatabase & other);

  void load_json(const QString & json_path);
  void load_json(const QJsonDocument & json_document);
  void to_json(const QString & json_path) const;
  QJsonDocument to_json() const;

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

#endif /* __BLEAU_DATABASE_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
