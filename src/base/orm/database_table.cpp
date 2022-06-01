/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine Toolkit software.
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

#include "database_table.h"
#include "alpine_toolkit.h"

#include "database.h"
#include "database_query.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>

/**************************************************************************************************/

QString
comma_join(const QStringList & string_list)
{
  return string_list.join(',');
}

int
last_insert_id(const QSqlQuery & query)
{
  return query.lastInsertId().toInt();
}

/**************************************************************************************************/

QString
QoDatabaseTable::format_prepare(int number_of_fields)
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
QoDatabaseTable::format_prepare_update(const QStringList & fields)
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
QoDatabaseTable::format_kwarg(const QVariantHash & kwargs, const QString & separator)
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
QoDatabaseTable::format_simple_where(const QVariantHash & kwargs)
{
  return format_kwarg(kwargs, QLatin1String(" AND "));
}

QoDatabaseTable::QoDatabaseTable()
  : m_database(nullptr),
    m_schema(),
    m_name()
{}

QoDatabaseTable::QoDatabaseTable(QoDatabase * database, const QString & name)
  : m_database(database),
    m_schema(name, name),
    m_name(name)
{}

QoDatabaseTable::QoDatabaseTable(QoDatabase * database, const QoSchema & schema)
  : m_database(database),
    m_schema(schema),
    m_name(schema.table_name())
{}

QoDatabaseTable::QoDatabaseTable(const QoDatabaseTable & other)
  : m_database(other.m_database),
    m_schema(other.m_schema),
    m_name(other.m_name)
{}

QoDatabaseTable::~QoDatabaseTable()
{
  qATInfo() << "--- Delete QoDatabaseTable";
}

QoDatabaseTable &
QoDatabaseTable::operator=(const QoDatabaseTable & other)
{
  if (this != &other) {
    m_database = other.m_database;
    m_schema = other.m_schema;
    m_name = other.m_name;
  }

  return *this;
}

SqlFlavour
QoDatabaseTable::sql_flavour() const
{
  return m_database->sql_flavour();
}

void
QoDatabaseTable::commit()
{
   m_database->commit();
}

bool
QoDatabaseTable::exists() const
{
  QStringList tables = m_database->database().tables(QSql::Tables);
  return tables.contains(m_name);
}

bool
QoDatabaseTable::create()
{
  return m_database->execute_queries(m_schema.to_sql_definition());
}

QoSqlQuery
QoDatabaseTable::sql_query()
{
  return QoSqlQuery(this);
}

QSqlQuery
QoDatabaseTable::exec(const QoSqlQuery & sql_query)
{
  // Fixme: why pass QSqlQuery, could return it ???
  QSqlQuery query = m_database->new_query();
  QoDatabase::exec_and_check(query, sql_query);

  return query;
}

bool
QoDatabaseTable::drop()
{
  QString sql_query = QLatin1String("DROP TABLE ") + m_name;
  return m_database->execute_query(sql_query);
}

QSqlQuery
QoDatabaseTable::prepare_complete_insert()
{
  QSqlQuery query = m_database->new_query();
  QoSqlQuery _sql_query = sql_query(); // Fixme: name clash
  for (const auto & field : m_schema.fields_without_row_id()) {
    // QoSqlField sql_field = field->to_sql_field()
    // need a QoSqlFieldPtr alive
    QString sql_field = field->name();
    if (field->has_sql_column_ctor())
      _sql_query.add_column(sql_field, field->sql_value_ctor());
    else
      _sql_query.add_column(sql_field);
  }
  _sql_query.insert();
  qATInfo() << "prepare_complete_insert" << _sql_query.to_sql();
  query.prepare(_sql_query.to_sql());

  return query;
}

QSqlQuery
QoDatabaseTable::prepare_complete_insert(int number_of_fields)
{
  QSqlQuery query = m_database->new_query();
  QString sql_query =
    QLatin1String("INSERT INTO ") + m_name + QLatin1String(" VALUES (") + format_prepare(number_of_fields) + ')';
  query.prepare(sql_query);

  return query;
}

