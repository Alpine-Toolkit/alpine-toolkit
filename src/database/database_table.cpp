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

#include "database_table.h"

#include "database.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>

/**************************************************************************************************/

QString
QcDatabaseTable::format_prepare(int number_of_fields)
{
  QString string;
  for (int i = 0; i < number_of_fields; i++) {
    if (i > 0)
      string += ',';
    string += '?';
  }
  return string;
}

QString
QcDatabaseTable::format_prepare_update(const QStringList & fields)
{
  // QStringList string_list;
  // for (const auto & field : fields)
  //   string_list << field + QLatin1String("= ?")
  // return fields.join(',');
  QString string;
  int i = 0;
  for (const auto & field : fields) {
    if (i++)
      string += ',';
    string += field + QLatin1String("=?");
  }
  return string;
}

QString
QcDatabaseTable::format_kwarg(const QVariantHash & kwargs, const QString & separator)
{
  QString kwarg_string;
  int i = 0;
  // for (const auto & pair: kwargs) {
  for (const auto & field: kwargs.keys()) {
    if (i++)
      kwarg_string += separator;
    kwarg_string += field + '=';
    QVariant variant = kwargs[field];
    bool is_string = variant.canConvert<QString>();
    if (is_string)
      kwarg_string += '"';
    kwarg_string += variant.toString();
    if (is_string)
      kwarg_string += '"';
  }
  return kwarg_string;
}

QString
QcDatabaseTable::format_simple_where(const QVariantHash & kwargs)
{
  return format_kwarg(kwargs, QLatin1String(" AND "));
}

QcDatabaseTable::QcDatabaseTable()
  : m_database(nullptr),
    m_schema(),
    m_name()
{}

QcDatabaseTable::QcDatabaseTable(QcDatabase * database, const QString & name)
  : m_database(database),
    m_schema(name, name),
    m_name(name)
{}

QcDatabaseTable::QcDatabaseTable(QcDatabase * database, const QcSchema & schema)
  : m_database(database),
    m_schema(schema),
    m_name(schema.table_name())
{}

QcDatabaseTable::QcDatabaseTable(const QcDatabaseTable & other)
  : m_database(other.m_database),
    m_schema(other.m_schema),
    m_name(other.m_name)
{}

QcDatabaseTable::~QcDatabaseTable()
{
  qInfo() << "~QcDatabaseTable";
}

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
  QString sql_query = m_schema.to_sql_definition();
  return m_database->execute_query(sql_query);
}

bool
QcDatabaseTable::drop()
{
  QString sql_query = QLatin1String("DROP TABLE ") + m_name;
  return m_database->execute_query(sql_query);
}

QSqlQuery
QcDatabaseTable::prepare_complete_insert(int number_of_fields)
{
  QSqlQuery query = m_database->new_query();
  QString sql_query =
    QLatin1String("INSERT INTO ") + m_name + QLatin1String(" VALUES (") + format_prepare(number_of_fields) + ')';
  query.prepare(sql_query);

  return query;
}

QSqlQuery
QcDatabaseTable::complete_insert(const QVariantList & variants, bool commit)
{
  QSqlQuery query = prepare_complete_insert(variants.size());
  qInfo() << query.lastQuery() << variants;

  for (const auto & value : variants)
    query.addBindValue(value);

  // Fixme: namesapce ???
  if (QcDatabase::exec_and_check_prepared_query(query) and commit)
    m_database->commit();

  return query;
}

void
QcDatabaseTable::add(QcRowTraits & row)
{
  QSqlQuery query = complete_insert(row.to_variant_list_sql());
  int rowid = query.lastInsertId().toInt();
  // To only set rowid for such table, we must know the type at run time
  //   e.g. dynamic_cast<QcRowWithId *>(row);
  row.set_insert_id(rowid);
}

void
QcDatabaseTable::bind_and_exec(QSqlQuery & query, const QVariantHash & kwargs, bool commit)
{
  // qInfo() << "Bind on" << query.lastQuery() << kwargs;

  for (const auto & value : kwargs.values())
    query.addBindValue(value);

  if (QcDatabase::exec_and_check_prepared_query(query) and commit)
    m_database->commit();
}

QSqlQuery
QcDatabaseTable::prepare_insert(const QStringList & fields)
{
  QSqlQuery query = m_database->new_query();
  QString sql_query =
    QLatin1String("INSERT INTO ") + m_name +
    QLatin1String(" (") + fields.join(',') + QLatin1String(") VALUES (") + format_prepare(fields.size()) + ')';
  query.prepare(sql_query);

  return query;
}

QSqlQuery
QcDatabaseTable::insert(const QVariantHash & kwargs, bool commit)
{
  QSqlQuery query = prepare_insert(kwargs.keys());
  qInfo() << query.lastQuery() << kwargs;
  bind_and_exec(query, kwargs, commit);

  return query;
}

QSqlQuery
QcDatabaseTable::select(const QStringList & fields, const QString & where) const
{
  QSqlQuery query = m_database->new_query();
  QString sql_query = QLatin1String("SELECT ") + fields.join(',') + QLatin1String(" FROM ") + m_name;
  if (!where.isEmpty())
    sql_query += QLatin1String(" WHERE ") + where;
  qInfo() << sql_query << fields;
  QcDatabase::exec_and_check(query, sql_query);

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

QSqlRecord
QcDatabaseTable::select_one(const QString & where) const
{
  QStringList fields(QLatin1String("*"));
  // if (m_schema.has_rowid_primary_key())
  //   fields << QLatin1String("id"); // rowid
  return select_one(fields, where);
}

QSqlQuery
QcDatabaseTable::prepare_update(const QStringList & fields, const QString & where)
{
  QSqlQuery query = m_database->new_query();
  QString sql_query = QLatin1String("UPDATE ") + m_name + QLatin1String(" SET ") + format_prepare_update(fields);
  if (!where.isEmpty())
    sql_query += QLatin1String(" WHERE ") + where;
  query.prepare(sql_query);

  return query;
}

QSqlQuery
QcDatabaseTable::update(const QVariantHash & kwargs, const QString & where)
{
  QSqlQuery query = prepare_update(kwargs.keys(), where);
  bind_and_exec(query, kwargs, true);

  // Fixme: return ?
  return query;
}

QSqlQuery
QcDatabaseTable::delete_row(const QString & where)
{
  QSqlQuery query = m_database->new_query();
  QString sql_query = QLatin1String("DELETE FROM ") + m_name;
  if (!where.isEmpty())
    sql_query += QLatin1String(" WHERE ") + where;
  // Fixme: execute_query ?
  QcDatabase::exec_and_check(query, sql_query);

  return query;
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
