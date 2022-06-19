// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
  QJsonDocument to_json_document(); // const

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
