// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __DATABASE_H__
#define __DATABASE_H__

/**************************************************************************************************/

// #include "orm/database_query.h"
#include "orm/sql_flavour.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QStringList>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QoSqlQuery;

/**************************************************************************************************/

class QoDatabase
{
public:
  // Fixme: why pass QSqlQuery ???
  static bool exec_and_check_prepared_query(QSqlQuery & query);
  static bool exec_and_check(QSqlQuery & query, const QString & sql_query);
  static bool exec_and_check(QSqlQuery & query, const QoSqlQuery & sql_query);

private:
  static void log_query_error_message(const QSqlQuery & query);

public:
  QoDatabase();
  virtual ~QoDatabase();

  QSqlDatabase & database () { return m_database; }

  SqlFlavour sql_flavour() const { return m_sql_flavour; }

  bool transaction() { return m_database.transaction(); }
  bool commit() { return m_database.commit(); }

  QSqlQuery new_query() const { return QSqlQuery(m_database); }
  // QSqlQuery new_query(const QString & sql_query) const; { return QSqlQuery(sql_query, m_database); } // exec query

  QSqlQuery prepare_query(const QString & sql_query);
  QSqlQuery prepare_query(const QoSqlQuery & sql_query);

  bool execute_query(const QString & sql_query);
  bool execute_query(const QoSqlQuery & sql_query);
  bool execute_queries(const QStringList & sql_queries, bool commit = true);

protected:
  void set_sql_flavour();

protected: // for SQLite and Network subclasses
  QSqlDatabase m_database;
  SqlFlavour m_sql_flavour = SqlFlavour::ANSI;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __DATABASE_H__ */
