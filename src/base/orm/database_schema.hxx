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

#include "database_schema.h" // for checker
#include "alpine_toolkit.h"

/**************************************************************************************************/

#ifndef __DATABASE_SCHEMA_H__
#define __DATABASE_SCHEMA_H__

/**************************************************************************************************/

template<class T>
void
QoDatabaseSchema::add(T & row, bool save_relations, bool commit)
{
  // Check foreign keys are set
  if (not row.can_save()) {
    qWarning().noquote() << QLatin1String("ORM: Cannot save on database:") << row;
    return;
  }

  QoDatabaseTable & table = get_table_by_schema(T::schema());
  table.add(row, commit); // call set_insert_id

  // Fixme: if error ?
  row.set_database_schema(this);

  if (save_relations) {
    qATInfo() << "Save relations of" << row;
    row.save_relations();
  }
}

template<class T>
void
QoDatabaseSchema::add_ptr(T & row_ptr, bool save_relations, bool commit)
{
  add(*row_ptr, save_relations, commit);
}

template<class T>
QoDatabaseSchema &
QoDatabaseSchema::operator<<(QoRowTraits & row)
{
  add(row); // Fixme: save_relations, commit
  return *this;
}

template<class T>
void
QoDatabaseSchema::add_row_ptrs(QList<T> & row_ptrs, bool commit) // Fixme: const
{
  // Fixme: more efficient way ? base Ptr class ?
  QList<QoRowTraits*> rows;
  for (auto & row : row_ptrs)
    rows << row.data();

  QoDatabaseTable & table = get_table_by_schema(T::Class::schema());
  table.add(rows, commit);

  for (auto & row : row_ptrs)
    row->set_database_schema(this);
}

template<class T>
void
QoDatabaseSchema::add_rows(const QList<T *> & rows, bool commit)
{
  // Fixme:
  QList<QoRowTraits*> _rows;
  for (auto * row : rows)
    _rows << row;
  // error: invalid cast from type ‘const QList<Refuge*>’ to type ‘const QList<QoRowTraits*>’
  // reinterpret_cast<const QList<QoRowTraits*> >(rows)
  // http://en.cppreference.com/w/cpp/algorithm/transform

  QoDatabaseTable & table = get_table_by_schema(T::schema());
  table.add(_rows, commit);
}

template<class T>
void
QoDatabaseSchema::add_rows(const QList<T> & rows, bool commit)
{
  QList<T * > row_ptrs;
  for (auto & row : rows)
    row_ptrs << &row;

  add(row_ptrs, commit);
}

template<class T>
typename T::PtrList
QoDatabaseSchema::query(bool lazy_load)
{
  const QoSchema & schema = T::schema();
  QoDatabaseTable & table = get_table_by_schema(schema);

  // Fixme: for test
  QSqlQuery query;
  if (schema.has_sql_value_ctor())
    query = table.select_all();
  else
    query = table.select_where();

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
QoDatabaseSchema::query_by_id(int rowid, bool lazy_load)
{
  const QoSchema & schema = T::schema();
  QoDatabaseTable & table = get_table_by_schema(schema);
  typename T::Ptr row(table.select_by_id(rowid)); // Fixme: (this, ..., lazy_load)

  // register_row<T>(row); // Fixme: a template cannot be virtual, can only pass QoRowTraits
  // register_row(* row);
  // Fixme: non specific code, QoDatabaseTable has no link to database QoDatabaseSchema !
  row->set_database_schema(this); // Fixme: for all ???

  if (schema.has_foreign_keys()) {
    if (not lazy_load)
      row->load_relations();
  }

  return row;
}

template<class T>
typename T::PtrList
QoDatabaseSchema::query_by_foreign_key(const QString & foreign_key, const QVariant & value, bool lazy_load)
{
  QVariantHash kwargs;
  kwargs[foreign_key] = value;

  const QoSchema & schema = T::schema();
  QoDatabaseTable & table = get_table_by_schema(schema);
  QSqlQuery query = table.select_where(kwargs);

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
QoDatabaseSchema::update(T & row, bool save_relations)
{
  // Check primary key are set
  if (not row.can_update()) {
    qWarning().noquote() << QLatin1String("ORM: Cannot update on database:") << row;
    return;
  }

  QVariantHash kwargs = row.to_variant_hash_sql(true);
  QVariantHash where_kwargs = row.rowid_kwargs();

  QoDatabaseTable & table = get_table_by_schema(T::schema());
  table.update(kwargs, where_kwargs);

  // if (save_relations) {
  //   qATInfo() << "Save relations of" << row;
  //   row.save_relations();
  // }
}

template<class T>
void
QoDatabaseSchema::delete_by_id(int rowid)
{
  QoDatabaseTable & table = get_table_by_schema(T::schema());
  table.delete_by_id(rowid);
}

/**************************************************************************************************/

#endif /* __DATABASE_SCHEMA_H__ */
