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

#include "database.h"

#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QString
QcDatabaseTable::format_kwarg(const KeyValuePair & kwargs, const QString & separator)
{
  QString kwarg_string;
  int i = 0;
  // for (const auto & pair: kwargs) {
  for (const auto & field: kwargs.keys()) {
    if (i)
      kwarg_string += separator;
    kwarg_string += field + '=';
    QVariant variant = kwargs[field];
    bool is_string = variant.canConvert<QString>();
    if (is_string)
      kwarg_string += '"';
    kwarg_string += variant.toString();
    if (is_string)
      kwarg_string += '"';
    i++;
  }
  return kwarg_string;
}

QString
QcDatabaseTable::format_simple_where(const KeyValuePair & kwargs)
{
  return format_kwarg(kwargs, QStringLiteral(" AND "));
}

QcDatabaseTable::QcDatabaseTable()
  : m_database(nullptr),
    m_schema(),
    m_name()
{}

QcDatabaseTable::QcDatabaseTable(QcDatabase * database, const QString & name)
  : m_database(database),
    m_schema(name),
    m_name(name)
{}

QcDatabaseTable::QcDatabaseTable(QcDatabase * database, const QcSchema & schema)
  : m_database(database),
    m_schema(schema),
    m_name(schema.name())
{}

QcDatabaseTable::QcDatabaseTable(const QcDatabaseTable & other)
  : m_database(other.m_database),
    m_schema(other.m_schema),
    m_name(other.m_name)
{}

QcDatabaseTable::~QcDatabaseTable()
{}

QcDatabaseTable &
QcDatabaseTable::operator=(const QcDatabaseTable & other)
{
  if (this != &other) {
    m_database = other.m_database;
    m_schema = other.m_schema;
    m_name = other.m_name;
  }

  return *this;
}

bool
QcDatabaseTable::exists() const
{
  QStringList tables = m_database->database().tables(QSql::Tables);
  return tables.contains(m_name);
}

bool
QcDatabaseTable::create()
{
  QString sql_query = QLatin1String("CREATE TABLE ");
  sql_query += m_name;
  sql_query += QLatin1String(" (");
  QStringList sql_fields;
  for (const auto & field : m_schema.fields())
    sql_fields << field.to_sql_definition();
  sql_query += sql_fields.join(QLatin1String(", "));
  sql_query += ')';
  return m_database->execute_query(sql_query);
}

bool
QcDatabaseTable::drop()
{
  QString sql_query = QLatin1String("DROP TABLE ") + m_name;
  return m_database->execute_query(sql_query);
}


QSqlQuery
QcDatabaseTable::insert(const KeyValuePair & kwargs, bool commit_request)
{
  QSqlQuery query = m_database->new_query();
  QStringList fields = kwargs.keys();
  QString sql_query =
    QStringLiteral("INSERT INTO ") + m_name +
    QStringLiteral(" (") + fields.join(',') + QStringLiteral(") VALUES (");
  for (int i = 0; i < fields.size(); i++) {
    if (i > 0)
      sql_query += ',';
    sql_query += '?';
  }
  sql_query += ')';
  qInfo() << sql_query << kwargs;
  query.prepare(sql_query);

  for (const auto & value : kwargs.values())
    query.addBindValue(value);

  if (!query.exec())
    qWarning() << query.lastError().text();

  if (commit_request)
    m_database->commit();

  return query;
}

QSqlQuery
QcDatabaseTable::select(const QStringList & fields, const QString & where) const
{
  QSqlQuery query = m_database->new_query();
  QString sql_query = QStringLiteral("SELECT ") + fields.join(',') + QStringLiteral(" FROM ") + m_name;
  if (!where.isEmpty())
    sql_query += QStringLiteral(" WHERE ") + where;
  qInfo() << sql_query << fields;

  if (!query.exec(sql_query))
    qWarning() << query.lastError().text();

  return query;
}

QSqlRecord
QcDatabaseTable::select_one(const QStringList & fields, const QString & where) const
{
  QSqlQuery query = select(fields, where);
  QSqlRecord record;
  if (query.next()) {
    record = query.record();
    if (query.next())
      qWarning() << "More than one rows returned";
  } else
    qWarning() << "Any row";

  return record; // test with isEmpty()
}


