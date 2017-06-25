// -*- mode: c++ -*-
/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the QtCarto library.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $ALPINE_TOOLKIT_END_LICENSE$
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

class QcDatabaseSchema;

/**************************************************************************************************/

// Trait class to be used as generic row (QcRowTraits *) since QcRow is a template class

class QcRowTraits
{
public:
  QcRowTraits() {};
  // ~QcRowTraits();

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
  // virtual bool is_modified() const = 0; // implemented in QcRow

  // Field accessor by position
  virtual QVariant field(int position) const = 0;
  virtual void set_field(int position, const QVariant & value) = 0;

  // Fixme: implement has mixin ?
  QcDatabaseSchema * database_schema() const { return m_database_schema; }
  void set_database_schema(QcDatabaseSchema * database_schema)  { m_database_schema = database_schema; }

  // To set id when the row was inserted
  virtual void set_insert_id(int id) {};
  virtual bool exists_on_database() const {
    return m_database_schema != nullptr; // Fixme: right ??? commited !
  }

  virtual bool can_save() const { return true; } // Return false if a foreign key is undefined
  virtual void load_relations() {} // To load relations
  virtual void save_relations() {} // To save relations

  virtual bool can_update() const = 0; // To update row
  virtual QVariantHash rowid_kwargs() const = 0;

private:
  QcDatabaseSchema * m_database_schema = nullptr; // use memory !
};

/**************************************************************************************************/

// Row template parametrised by its schema

template<class S>
class QcRow : public QcRowTraits
{
public:
  typedef S Schema;

  static Schema & schema() { return Schema::instance(); }
  int schema_id() const { return schema().schema_id(); }
  // static int number_of_fields() { return schema().number_of_fields(); }
  static int number_of_fields() { return Schema::NUMBER_OF_FIELDS; } // Fixme: faster ?

public:
  QcRow();
  QcRow(const QcRow & other);
  QcRow(const QJsonObject & json_object) : QcRow() {} // JSON deserializer
  QcRow(const QVariantHash & variant_hash) : QcRow() {}
  QcRow(const QVariantList & variants) : QcRow() {}
  QcRow(const QSqlRecord & record) : QcRow() {} // SQL deserializer
  QcRow(const QSqlQuery & query, int offset = 0) : QcRow() {} // SQL deserializer
  ~QcRow() {}

  QcRow & operator=(const QcRow & other) { return *this; } // Fixme: m_bits ?

  bool operator==(const QcRow & other) const { return true; } // Fixme: m_bits ?

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
class QcRowWithId : public QcRow<S>
{
public:
  const int INVALID_ID = -1;

public:
  QcRowWithId();
  QcRowWithId(const QcRowWithId & other);
  QcRowWithId(const QJsonObject & json_object); // JSON deserializer
  QcRowWithId(const QVariantHash & variant_hash);
  QcRowWithId(const QVariantList & variants); // , bool with_id = false
  QcRowWithId(const QSqlRecord & record); // SQL deserializer
  QcRowWithId(const QSqlQuery & query); // SQL deserializer
  ~QcRowWithId();

  QcRowWithId & operator=(const QcRowWithId & other);

  bool operator==(const QcRowWithId & other);

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

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
