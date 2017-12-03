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

#include "database_schema.h"
#include "alpine_toolkit.h"

#include <QtDebug>

/**************************************************************************************************/

QoDatabaseSchema::QoDatabaseSchema(QoDatabase & database)
  : m_database(database),
    m_tables(),
    m_table_name_map(),
    m_schema_map()
{}

QoDatabaseSchema::~QoDatabaseSchema()
{
  for (auto * table_ptr : m_tables)
    delete table_ptr;
}

// Database must be opened before to create table !
/*
QoDatabase::QoDatabase(const QList<QoSchema> & schemas)
  : QoDatabase()
{
  for (const auto & schema : schemas)
    register_table(schema);
}
*/

QoDatabaseTable &
QoDatabaseSchema::register_table(QoDatabaseTable * table_ptr)
{
  // m_tables << std::unique_ptr<QoDatabaseTable>(table_ptr);
  m_tables << table_ptr; // Fixme:
  m_table_name_map[table_ptr->name()] = table_ptr;
  m_schema_map[table_ptr->schema().schema_id()] = table_ptr;
  return *table_ptr;
}

QoDatabaseTable &
QoDatabaseSchema::register_table(const QString & name)
{
  return register_table(new QoDatabaseTable(&m_database, name));
}

QoDatabaseTable &
QoDatabaseSchema::register_table(const QoSchema & schema)
{
  QoDatabaseTable & table = register_table(new QoDatabaseTable(&m_database, schema));
  if (not table.exists()) {
    table.create();
    m_database.commit();
  }
  return table;
}
