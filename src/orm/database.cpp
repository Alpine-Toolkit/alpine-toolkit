/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the QtCarto library.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $ALPINE_TOOLKIT_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include "database.h"

#include "database_query.h"

#include <QSqlDriver>
#include <QSqlError>
#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QcDatabase::QcDatabase()
  : m_database()
{}

QcDatabase::~QcDatabase()
{
  if (m_database.isValid())
    m_database.close();
}

void
QcDatabase::set_sql_flavour()
{
  QSqlDriver * driver = m_database.driver();

  switch(driver->dbmsType()) {
  case QSqlDriver::SQLite:
    m_sql_flavour = SqlFlavour::ANSI;
  case QSqlDriver::PostgreSQL:
    m_sql_flavour = SqlFlavour::PostgreSQL;
  case QSqlDriver::MySqlServer:
    m_sql_flavour = SqlFlavour::MySQL;
  case QSqlDriver::MSSqlServer:
    m_sql_flavour = SqlFlavour::SQL_Server;
  case QSqlDriver::Oracle:
    m_sql_flavour = SqlFlavour::Oracle;
  case QSqlDriver::DB2:
    m_sql_flavour = SqlFlavour::DB2;
  case QSqlDriver::UnknownDbms:
  case QSqlDriver::Interbase:
  case QSqlDriver::Sybase:
    m_sql_flavour = SqlFlavour::ANSI;
  }
}

QSqlQuery
QcDatabase::prepare_query(const QString & sql_query)
{
  transaction();
  QSqlQuery query = new_query();
  query.prepare(sql_query);
  return query;
}

QSqlQuery
QcDatabase::prepare_query(const QcSqlQuery & sql_query)
{
  return prepare_query(sql_query.to_sql()); // Fixme: QString cast ?
}

void
QcDatabase::log_query_error_message(const QSqlQuery & query)
{
  qCritical().noquote()
    << QLatin1String("SQL error on") << query.lastQuery()
    << QLatin1String(": ") << query.lastError().text();
}

bool
QcDatabase::exec_and_check_prepared_query(QSqlQuery & query)
{
  qInfo().noquote() << "Exec SQL Query:" << query.lastQuery();
  if (!query.exec()) {
    log_query_error_message(query);
    return false;
  } else
    return true;
}

bool
QcDatabase::exec_and_check(QSqlQuery & query, const QString & sql_query)
{
  qInfo().noquote() << "Exec SQL Query:" << sql_query;
  if (!query.exec(sql_query)) {
    log_query_error_message(query);
    return false;
  } else
    return true;
}

bool
QcDatabase::exec_and_check(QSqlQuery & query, const QcSqlQuery & sql_query)
{
  return exec_and_check(query, sql_query.to_sql());
}

bool
QcDatabase::execute_query(const QString & sql_query)
{
  // QSqlQuery query = QSqlQuery(sql_query, m_database);
  // if (query.lastError().type() == QSqlError::NoError)
  //   return true;
  // else {
  //   log_query_error_message(query);
  //   return false;
  // }
  QSqlQuery query = new_query();
  return exec_and_check(query, sql_query);
}

bool
QcDatabase::execute_query(const QcSqlQuery & sql_query)
{
  return execute_query(sql_query.to_sql());
}

bool
QcDatabase::execute_queries(const QStringList & sql_queries, bool commit_request)
{
  // Fixme: ok ?
  if (commit_request)
    transaction();

  bool ok = true;
  for (const auto & sql_query : sql_queries)
    if (not execute_query(sql_query))
      ok = false;

  if (commit_request)
    m_database.commit();

  return ok;
}

/**************************************************************************************************/

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
