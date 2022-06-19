// -*- mode: c++ -*-
/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef __DATABASE_ROW_H__
#define __DATABASE_ROW_H__

/**************************************************************************************************/

#include <QBitArray>
#include <QJsonObject>
#include <QObject>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariantHash>
#include <QVariantList>
#include <QtDebug>

/**************************************************************************************************/

class QoDatabaseSchema;

/**************************************************************************************************/

// Trait class to be used as generic row (QoRowTraits *) since QoRow is a template class

class QoRowTraits
{
public:
  QoRowTraits() {};
  // ~QoRowTraits();

  // Followings methods define the Row API

  virtual int schema_id() const = 0;

  // JSON Serializer
  virtual QJsonObject to_json(bool only_changed = false) const = 0;

  // Generic Variant Serializer
  virtual QVariantHash to_variant_hash(bool only_changed = false) const = 0;
  virtual QVariantList to_variant_list() const = 0;

  // SQL Serializer
  virtual QVariantHash to_variant_hash_sql(bool only_changed = false, bool duplicate = false) const = 0;
  virtual QVariantList to_variant_list_sql(bool duplicate = false) const = 0;

  // Query for update
  // virtual bool is_modified() const = 0; // implemented in QoRow

  // Field accessor by position
  virtual QVariant field(int position) const = 0;
  virtual void set_field(int position, const QVariant & value) = 0;

  // Fixme: implement has mixin ?
  QoDatabaseSchema * database_schema() const { return m_database_schema; }
  void set_database_schema(QoDatabaseSchema * database_schema)  { m_database_schema = database_schema; }

  // To set id when the row was inserted
  virtual void set_insert_id(int id) { Q_UNUSED(id); };
  virtual bool exists_on_database() const {
    return m_database_schema != nullptr; // Fixme: right ??? commited !
  }

  virtual bool can_save() const { return true; } // Return false if a foreign key is undefined
  virtual void load_relations() {} // To load relations
  virtual void save_relations() {} // To save relations

  virtual bool can_update() const = 0; // To update row
  virtual QVariantHash rowid_kwargs() const = 0;

private:
  QoDatabaseSchema * m_database_schema = nullptr; // use memory !
};

/**************************************************************************************************/

// Row template parametrised by its schema

template<class S>
class QoRow : public QoRowTraits
{
public:
  typedef S Schema;

  static Schema & schema() { return Schema::instance(); }
  int schema_id() const { return schema().schema_id(); }
  // static int number_of_fields() { return schema().number_of_fields(); }
  static int number_of_fields() { return Schema::NUMBER_OF_FIELDS; } // Fixme: faster ?

public:
  QoRow();
  QoRow(const QoRow & other);
  QoRow(const QJsonObject & json_object) : QoRow() { Q_UNUSED(json_object); } // JSON deserializer
  QoRow(const QVariantHash & variant_hash) : QoRow() { Q_UNUSED(variant_hash); }
  QoRow(const QVariantList & variants) : QoRow() { Q_UNUSED(variants); }
  QoRow(const QSqlRecord & record) : QoRow() { Q_UNUSED(record); } // SQL deserializer
  QoRow(const QSqlQuery & query, int offset = 0) : QoRow() { Q_UNUSED(query); Q_UNUSED(offset); } // SQL deserializer
  ~QoRow() {}

  QoRow & operator=(const QoRow & other) { Q_UNUSED(other); return *this; } // Fixme: m_bits ?

  bool operator==(const QoRow & other) const { Q_UNUSED(other); return true; } // Fixme: m_bits ?

  bool is_modified() const {
    return m_bits.count(true);
  }

protected:
  bool bit_status(int i) const { return m_bits[i]; }
  void set_bit(int i) { return m_bits.setBit(i); }

private:
  QBitArray m_bits;
};

/**************************************************************************************************/

// This implementation embed the rowid, and it thus factorise code
// But it makes code generation more complicated, since we have to omit the id field

/*
template<class S>
class QoRowWithId : public QoRow<S>
{
public:
  const int INVALID_ID = -1;

public:
  QoRowWithId();
  QoRowWithId(const QoRowWithId & other);
  QoRowWithId(const QJsonObject & json_object); // JSON deserializer
  QoRowWithId(const QVariantHash & variant_hash);
  QoRowWithId(const QVariantList & variants); // , bool with_id = false
  QoRowWithId(const QSqlRecord & record); // SQL deserializer
  QoRowWithId(const QSqlQuery & query); // SQL deserializer
  ~QoRowWithId();

  QoRowWithId & operator=(const QoRowWithId & other);

  bool operator==(const QoRowWithId & other);

  int id() const { return m_id; }
  void set_id(int value) { m_id = value; }
  bool exists_on_database() const { m_id != INVALID_ID; }
  void detach();

private:
  int m_id = INVALID_ID;
};
*/

/**************************************************************************************************/

#ifndef QC_MANUAL_INSTANTIATION
#include "database_row.hxx"
#endif

/**************************************************************************************************/

#endif /* __DATABASE_ROW_H__ */
