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

#include "database_schema.h"

#include <QtDebug>

/**************************************************************************************************/

QcDatabaseSchema::QcDatabaseSchema(QcDatabase & database)
  : m_database(database),
    m_tables(),
    m_table_name_map(),
    m_schema_map()
{}

QcDatabaseSchema::~QcDatabaseSchema()
{
  for (auto * table_ptr : m_tables)
    delete table_ptr;
}

// Database must be opened before to create table !
/*
QcDatabase::QcDatabase(const QList<QcSchema> & schemas)
  : QcDatabase()
{
  for (const auto & schema : schemas)
    register_table(schema);
}
*/

QcDatabaseTable &
QcDatabaseSchema::register_table(QcDatabaseTable * table_ptr)
{
  // m_tables << std::unique_ptr<QcDatabaseTable>(table_ptr);
  m_tables << table_ptr; // Fixme:
  m_table_name_map[table_ptr->name()] = table_ptr;
  m_schema_map[table_ptr->schema().schema_id()] = table_ptr;
  return *table_ptr;
}

QcDatabaseTable &
QcDatabaseSchema::register_table(const QString & name)
{
  return register_table(new QcDatabaseTable(&m_database, name));
}

QcDatabaseTable &
QcDatabaseSchema::register_table(const QcSchema & schema)
{
  QcDatabaseTable & table = register_table(new QcDatabaseTable(&m_database, schema));
  if (not table.exists()) {
    table.create();
    m_database.commit();
  }
  return table;
}

void
QcDatabaseSchema::add(QcRowTraits & row)
{
  int schema_id = row.schema_id();
  QcDatabaseTable & table = get_table_by_schema_id(schema_id);
  QSqlQuery query = table.complete_insert(row.to_variant_list_sql());
  // QcRowWithId * row_ptr = dynamic_cast<QcRowWithId *>(row);
  int rowid = query.lastInsertId().toInt();
  qInfo() << "add" << schema_id << table.name() << rowid;
  row.set_insert_id(rowid);
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
