// -*- mode: c++ -*-
/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire
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
 * $QTCARTO_END_LICENSE$
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

/**************************************************************************************************/

class QcRowTraits
{
public:
  virtual int schema_id() const = 0;

  virtual void set_rowid(int value) = 0;

  // JSON Serializer
  virtual QJsonObject to_json(bool only_changed = false) const = 0;

  // Generic Variant Serializer
  virtual QVariantHash to_variant_hash(bool only_changed = false) const = 0;
  virtual QVariantList to_variant_list() const = 0;

  // SQL Serializer
  virtual QVariantHash to_variant_hash_sql(bool only_changed = false) const = 0;
  virtual QVariantList to_variant_list_sql() const = 0;

  // Query for update
  // virtual bool is_modified() const = 0;

  // Field accessor by position
  virtual QVariant field(int position) const = 0;
  virtual void set_field(int position, const QVariant & value) = 0;
};

/**************************************************************************************************/

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
  QcRow(const QSqlQuery & query) : QcRow() {} // SQL deserializer
  ~QcRow() {}

  QcRow & operator=(const QcRow & other) { return *this; } // m_bits ?

  bool operator==(const QcRow & other) { return true; } // m_bits ?

  virtual int rowid() const { return -1; } // ???

  bool is_modified() const { return not m_bits.isNull(); }

protected:
  bool bit_status(int i) const { return m_bits[i]; }
  void set_bit(int i) { return m_bits.setBit(i); }

private:
  QBitArray m_bits;
};

/**************************************************************************************************/

template<class S>
class QcRowWithId : public QcRow<S>
{
public:
  QcRowWithId();
  QcRowWithId(const QcRowWithId & other);
  QcRowWithId(const QJsonObject & json_object); // JSON deserializer
  QcRowWithId(const QVariantHash & variant_hash);
  QcRowWithId(const QVariantList & variants); // , bool with_rowid = false
  QcRowWithId(const QSqlRecord & record); // SQL deserializer
  QcRowWithId(const QSqlQuery & query); // SQL deserializer
  ~QcRowWithId();

  QcRowWithId & operator=(const QcRowWithId & other);

  bool operator==(const QcRowWithId & other);

  int rowid() const { return m_rowid; }
  void set_rowid(int value) { m_rowid = value; }

private:
  int m_rowid = -1; // note: table can be created without rowid
};

/**************************************************************************************************/

template<class S>
QcRow<S>::QcRow()
  :m_bits(number_of_fields())
{}

template<class S>
QcRow<S>::QcRow(const QcRow & other)
  : QcRow()
    // m_bits(other.m_bits) // Fixme: ???
{}

/**************************************************************************************************/

template<class S>
QcRowWithId<S>::QcRowWithId()
  : QcRow<S>()
{}

template<class S>
QcRowWithId<S>::QcRowWithId(const QcRowWithId & other)
  : QcRow<S>(static_cast<const QcRow<S> &>(other)),
    m_rowid(other.m_rowid)
{}

template<class S>
QcRowWithId<S>::QcRowWithId(const QJsonObject & json_object)
 : QcRowWithId()
{}

template<class S>
QcRowWithId<S>::QcRowWithId(const QVariantHash & variant_hash)
 : QcRowWithId()
{
  if (variant_hash.contains(QLatin1String("rowid")))
    m_rowid = variant_hash[QLatin1String("rowid")].toInt();
  else
    m_rowid = -1;
}

template<class S>
QcRowWithId<S>::QcRowWithId(const QVariantList & variants) // , bool with_rowid
 : QcRowWithId()
{
  int _number_of_fields = QcRow<S>::number_of_fields();
  if (variants.size() == _number_of_fields +1) // with_rowid, danger ?
    // int number_of_fields = variants.size();
    m_rowid = variants[_number_of_fields].toInt();
  else
    m_rowid = -1;
}

template<class S>
QcRowWithId<S>::QcRowWithId(const QSqlRecord & record)
 : QcRowWithId()
{
  // int number_of_fields = record.count();
  m_rowid = record.value(QcRow<S>::number_of_fields()).toInt();
}

template<class S>
QcRowWithId<S>::QcRowWithId(const QSqlQuery & query)
 : QcRowWithId()
{
  // int number_of_fields = query.record().count(); // Fixme: slower ?
  m_rowid = query.value(QcRow<S>::number_of_fields()).toInt();
}

template<class S>
QcRowWithId<S>::~QcRowWithId()
{}

template<class S>
QcRowWithId<S> &
QcRowWithId<S>::operator=(const QcRowWithId & other)
{
  if (this != &other) {
    m_rowid = other.m_rowid;
  }

  return *this;
}

template<class S>
bool
QcRowWithId<S>::operator==(const QcRowWithId & other)
{
  return m_rowid == other.m_rowid;
}

/*
template<class S>
void
QcRowWithId<S>::set_rowid(int value)
{
  if (m_rowid != value) {
    m_rowid = value;
    emit rowidChanged();
  }
}
*/

/**************************************************************************************************/

#endif /* __DATABASE_ROW_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
