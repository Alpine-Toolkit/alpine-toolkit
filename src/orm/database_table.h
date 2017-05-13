// -*- mode: c++ -*-
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

#ifndef __DATABASE_TABLE_H__
#define __DATABASE_TABLE_H__

/**************************************************************************************************/

#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantHash>

#include "orm/schema.h"
#include "orm/database_row.h"

/**************************************************************************************************/

class QcDatabase;

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
  const QcSchema & schema() { return m_schema; }
  const QString & name() { return m_name; } // m_schema.name()

  bool exists() const;
  bool create();
  bool drop();

  QSqlQuery select(const QStringList & fields, const QString & where = QString()) const;
  QSqlQuery select(const QStringList & fields, const QVariantHash & kwargs) const {
    return select(fields, format_simple_where(kwargs));
  }
  QSqlQuery select(const QString & where = QString()) const {
    return select(QStringList(QLatin1String("*")), where);
  }
  QSqlQuery select(const QVariantHash & kwargs) const {
    return select(QStringList(QLatin1String("*")), format_simple_where(kwargs));
  }

  QSqlRecord select_one(const QStringList & fields, const QString & where = QString()) const;
  QSqlRecord select_one(const QStringList & fields, const QVariantHash & kwargs) const {
    return select_one(fields, format_simple_where(kwargs));
  }
  QSqlRecord select_one(const QString & where = QString()) const;
  QSqlRecord select_one(const QVariantHash & kwargs) const  {
    return select_one(format_simple_where(kwargs));
  }
  QSqlRecord select_by_id(int id) const  {
    return select_one(kwarg_for_id(id));
  }
  // select_one(const QList<QcSchemaField> & fields, const QVariantHash & kwargs) // -> success/error callback, return QList<QVariant> ?

  QSqlQuery join(JoinType join_type, const QcDatabaseTable & table2, const QString & where) const;

  QSqlQuery complete_insert(const QVariantList & variants, bool commit = true);
  void add(QcRowTraits & row, bool commit = true);
  void add(const QList<QcRowTraits *> rows, bool commit = true);

  QSqlQuery insert(const QVariantHash & kwargs, bool commit = true);

  QSqlQuery update(const QVariantHash & kwargs, const QString & where = QString());
  QSqlQuery update(const QVariantHash & kwargs, const QVariantHash & where_kwargs) {
    return update(kwargs, format_simple_where(where_kwargs));
  }

  QSqlQuery delete_row(const QString & where = QString());
  QSqlQuery delete_row(const QVariantHash & kwargs) {
    return delete_row(format_simple_where(kwargs));
  }
  QSqlQuery delete_by_id(int id)  {
    return delete_row(kwarg_for_id(id));
  }

private:
  static QVariantHash kwarg_for_id(int id) { return {{QLatin1String("rowid"), id}}; }
  void commit();
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
