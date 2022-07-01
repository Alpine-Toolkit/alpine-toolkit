/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#include "sqlite_database.h"
#include "alpine_toolkit.h"

#include <QFile>
#include <QSqlError>
#include <QtDebug>

/**************************************************************************************************/

QoSqliteDatabase::QoSqliteDatabase(const QString & sqlite_path, bool use_spatialite)
  : m_sqlite_path(sqlite_path),
    m_created(false),
    m_use_spatialite(use_spatialite)
{
  open();
}

QoSqliteDatabase::~QoSqliteDatabase()
{}

void
QoSqliteDatabase::open()
{
  m_created = not QFile(m_sqlite_path).exists();

  // Set the connection name to sqlite_path
  m_sql_flavour = SqlFlavour::SQLite;
  QString plugin = m_use_spatialite ? QLatin1String("QSQLITE-AT") : QLatin1String("QSQLITE");
  qATInfo() << "Open SQLite" << m_sqlite_path << plugin;
  m_database = QSqlDatabase::addDatabase(plugin, m_sqlite_path);
  m_database.setDatabaseName(m_sqlite_path);
  if (not m_database.open())
    qWarning() << m_database.lastError().text();

  if (m_use_spatialite)
    init_spatialite();
}

void
QoSqliteDatabase::init_spatialite()
{
  execute_query(QLatin1String("SELECT load_extension('mod_spatialite')"));

  QSqlQuery query = new_query();
  exec_and_check(query, QLatin1String("SELECT spatialite_version()"));
  query.first();
  qATInfo() << "Spatialite Version" << query.value(0).toString();

  if (m_created)
    execute_query(QLatin1String("SELECT InitSpatialMetaData(1);"));
}

bool
QoSqliteDatabase::move_database(const QString & new_path, bool commit) // unused
{
  m_database.commit();
  m_database.close();

  bool rc = QFile(m_sqlite_path).rename(new_path);
  if (rc)
    m_sqlite_path = new_path;

  open();

  return rc;
}
