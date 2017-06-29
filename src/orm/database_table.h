// -*- mode: c++ -*-
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

#ifndef __DATABASE_TABLE_H__
#define __DATABASE_TABLE_H__

/**************************************************************************************************/

// #include "orm/database_query.h"
#include "orm/database_row.h"
#include "orm/schema.h"
#include "orm/sql_flavour.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantHash>

/**************************************************************************************************/

class QcDatabase;
class QcSqlQuery;

/**************************************************************************************************/

class QcDatabaseTable
{
public:
  static QString format_prepare(int number_of_fields);
  static QString format_prepare_update(const QStringList & fields);
  static QString format_kwarg(const QVariantHash & kwargs, const QString & separator = QStringLiteral(","));
  static QString format_simple_where(const QVariantHash & kwargs);

  enum class JoinType {
    InnerJoin,
    LeftJoin,
    RightJoin,
    FullJoin,
    SelfJoin,
  };

public:
  QcDatabaseTable();
  QcDatabaseTable(QcDatabase * database, const QString & name);
  QcDatabaseTable(QcDatabase * database, const QcSchema & schema);
  QcDatabaseTable(const QcDatabaseTable & other);
  ~QcDatabaseTable();

  QcDatabaseTable & operator=(const QcDatabaseTable & other);

  QcDatabase * database() { return m_database; }
  SqlFlavour sql_flavour() const; // QcDatabase is incomplete
  const QcSchema & schema() { return m_schema; }
  const QString & name() { return m_name; } // m_schema.name()

  bool exists() const;
  bool create();
  bool drop();

  QcSqlQuery sql_query();
  QSqlQuery exec(const QcSqlQuery & query); // Fixme: execute_query

  QSqlQuery select_all(); // const
  QSqlQuery select(const QStringList & fields, const QString & where = QString()) const;
  QSqlQuery select(const QString & field, const QString & where = QString()) const {
    return select(QStringList(field), where);
  }
  QSqlQuery select(const QStringList & fields, const QVariantHash & kwargs) const {
    return select(fields, format_simple_where(kwargs));
  }
  QSqlQuery select(const QString & field, const QVariantHash & kwargs) const {
    return select(QStringList(field), format_simple_where(kwargs));
  }
  QSqlQuery select_where(const QString & where = QString()) const {
    return select(QStringList(QLatin1String("*")), where);
  }
  QSqlQuery select_where(const QVariantHash & kwargs) const {
    return select(QStringList(QLatin1String("*")), format_simple_where(kwargs));
  }

  QSqlRecord select_one(const QStringList & fields, const QString & where = QString()) const;
  QSqlRecord select_one(const QString & field, const QString & where = QString()) const {
    return select_one(QStringList(field), where);
  }
  QSqlRecord select_one(const QStringList & fields, const QVariantHash & kwargs) const {
    return select_one(fields, format_simple_where(kwargs));
  }
  QSqlRecord select_one(const QString & field, const QVariantHash & kwargs) const {
    return select_one(QStringList(field), format_simple_where(kwargs));
  }
  QSqlRecord select_one_where(const QString & where = QString()) const;
  QSqlRecord select_one_where(const QVariantHash & kwargs) const  {
    return select_one_where(format_simple_where(kwargs));
  }
  QSqlRecord select_by_id(int rowid) const  {
    return select_one_where(kwarg_for_id(rowid));
  }
  // select_one(const QList<QcSchemaField> & fields, const QVariantHash & kwargs) // -> success/error callback, return QList<QVariant> ?

  int count(const QString & where = QString()) const;
  int count(const QVariantHash & kwargs) const {
    return count(format_simple_where(kwargs));
  }
  int rowid(const QString & where = QString()) const;
  int rowid(const QVariantHash & kwargs) const {
    return rowid(format_simple_where(kwargs));
  }

  QSqlQuery join(JoinType join_type, const QcDatabaseTable & table2, const QString & where) const;

  // Add a complete row
  QSqlQuery complete_insert(const QVariantList & variants, bool commit = true);
  // Add a row or rows
  void add(QcRowTraits & row, bool commit = true);
  void add(const QList<QcRowTraits *> & rows, bool commit = true);

  QSqlQuery insert(const QVariantHash & kwargs, bool commit = true);

  QSqlQuery update(const QVariantHash & kwargs, const QString & where = QString());
  QSqlQuery update(const QVariantHash & kwargs, const QVariantHash & where_kwargs) {
    return update(kwargs, format_simple_where(where_kwargs));
  }
  QSqlQuery update_by_id(int rowid, const QVariantHash & kwargs) {
    return update(kwargs, kwarg_for_id(rowid));
  }

  QSqlQuery delete_row(const QString & where = QString());
  QSqlQuery delete_row(const QVariantHash & kwargs) {
    return delete_row(format_simple_where(kwargs));
  }
  QSqlQuery delete_by_id(int rowid)  {
    return delete_row(kwarg_for_id(rowid));
  }

private:
  static QVariantHash kwarg_for_id(int rowid) { return {{QLatin1String("rowid"), rowid}}; }
  void commit();
  QSqlQuery prepare_complete_insert();
  QSqlQuery prepare_complete_insert(int number_of_fields);
  QSqlQuery prepare_complete_insert(const QStringList & fields);
  QSqlQuery prepare_insert(const QStringList & fields);
  QSqlQuery prepare_update(const QStringList & fields, const QString & where);
  void bind_and_exec(QSqlQuery & query, const QVariantHash & kwargs, bool commit);

private:
  QcDatabase * m_database = nullptr; // ptr for default ctor
  QcSchema m_schema;
  QString m_name;
};

/**************************************************************************************************/

#endif /* __DATABASE_TABLE_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
