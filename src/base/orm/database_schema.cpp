/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
