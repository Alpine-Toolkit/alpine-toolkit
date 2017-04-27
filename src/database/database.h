// -*- mode: c++ -*-

/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
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
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __DATABASE_H__
#define __DATABASE_H__

/**************************************************************************************************/

#include <QByteArray>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVariantHash>

#include "database/schema.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcSqlRecordWrapper
{
public:
  inline QcSqlRecordWrapper(const QSqlRecord & record)
    : m_record(record)
  {}

  inline const QSqlRecord & record() const { return m_record; }

  inline bool is_empty() const { return m_record.isEmpty(); }
  inline bool is_not_empty() const { return not is_empty(); }

  inline int to_int(int position = 0) const {
    return m_record.value(position).toInt();
  }

  inline QByteArray to_byte_array(int position = 0) const {
    return m_record.value(position).toByteArray();
  }

  inline QString to_string(int position = 0) const {
    return m_record.value(position).toString();
  }

private:
  const QSqlRecord & m_record;
};

// Fixme: same QSqlQuery ?

/**************************************************************************************************/

class QcDatabase;

class QcDatabaseTable
{
public:
  static QString format_prepare(int number_of_fields);
  static QString format_prepare_update(const QStringList & fields);
  static QString format_kwarg(const QVariantHash & kwargs, const QString & separator = QStringLiteral(","));
  static QString format_simple_where(const QVariantHash & kwargs);

public:
  QcDatabaseTable();
  QcDatabaseTable(QcDatabase * database, const QString & name);
  QcDatabaseTable(QcDatabase * database, const QcSchema & schema);
  QcDatabaseTable(const QcDatabaseTable & other);
  ~QcDatabaseTable();

  QcDatabaseTable & operator=(const QcDatabaseTable & other);

  inline QcDatabase * database() { return m_database; }
  inline const QcSchema & schema() { return m_schema; }
  inline const QString & name() { return m_name; } // m_schema.name()

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
  QSqlRecord select_one(const QString & where = QString()) const {
    return select_one(QStringList(QLatin1String("*")), where);
  }
  QSqlRecord select_one(const QVariantHash & kwargs) const  {
    return select_one(QStringList(QLatin1String("*")), format_simple_where(kwargs));
  }
  // select_one(const QList<QcSchemaField> & fields, const QVariantHash & kwargs) // -> success/error callback, return QList<QVariant> ?

  QSqlQuery prepare_complete_insert(int number_of_fields);
  QSqlQuery complete_insert(const QVariantList & variants, bool commit = false);
  QSqlQuery prepare_insert(const QStringList & fields);

  QSqlQuery insert(const QVariantHash & kwargs, bool commit = false);

  QSqlQuery prepare_update(const QStringList & fields, const QString & where);
  QSqlQuery update(const QVariantHash & kwargs, const QString & where = QString());
  QSqlQuery update(const QVariantHash & kwargs, const QVariantHash & where_kwargs) {
    return update(kwargs, format_simple_where(where_kwargs));
  }

  QSqlQuery delete_row(const QString & where = QString());
  QSqlQuery delete_row(const QVariantHash & kwargs) {
    return delete_row(format_simple_where(kwargs));
  }

private:
  void bind_and_exec(QSqlQuery & query, const QVariantHash & kwargs, bool commit);

private:
  QcDatabase * m_database;
  QcSchema m_schema;
  QString m_name;
};

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
  // QcDatabase(const QList<QcSchema> & schemas);
  virtual ~QcDatabase();

  inline QSqlDatabase & database () { return m_database; }

  QcDatabaseTable & register_table(const QString & name);
  QcDatabaseTable & register_table(const QcSchema & schema);

  QcDatabaseTable & table(const QString & name) { return m_tables[name]; } // Fixme: wrong name ?
  QcDatabaseTable & operator[](const QString & name) { return m_tables[name]; }

  inline bool transaction() { return m_database.transaction(); }
  inline bool commit() { return m_database.commit(); }

  inline QSqlQuery new_query() const { return QSqlQuery(m_database); }
  // inline QSqlQuery new_query(const QString & sql_query) const; { return QSqlQuery(sql_query, m_database); } // exec query

  QSqlQuery prepare_query(const QString & sql_query);

  bool execute_query(const QString & sql_query);
  bool execute_queries(const QStringList & sql_queries, bool commit = true);

protected:
  QSqlDatabase m_database;
  QHash<QString, QcDatabaseTable> m_tables; // => QcDatabaseTable() => QcDatabase *
};

/**************************************************************************************************/

struct QcDatabaseConnectionData
{
  QString host;
  int port;
  QString database;
  QString user;
  QString password;
};

/**************************************************************************************************/

class QcNetworkDatabase : public QcDatabase
{
public:
  QcNetworkDatabase();
  virtual ~QcNetworkDatabase();

  void open(const QcDatabaseConnectionData & connection_data);

  bool create_extension(const QString & extension);

  virtual QString driver_name() const = 0;
};

/**************************************************************************************************/

class QcSqliteDatabase : public QcDatabase
{
public:
  QcSqliteDatabase(); // Fixme: const QString & path ???
  virtual ~QcSqliteDatabase();

  bool open(const QString & sqlite_path);
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