QSqlQuery
QoDatabaseTable::prepare_complete_insert(const QStringList & fields)
{
  QSqlQuery query = m_database->new_query();
  // QString sql_query =
  //   QLatin1String("INSERT INTO ") + m_name +
  //   QLatin1String(" (") + comma_join(fields) + QLatin1String(") VALUES (") + format_prepare(fields.size()) + ')';
  QoSqlQuery _sql_query = sql_query().add_columns(fields).insert(); // Fixme: name clash
  query.prepare(_sql_query.to_sql());

  return query;
}

QSqlQuery
QoDatabaseTable::complete_insert(const QVariantList & variants, bool _commit)
{
  QSqlQuery query;
  if (m_schema.has_sql_value_ctor())
    // Use Sql Query builder
    query = prepare_complete_insert();
  else if (m_schema.has_rowid_primary_key())
    // excepted if we want to set the id manually
    query = prepare_complete_insert(m_schema.field_names_witout_rowid());
  else
    query = prepare_complete_insert(variants.size());
  qATInfo() << query.lastQuery() << variants;

  for (const auto & value : variants)
    query.addBindValue(value);

  // Fixme: namesapce ???
  if (_commit and QoDatabase::exec_and_check_prepared_query(query))
    commit();

  return query;
}

void
QoDatabaseTable::add(QoRowTraits & row, bool commit)
{
  // if (not row.can_save()) {
  //   qWarning() << "Cannot save" << row; // Fixme: cannot log !
  //   return;
  // }

  // We could use QVariantHash to only set defined field (skip default),
  //   but we have to track correctly defined field
  //   Moreover QVariantHash is slower
  QSqlQuery query = complete_insert(row.to_variant_list_sql(), commit); // duplicate = false
  int rowid = last_insert_id(query);
  // To only set rowid for such table, we must know the type at run time
  //   e.g. dynamic_cast<QoRowWithId *>(row);
  row.set_insert_id(rowid);
}

void
QoDatabaseTable::add(const QList<QoRowTraits *> & rows, bool _commit)
{
  QSqlQuery query;
  if (m_schema.has_sql_value_ctor())
    // Use Sql Query builder
    query = prepare_complete_insert();
  else if (m_schema.has_rowid_primary_key())
    // excepted if we want to set the id manually
    query = prepare_complete_insert(m_schema.field_names_witout_rowid());
  else
    query = prepare_complete_insert(m_schema.number_of_fields());

  for (auto * row : rows) {
    int i = 0;
    for (const auto & value : row->to_variant_list_sql())
      query.bindValue(i++, value);
    if (QoDatabase::exec_and_check_prepared_query(query))
      row->set_insert_id(last_insert_id(query));
  }

  if (_commit)
    commit();
}

void
QoDatabaseTable::bind_and_exec(QSqlQuery & query, const QVariantHash & kwargs, bool _commit)
{
  // qATInfo() << "Bind on" << query.lastQuery() << kwargs;

  for (const auto & value : kwargs.values())
    query.addBindValue(value);

  if (_commit and QoDatabase::exec_and_check_prepared_query(query))
    commit();
}

QSqlQuery
QoDatabaseTable::prepare_insert(const QStringList & fields)
{
  QSqlQuery query = m_database->new_query();
  QString sql_query =
    QLatin1String("INSERT INTO ") + m_name +
    QLatin1String(" (") + comma_join(fields) + QLatin1String(") VALUES (") + format_prepare(fields.size()) + ')';
  query.prepare(sql_query);

  return query;
}

QSqlQuery
QoDatabaseTable::insert(const QVariantHash & kwargs, bool commit)
{
  QSqlQuery query = prepare_insert(kwargs.keys());
  qATInfo() << query.lastQuery() << kwargs;
  bind_and_exec(query, kwargs, commit);

  return query;
}

QSqlQuery
QoDatabaseTable::select_all() // const // Fixme: sql_query() is not const due to QoSqlQuery::exec
{
  QSqlQuery query = m_database->new_query();

  QoSqlQuery _sql_query = sql_query(); // Fixme: name clash
  for (const auto & field : m_schema) {
    // QoSqlField sql_field = field->to_sql_field()
    // need a QoSqlFieldPtr alive
    QString sql_field = field->name();
    if (field->has_sql_value_getter())
      _sql_query.add_column(field->sql_value_getter()); // Fixme: pass field ?
    else
      _sql_query.add_column(sql_field);
  }
  _sql_query.all();
  qATInfo() << _sql_query.to_sql();

  QoDatabase::exec_and_check(query, _sql_query);

  return query;
}