QSqlQuery
QcDatabaseTable::update(const KeyValuePair & kwargs, const QString & where)
{
  QSqlQuery query = m_database->new_query();
  QString sql_query = QStringLiteral("UPDATE ") + m_name + QStringLiteral(" SET ") + format_kwarg(kwargs);
  if (!where.isEmpty())
    sql_query += QStringLiteral(" WHERE ") + where;
  qInfo() << sql_query << kwargs;

  if (!query.exec(sql_query))
    qWarning() << query.lastError().text();

  return query;
}

QSqlQuery
QcDatabaseTable::delete_row(const QString & where)
{
  QSqlQuery query = m_database->new_query();
  QString sql_query = QStringLiteral("DELETE FROM ") + m_name;
  if (!where.isEmpty())
    sql_query += QStringLiteral(" WHERE ") + where;
  qInfo() << sql_query;

  if (!query.exec(sql_query))
    qWarning() << query.lastError().text();

  return query;
}

/**************************************************************************************************/

QcDatabase::QcDatabase()
  : m_database(),
    m_tables()
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

QcDatabase::~QcDatabase()
{
  if (m_database.isValid())
    m_database.close();
}

QcDatabaseTable &
QcDatabase::register_table(const QString & name)
{
  m_tables[name] =  QcDatabaseTable(this, name);
  return m_tables[name];
}

QcDatabaseTable &
QcDatabase::register_table(const QcSchema & schema)
{
  const QString & name = schema.name();
  m_tables[name] = QcDatabaseTable(this, schema);
  QcDatabaseTable & table = m_tables[name];
  if (not table.exists()) {
    table.create();
    m_database.commit();
  }
  return table;
}

QSqlQuery
QcDatabase::prepare_query(const QString & sql_query)
{
  transaction();
  QSqlQuery query = new_query();
  query.prepare(sql_query);
  return query;
}

bool
QcDatabase::execute_query(const QString & sql_query)
{
  QSqlQuery query = new_query();
  if (!query.exec(sql_query)) {
    qWarning() << query.lastError().text();
    return false;
  } else
    return true;
}

bool
QcDatabase::execute_queries(const QStringList & sql_queries, bool commit_request)
{
  // Fixme: ok ?
  if (commit_request)
    transaction();

  QSqlQuery query = new_query();
  bool ok = true;
  for (const auto & sql_query : sql_queries)
    if (!query.exec(sql_query)) {
      ok = false;
      qWarning() << query.lastError().text();
    }

  if (commit_request)
    m_database.commit();

  return ok;
}

/**************************************************************************************************/

QcNetworkDatabase::QcNetworkDatabase()
{}

QcNetworkDatabase::~QcNetworkDatabase()
{}

void
QcNetworkDatabase::open(const QcDatabaseConnectionData & connection_data)
{
  m_database = QSqlDatabase::addDatabase(driver_name());
  m_database.setHostName(connection_data.host);
  m_database.setPort(connection_data.port);
  m_database.setDatabaseName(connection_data.database);
  m_database.setUserName(connection_data.user);
  m_database.setPassword(connection_data.password);
  if (!m_database.open())
    qWarning() << m_database.lastError().text();
}

bool
QcNetworkDatabase::create_extension(const QString & extension)
{
  // Fixme: PostresSQL
  QString sql_query = "CREATE EXTENSION IF NOT EXISTS " + extension + " WITH SCHEMA public;";
  return execute_query(sql_query);
}

/**************************************************************************************************/

QcSqliteDatabase::QcSqliteDatabase()
{}

QcSqliteDatabase::~QcSqliteDatabase()
{}

bool
QcSqliteDatabase::open(QString sqlite_path)
{
  bool created = !QFile(sqlite_path).exists();

  // Set the connection name to sqlite_path
  m_database = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"), sqlite_path);
  m_database.setDatabaseName(sqlite_path);
  if (!m_database.open())
    qWarning() << m_database.lastError().text();

  return created;
}

/**************************************************************************************************/

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
