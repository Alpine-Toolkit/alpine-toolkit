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

#include "database_schema.h" // for checker

/**************************************************************************************************/

#ifndef __DATABASE_SCHEMA_H__
#define __DATABASE_SCHEMA_H__

/**************************************************************************************************/

template<class T>
void
QcDatabaseSchema::add(T & row)
{
  QcDatabaseTable & table = get_table_by_schema(T::schema());
  table.add(row);
}

template<class T>
QcDatabaseSchema &
QcDatabaseSchema::operator<<(QcRowTraits & row)
{
  add(row);
  return *this;
}

template<class T>
void
QcDatabaseSchema::add(const QList<T *> rows)
{
  QcDatabaseTable & table = get_table_by_schema(T::schema());
  table.add(rows);
}

template<class T>
QSharedPointer<T>
QcDatabaseSchema::query_by_id(int rowid, bool lazy_load)
{
  const QcSchema & schema = T::schema();
  QcDatabaseTable & table = get_table_by_schema(schema);
  T * row = new T(table.select_by_id(rowid)); // Fixme: (this, ..., lazy_load)
  // Fixme: non specific code, QcDatabaseTable has no link to database QcDatabaseSchema !
  row->set_database_schema(this); // Fixme: for all ???
  if (schema.has_foreign_keys()) {
    if (not lazy_load)
      row->load_relations();
  }
  return QSharedPointer<T>(row);
}

/**************************************************************************************************/

#endif /* __DATABASE_SCHEMA_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
