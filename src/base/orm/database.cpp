/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "database.h"
#include "alpine_toolkit.h"

#include "database_query.h"

#include <QSqlDriver>
#include <QSqlError>
#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QoDatabase::QoDatabase()
  : m_database()
{}

QoDatabase::~QoDatabase()
{
  if (m_database.isValid())
    m_database.close();
}

void
QoDatabase::set_sql_flavour()
{
  QSqlDriver * driver = m_database.driver();

  switch(driver->dbmsType()) {
  case QSqlDriver::SQLite:
    m_sql_flavour = SqlFlavour::ANSI; // Fixme: -Wimplicit-fallthrough
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
QoDatabase::prepare_query(const QString & sql_query)
{
  transaction();
  QSqlQuery query = new_query();
  query.prepare(sql_query);
  return query;
}

QSqlQuery
QoDatabase::prepare_query(const QoSqlQuery & sql_query)
{
  return prepare_query(sql_query.to_sql()); // Fixme: QString cast ?
}

void
QoDatabase::log_query_error_message(const QSqlQuery & query)
{
  qATCritical().noquote()
    << QLatin1String("SQL error on") << query.lastQuery()
    << QLatin1String(": ") << query.lastError().text();
}

bool
QoDatabase::exec_and_check_prepared_query(QSqlQuery & query)
{
  qATInfo().noquote() << "Exec SQL Query:" << query.lastQuery();
  if (!query.exec()) {
    log_query_error_message(query);
    return false;
  } else
    return true;
}

bool
QoDatabase::exec_and_check(QSqlQuery & query, const QString & sql_query)
{
  qATInfo().noquote() << "Exec SQL Query:" << sql_query;
  if (!query.exec(sql_query)) {
    log_query_error_message(query);
    return false;
  } else
    return true;
}

bool
QoDatabase::exec_and_check(QSqlQuery & query, const QoSqlQuery & sql_query)
{
  return exec_and_check(query, sql_query.to_sql());
}

bool
QoDatabase::execute_query(const QString & sql_query)
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
QoDatabase::execute_query(const QoSqlQuery & sql_query)
{
  return execute_query(sql_query.to_sql());
}

bool
QoDatabase::execute_queries(const QStringList & sql_queries, bool commit_request)
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
