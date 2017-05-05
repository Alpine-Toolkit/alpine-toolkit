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

#ifndef __DATABASE_SHEMA_H__
#define __DATABASE_SHEMA_H__

/**************************************************************************************************/

#include "database/database.h"
#include "database/database_row.h"
#include "database/database_table.h"
#include "database/schema.h"

#include <memory>

#include<QSharedPointer>
#include<QtDebug>

/**************************************************************************************************/

class QcDatabaseSchema // : QObject
{
public:
  QcDatabaseSchema(QcDatabase & database); // register tables in subclass
  // T(const QList<QcSchema> & schemas);
  ~QcDatabaseSchema();

  QcDatabaseTable & register_table(const QString & name);
  QcDatabaseTable & register_table(const QcSchema & schema);

  QcDatabaseTable & get_table_by_name(const QString & name) { return *m_table_name_map[name]; }
  QcDatabaseTable & get_table_by_schema_id(int schema_id) { return *m_schema_map[schema_id]; }
  QcDatabaseTable & get_table_by_schema(const QcSchema & schema) { return get_table_by_schema_id(schema.schema_id()); }

  QcDatabaseTable & operator[](const QString & name) { return get_table_by_name(name); }

  void add(QcRowTraits & row);

  template<class T>
  void add(T & row) {
    QcDatabaseTable & table = get_table_by_schema(T::schema());
    table.add(row);
  }

  template<class T>
  QSharedPointer<T> query_by_id(int rowid, bool lazy_load = true) {
    const QcSchema & schema = T::schema();
    QcDatabaseTable & table = get_table_by_schema(schema);
    T * row = new T(table.select_by_id(rowid)); // Fixme: (this, ..., lazy_load)
    // Fixme: non specific code
    row->set_database_schema(this); // Fixme: for all ???
    if (schema.has_foreign_keys()) {
      if (not lazy_load)
        row->load_foreign_keys();
    }
    return QSharedPointer<T>(row);
  }

  // Derivative can implement:
  // QcDatabaseTable * table() { return m_table; }

private:
  QcDatabaseTable & register_table(QcDatabaseTable * table_ptr);

private:
  QcDatabase & m_database;
  // QList<std::unique_ptr<QcDatabaseTable>> m_tables;
  QList<QcDatabaseTable *> m_tables;
  QHash<QString, QcDatabaseTable *> m_table_name_map;
  QHash<int, QcDatabaseTable *> m_schema_map;
  // QcDatabaseTable * m_table;
};

/**************************************************************************************************/

#endif /* __DATABASE_SHEMA_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
