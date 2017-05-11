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
QcDatabaseSchema::add(T & row, bool save_relations)
{
  // Check foreign keys are set
  if (not row.can_save()) {
    qWarning().noquote() << QLatin1String("ORM: Cannot save on database:") << row;
    return;
  }

  QcDatabaseTable & table = get_table_by_schema(T::schema());
  table.add(row); // call set_insert_id

  row.set_database_schema(this);

  if (save_relations) {
    qInfo() << "Save relations of" << row;
    row.save_relations();
  }
}

template<class T>
QcDatabaseSchema &
QcDatabaseSchema::operator<<(QcRowTraits & row)
{
  add(row); // save_relations
  return *this;
}

template<class T>
void
QcDatabaseSchema::add(const QList<T *> rows, bool save_relations)
{
  QcDatabaseTable & table = get_table_by_schema(T::schema());
  table.add(rows, save_relations);
}

template<class T>
void
QcDatabaseSchema::add(const QList<T> rows, bool save_relations)
{
  QList<T * > row_ptrs;
  for (auto & row : rows)
    row_ptrs << &row;

  QcDatabaseTable & table = get_table_by_schema(T::schema());
  table.add(row_ptrs, save_relations);
}

template<class T>
typename T::PtrList
QcDatabaseSchema::query(bool lazy_load)
{
  const QcSchema & schema = T::schema();
  QcDatabaseTable & table = get_table_by_schema(schema);
  QSqlQuery query = table.select();

  typename T::PtrList rows;
  while (query.next()) {
    typename T::Ptr row(query);
    row->set_database_schema(this);
    if (not lazy_load)
      row->load_relations();
    rows << row;
  }

  return rows;
}

template<class T>
typename T::Ptr
QcDatabaseSchema::query_by_id(int rowid, bool lazy_load)
{
  const QcSchema & schema = T::schema();
  QcDatabaseTable & table = get_table_by_schema(schema);
  typename T::Ptr row(table.select_by_id(rowid)); // Fixme: (this, ..., lazy_load)

  // register_row<T>(row); // Fixme: a template cannot be virtual, can only pass QcRowTraits
  // register_row(* row);
  // Fixme: non specific code, QcDatabaseTable has no link to database QcDatabaseSchema !
  row->set_database_schema(this); // Fixme: for all ???

  if (schema.has_foreign_keys()) {
    if (not lazy_load)
      row->load_relations();
  }

  return row;
}

template<class T>
typename T::PtrList
QcDatabaseSchema::query_by_foreign_key(const QString & foreign_key, const QVariant & value, bool lazy_load)
{
  QVariantHash kwargs;
  kwargs[foreign_key] = value;

  const QcSchema & schema = T::schema();
  QcDatabaseTable & table = get_table_by_schema(schema);
  QSqlQuery query = table.select(kwargs);

  typename T::PtrList rows;
  while (query.next()) {
    typename T::Ptr row(query);
    row->set_database_schema(this);
    if (not lazy_load)
      row->load_relations();
    rows << row;
  }

  return rows;
}

template<class T>
void
QcDatabaseSchema::update(T & row, bool save_relations)
{
  // Check primary key are set
  if (not row.can_update()) {
    qWarning().noquote() << QLatin1String("ORM: Cannot update on database:") << row;
    return;
  }

  QVariantHash kwargs = row.to_variant_hash_sql(true);
  QVariantHash where_kwargs = row.rowid_kwargs();

  QcDatabaseTable & table = get_table_by_schema(T::schema());
  table.update(kwargs, where_kwargs);

  // if (save_relations) {
  //   qInfo() << "Save relations of" << row;
  //   row.save_relations();
  // }
}

template<class T>
void
QcDatabaseSchema::delete_by_id(int rowid)
{
  QcDatabaseTable & table = get_table_by_schema(T::schema());
  table.delete_by_id(rowid);
}

/**************************************************************************************************/

#endif /* __DATABASE_SCHEMA_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
