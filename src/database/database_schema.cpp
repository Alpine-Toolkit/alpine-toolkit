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
    m_tables()
{}

QcDatabaseSchema::~QcDatabaseSchema()
{}

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
QcDatabaseSchema::register_table(const QString & name)
{
  m_tables[name] = QcDatabaseTable(&m_database, name);
  return m_tables[name];
}

QcDatabaseTable &
QcDatabaseSchema::register_table(const QcSchema & schema)
{
  const QString & name = schema.table_name(); // versus name()
  m_tables[name] = QcDatabaseTable(&m_database, schema);
  QcDatabaseTable & table = m_tables[name];
  if (not table.exists()) {
    table.create();
    m_database.commit();
  }
  return table;
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
