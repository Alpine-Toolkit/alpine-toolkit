/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
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
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "sqlite_database.h"

#include <QFile>
#include <QSqlError>
#include <QtDebug>

/**************************************************************************************************/

QcSqliteDatabase::QcSqliteDatabase(const QString & sqlite_path, bool use_spatialite)
  : m_sqlite_path(sqlite_path),
    m_created(false),
    m_use_spatialite(use_spatialite)
{
  open();
}

QcSqliteDatabase::~QcSqliteDatabase()
{}

void
QcSqliteDatabase::open()
{
  m_created = not QFile(m_sqlite_path).exists();

  // Set the connection name to sqlite_path
  m_sql_flavour = SqlFlavour::SQLite;
  QString plugin = m_use_spatialite ? QLatin1String("QSQLITE-AT") : QLatin1String("QSQLITE");
  qInfo() << "Open SQLite" << m_sqlite_path << plugin;
  m_database = QSqlDatabase::addDatabase(plugin, m_sqlite_path);
  m_database.setDatabaseName(m_sqlite_path);
  if (not m_database.open())
    qWarning() << m_database.lastError().text();

  if (m_use_spatialite)
    init_spatialite();
}

void
QcSqliteDatabase::init_spatialite()
{
  execute_query(QLatin1String("SELECT load_extension('mod_spatialite')"));

  QSqlQuery query = new_query();
  exec_and_check(query, QLatin1String("SELECT spatialite_version()"));
  query.first();
  qInfo() << "Spatialite Version" << query.value(0).toString();

  if (m_created)
    execute_query(QLatin1String("SELECT InitSpatialMetaData(1);"));
}

bool
QcSqliteDatabase::move_database(const QString & new_path, bool commit)
{
  m_database.commit();
  m_database.close();

  bool rc = QFile(m_sqlite_path).rename(new_path);
  if (rc)
    m_sqlite_path = new_path;

  open();

  return rc;
}
