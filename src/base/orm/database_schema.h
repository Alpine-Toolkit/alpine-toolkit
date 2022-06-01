// -*- mode: c++ -*-
/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine Toolkit software.
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

#ifndef __DATABASE_SHEMA_H__
#define __DATABASE_SHEMA_H__

/**************************************************************************************************/

#include "orm/database.h"
#include "orm/database_row.h"
#include "orm/database_table.h"
#include "orm/schema.h"

#include <memory>

#include<QSharedPointer>
#include<QtDebug>

/**************************************************************************************************/

/*
class QoDatabaseSchemaCache : public QObject
{
  Q_OBJECT

public:
  QoDatabaseSchemaCache();
  ~QoDatabaseSchemaCache();

   void add(QoRowTraits * ptr);
   void remove(QoRowTraits * ptr);

public slots:
  void on_changed();

private:
  QMap<QoRowTraits *, QoRowTraits *> m_loaded_instances;
  QMap<QoRowTraits *, QoRowTraits *> m_modified_instances;
};
*/

/**************************************************************************************************/

class QoDatabaseSchema // : QObject
{
public:
  QoDatabaseSchema(QoDatabase & database); // register tables in subclass
  // T(const QList<QoSchema> & schemas);
  ~QoDatabaseSchema();

  QoDatabaseTable & register_table(const QString & name);
  QoDatabaseTable & register_table(const QoSchema & schema);

  QoDatabaseTable & get_table_by_name(const QString & name) { return *m_table_name_map[name]; }
  QoDatabaseTable & get_table_by_schema_id(int schema_id) { return *m_schema_map[schema_id]; }
  QoDatabaseTable & get_table_by_schema(const QoSchema & schema) { return get_table_by_schema_id(schema.schema_id()); }

  QoDatabaseTable & operator[](const QString & name) { return get_table_by_name(name); }

  // Add a row
  template<class T> void add(T & row, bool save_relations = true, bool commit = true);
  template<class T> void add_ptr(T & row_ptr, bool save_relations = true, bool commit = true);
  template<class T> QoDatabaseSchema & operator<<(QoRowTraits & row); // Fixme: save_relations, commit

  // Add rows
  template<class T> void add_row_ptrs(QList<T> & row_ptrs, bool commit = true); // , bool save_relations = true // Fixme: const ?
  template<class T> void add_rows(const QList<T *> & rows, bool commit = true); // , bool save_relations = true
  template<class T> void add_rows(const QList<T> & rows, bool commit = true); // , bool save_relations = true // Fixme: purpose ?

  template<class T> typename T::PtrList query(bool lazy_load = true);
  template<class T> typename T::Ptr query_by_id(int rowid, bool lazy_load = true);

  // template<class T> void register_row(typename T::Ptr & row) {}
  // virtual void register_row(QoRowTraits * row) = 0;

  template<class T>
  typename T::PtrList query_by_foreign_key(const QString & foreign_key, const QVariant & value, bool lazy_load = true);

  template<class T> void update(T & row, bool save_relations = true);
  template<class T> void update_ptr(T & row_ptr, bool save_relations = true) { update(*row_ptr); }

  template<class T> void delete_by_id(int rowid);

  // Derivative can implement:
  // QoDatabaseTable * table() { return m_table; }

private:
  QoDatabaseTable & register_table(QoDatabaseTable * table_ptr);

private:
  QoDatabase & m_database;
  // QList<std::unique_ptr<QoDatabaseTable>> m_tables;
  QList<QoDatabaseTable *> m_tables;
  QHash<QString, QoDatabaseTable *> m_table_name_map;
  QHash<int, QoDatabaseTable *> m_schema_map;
  // QoDatabaseTable * m_table;
};

/**************************************************************************************************/

#ifndef QC_MANUAL_INSTANTIATION
#include "database_schema.hxx"
#endif

/**************************************************************************************************/

#endif /* __DATABASE_SHEMA_H__ */
