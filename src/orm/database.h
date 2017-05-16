// -*- mode: c++ -*-

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

#ifndef __DATABASE_H__
#define __DATABASE_H__

/**************************************************************************************************/

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QStringList>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcDatabase
{
public:
  static bool exec_and_check_prepared_query(QSqlQuery & query);
  static bool exec_and_check(QSqlQuery & query, const QString & sql_query);

private:
  static void log_query_error_message(const QSqlQuery & query);

public:
  QcDatabase();
  virtual ~QcDatabase();

  QSqlDatabase & database () { return m_database; }

  bool transaction() { return m_database.transaction(); }
  bool commit() { return m_database.commit(); }

  QSqlQuery new_query() const { return QSqlQuery(m_database); }
  // QSqlQuery new_query(const QString & sql_query) const; { return QSqlQuery(sql_query, m_database); } // exec query

  QSqlQuery prepare_query(const QString & sql_query);

  bool execute_query(const QString & sql_query);
  bool execute_queries(const QStringList & sql_queries, bool commit = true);

protected: // for SQLite and Network subclasses
  QSqlDatabase m_database;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __DATABASE_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