QSqlQuery
QoDatabaseTable::select(const QStringList & fields, const QString & where) const
{
  QSqlQuery query = m_database->new_query();
  // Fixme: use query api ?
  //   but only strings : basic
  //   modify ORM to use QoSqlField instead
  QString sql_query = QLatin1String("SELECT ") + comma_join(fields) + QLatin1String(" FROM ") + m_name;
  if (!where.isEmpty())
    sql_query += QLatin1String(" WHERE ") + where;
  qATInfo() << sql_query << fields;
  QoDatabase::exec_and_check(query, sql_query);

  return query;
}

QSqlRecord
QoDatabaseTable::select_one(const QStringList & fields, const QString & where) const
{
  QSqlQuery query = select(fields, where);
  QSqlRecord record;
  if (query.next()) {
    record = query.record();
    if (query.next())
      qWarning() << QLatin1String("More than one rows returned");
  } else
    qWarning() << "Any row";

  return record; // test with isEmpty()
}

QSqlRecord
QoDatabaseTable::select_one_where(const QString & where) const
{
  QStringList fields(QLatin1String("*"));
  // if (m_schema.has_rowid_primary_key())
  //   fields << QLatin1String("id"); // rowid
  return select_one(fields, where);
}

int
QoDatabaseTable::count(const QString & where) const
{
  QSqlQuery query = select(QLatin1String("COUNT()"), where);
  if (query.next()) // only one row is returned
    return query.value(0).toInt();
  else
    return -1;
}

int
QoDatabaseTable::rowid(const QString & where) const
{
  QSqlQuery query = select(QLatin1String("rowid"), where);
  int rowid = -1;
  if (query.next()) {
    int _rowid = query.value(0).toInt();
    if (query.next())
      qWarning() << QLatin1String("More than one rows returned");
    else
      rowid = _rowid;
  }

  return rowid;
}

QSqlQuery
QoDatabaseTable::join(JoinType join_type, const QoDatabaseTable & table2, const QString & where) const
{
  QSqlQuery query = m_database->new_query();

  QString join_string;
  switch (join_type) {
  case JoinType::InnerJoin: join_string = QLatin1String("Inner"); break;
  case JoinType::LeftJoin: join_string = QLatin1String("Left"); break;
  case JoinType::RightJoin: join_string = QLatin1String("Right"); break;
  case JoinType::FullJoin: join_string = QLatin1String("FULL OUTER"); break;
  case JoinType::SelfJoin: return query;
  }

  const QString & name1 = m_name;
  const QString & name2 = table2.m_name;
  const QoSchema & schema1 = m_schema;
  const QoSchema & schema2 = table2.m_schema;
  QStringList fields1 = schema1.prefixed_field_names();
  QStringList fields2 = schema2.prefixed_field_names();
  QStringList fields = fields1 + fields2;

  QString sql_query = QLatin1String("SELECT ") + comma_join(fields) +
    QLatin1String(" FROM ") + name1 + join_string + QLatin1String(" JOIN ") + name2 +
    QLatin1String(" WHERE ") + where;
  QoDatabase::exec_and_check(query, sql_query);

  return query;
}

QSqlQuery
QoDatabaseTable::prepare_update(const QStringList & fields, const QString & where)
{
  QSqlQuery query = m_database->new_query();
  QString sql_query = QLatin1String("UPDATE ") + m_name + QLatin1String(" SET ") + format_prepare_update(fields);
  if (!where.isEmpty())
    sql_query += QLatin1String(" WHERE ") + where;
  query.prepare(sql_query);

  return query;
}

QSqlQuery
QoDatabaseTable::update(const QVariantHash & kwargs, const QString & where)
{
  QSqlQuery query = prepare_update(kwargs.keys(), where);
  bind_and_exec(query, kwargs, true);

  // Fixme: return ?
  return query;
}

QSqlQuery
QoDatabaseTable::delete_row(const QString & where)
{
  QSqlQuery query = m_database->new_query();
  QString sql_query = QLatin1String("DELETE FROM ") + m_name;
  if (!where.isEmpty())
    sql_query += QLatin1String(" WHERE ") + where;
  // Fixme: execute_query ?
  QoDatabase::exec_and_check(query, sql_query);

  return query;
}
