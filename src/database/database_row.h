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

template<int NUMBER_OF_FIELDS>
class QcRow // : public QObject
{
  // Q_OBJECT

public:
  // virtual constexpr int number_of_fields() { return 0; }

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

protected: // Fixme: ???
  QBitArray m_bits;
};

/**************************************************************************************************/

template<int NUMBER_OF_FIELDS>
class QcRowWithId : public QcRow<NUMBER_OF_FIELDS>
{
  // Q_OBJECT

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
  // void set_rowid(int value) { m_rowid = value; }

private:
  int m_rowid = -1; // note: table can be created without rowid
};

/**************************************************************************************************/

template<int NUMBER_OF_FIELDS>
QcRow<NUMBER_OF_FIELDS>::QcRow()
  : // QObject(),
    m_bits(NUMBER_OF_FIELDS)
{}

template<int NUMBER_OF_FIELDS>
QcRow<NUMBER_OF_FIELDS>::QcRow(const QcRow & other)
  : QcRow()
    // : QObject(),
    //   m_bits(other.m_bits) // Fixme: ???
{}

/**************************************************************************************************/

template<int NUMBER_OF_FIELDS>
QcRowWithId<NUMBER_OF_FIELDS>::QcRowWithId()
  : QcRow<NUMBER_OF_FIELDS>()
{}

template<int NUMBER_OF_FIELDS>
QcRowWithId<NUMBER_OF_FIELDS>::QcRowWithId(const QcRowWithId & other)
  : QcRow<NUMBER_OF_FIELDS>(static_cast<const QcRow<NUMBER_OF_FIELDS> &>(other)),
    m_rowid(other.m_rowid)
{}

template<int NUMBER_OF_FIELDS>
QcRowWithId<NUMBER_OF_FIELDS>::QcRowWithId(const QJsonObject & json_object)
 : QcRowWithId()
{}

template<int NUMBER_OF_FIELDS>
QcRowWithId<NUMBER_OF_FIELDS>::QcRowWithId(const QVariantHash & variant_hash)
 : QcRowWithId()
{
  if (variant_hash.contains(QLatin1String("rowid")))
    m_rowid = variant_hash[QLatin1String("rowid")].toInt();
  else
    m_rowid = -1;
}

template<int NUMBER_OF_FIELDS>
QcRowWithId<NUMBER_OF_FIELDS>::QcRowWithId(const QVariantList & variants) // , bool with_rowid
 : QcRowWithId()
{
  if (variants.size() == NUMBER_OF_FIELDS +1) // with_rowid, danger ?
    // int number_of_fields = variants.size();
    m_rowid = variants[NUMBER_OF_FIELDS].toInt();
  else
    m_rowid = -1;
}

template<int NUMBER_OF_FIELDS>
QcRowWithId<NUMBER_OF_FIELDS>::QcRowWithId(const QSqlRecord & record)
 : QcRowWithId()
{
  // int number_of_fields = record.count();
  m_rowid = record.value(NUMBER_OF_FIELDS).toInt();
}

template<int NUMBER_OF_FIELDS>
QcRowWithId<NUMBER_OF_FIELDS>::QcRowWithId(const QSqlQuery & query)
 : QcRowWithId()
{
  // int number_of_fields = query.record().count(); // Fixme: faster using static function ?
  m_rowid = query.value(NUMBER_OF_FIELDS).toInt();
}

template<int NUMBER_OF_FIELDS>
QcRowWithId<NUMBER_OF_FIELDS>::~QcRowWithId()
{}

template<int NUMBER_OF_FIELDS>
QcRowWithId<NUMBER_OF_FIELDS> &
QcRowWithId<NUMBER_OF_FIELDS>::operator=(const QcRowWithId & other)
{
  if (this != &other) {
    m_rowid = other.m_rowid;
  }

  return *this;
}

template<int NUMBER_OF_FIELDS>
bool
QcRowWithId<NUMBER_OF_FIELDS>::operator==(const QcRowWithId & other)
{
  return m_rowid == other.m_rowid;
}

/*
template<int NUMBER_OF_FIELDS>
void
QcRowWithId<NUMBER_OF_FIELDS>::set_rowid(int value)
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
