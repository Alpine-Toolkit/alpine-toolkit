/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire
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
 * $QTCARTO_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "database_query.h"
#include "alpine_toolkit.h"

#include "database_table.h"

/**************************************************************************************************/

constexpr const char EQUAL[] = "=";
constexpr const char NOT_EQUAL[] = "!=";

constexpr const char LESS_THAN[] = "<";
constexpr const char GREATHER_THAN[] = ">";
constexpr const char LESS_EQUAL_THAN[] = "<=";
constexpr const char GREATHER_EQUAL_THAN[] = ">=";

constexpr const char NOT[] = "NOT";
constexpr const char AND[] = "AND";
constexpr const char OR[] = "OR";

constexpr const char MIN[] = "MIN";
constexpr const char MAX[] = "MAX";

constexpr const char AVG[] = "AVG";
constexpr const char SUM[] = "SUM";

constexpr const char COUNT[] = "COUNT";

constexpr const char LIKE[] = "LIKE";

constexpr const char IS_NULL[] = "IS NULL";
constexpr const char IS_NOT_NULL[] = "IS NOT NULL";

constexpr const char DESC[] = "DESC";
constexpr const char ASC[] = "ASC";

constexpr const char __ST_GeomFromText__[] = "ST_GeomFromText";
constexpr const char __ST_AsText__[] = "ST_AsText";
constexpr const char __ST_GeomFromWKB__[] = "ST_GeomFromWKB";
constexpr const char __ST_AsBinary__[] = "ST_AsBinary";

/**************************************************************************************************/

typedef QoSqlExpressionTrait ExpTrait;

/**************************************************************************************************/

// Fixme: multiple ...
bool
_is_alpha_string(const QString & name)
{
  for (const auto & c : name)
    if (not (c.isLetterOrNumber() or c == '_'))
        return false;
  return true;
}

QString
QoSqlExpressionTrait::quote_sql_identifier(const QString & name, SqlFlavour flavour)
{
  /*
   * 'keyword'		A keyword in single quotes is a string literal.
   * "keyword"		A keyword in double-quotes is an identifier.
   * [keyword]		A keyword enclosed in square brackets is an identifier. This is not standard SQL.
   *                      This quoting mechanism is used by MS Access and SQL Server.
   * `keyword`		A keyword enclosed in grave accents (ASCII code 96) is an identifier. This is not standard SQL.
   *                      This quoting mechanism is used by MySQL and is included in SQLite for compatibility.
   */

  // Only quote when necessary
  if (_is_alpha_string(name))
    return name;

  switch (flavour) {
  case SqlFlavour::MySQL:
    return '`' + name + '`';
  case SqlFlavour::SQL_Server:
    return '[' + name + ']';
  default:
    return '"' + name + '"';
  }
}

QcSqlExpressionPtr
QoSqlExpressionTrait::as(const QString & label) const
{
  return QcSqlExpressionPtr(new QoSqlAsExpression(clone(), label));
}

QString
QoSqlExpressionTrait::to_sql(const QVariant & value)
{
  if (value.type() == QVariant::String)
    return QLatin1String("'") + value.toString() + QLatin1String("'");
  else
    return value.toString();
}

QString
QoSqlExpressionTrait::comma_join(const QStringList & strings)
{
  return strings.join(QLatin1String(", "));
}

QString
QoSqlExpressionTrait::comma_join(const QcSqlExpressionList & expressions, SqlFlavour flavour)
{
  QStringList strings;

  for (const auto & expression : expressions)
    strings << expression->to_sql(flavour);

  return comma_join(strings);
}

/**************************************************************************************************/

QoSqlAsExpression::QoSqlAsExpression(const QcSqlExpressionPtr & expression,
                                     const QString & label)
  : m_expression(expression),
    m_label(label)
{
}

QString
QoSqlAsExpression::to_sql(SqlFlavour flavour) const
{
  return m_expression->to_sql(flavour) + QLatin1String(" AS ") + m_label;
}

/**************************************************************************************************/

QoSqlField::QoSqlField(const QString & name)
  : m_name(name),
    m_table_name()
{}

QoSqlField::QoSqlField(const QString & name, const QString & table_name)
  : m_name(name),
    m_table_name(table_name)
{}

QoSqlField::QoSqlField(const QoSqlField & other)
  : m_name(other.m_name),
    m_table_name(other.m_table_name)
{}

QoSqlField &
QoSqlField::operator=(const QoSqlField & other)
{
  if (this != &other) {
    m_name = other.m_name;
    m_table_name = other.m_table_name;
  }

  return *this;
}

QoSqlField::~QoSqlField()
{}

QString
QoSqlField::to_sql(SqlFlavour flavour) const
{
  QString name = m_table_name.isEmpty() ? m_name : m_table_name + '.' + m_name;
  return quote_sql_identifier(name, flavour);
}

QString
QoSqlField::as(const QString & name, SqlFlavour flavour) const
{
  return to_sql(flavour) + QLatin1String(" AS ") + name;
}

QString
QoSqlField::as(SqlFlavour flavour) const
{
  QString name = m_table_name + '_' + m_name;
  return as(name, flavour);
}

/**************************************************************************************************/

QoSqlPrepareValue::QoSqlPrepareValue()
{}

QoSqlPrepareValue::QoSqlPrepareValue(const QoSqlPrepareValue & other)
  : QoSqlPrepareValue()
{
  Q_UNUSED(other);
}

QoSqlPrepareValue &
QoSqlPrepareValue::operator=(const QoSqlPrepareValue & other)
{
  Q_UNUSED(other);
  return *this;
}

QoSqlPrepareValue::~QoSqlPrepareValue()
{}

QString
QoSqlPrepareValue::to_sql(SqlFlavour flavour) const // unused
{
  return QLatin1String("?");
}

/**************************************************************************************************/

QoSqlFieldExpressionTwoValue::QoSqlFieldExpressionTwoValue(const QoSqlField & field,
                                                           const QVariant & value1,
                                                           const QVariant & value2)
  : m_field(field),
    m_value1(value1),
    m_value2(value2)
{}

/**************************************************************************************************/

QoSqlFieldExpressionValueList::QoSqlFieldExpressionValueList(const QoSqlField & field,
                                                             const QVariantList & values)
  : m_field(field),
    m_values(values)
{}

QStringList
QoSqlFieldExpressionValueList::string_values() const
{
  QStringList strings;
  for (const auto & value : m_values)
    strings << to_sql(value);

  return strings;
}

/**************************************************************************************************/

QString
QoSqlInExpression::to_sql(SqlFlavour flavour) const
{
  return m_field.to_sql(flavour) +
    QLatin1String(" IN (") + comma_join(string_values()) + + ')';
}

/**************************************************************************************************/

QString
QoSqlBetweenExpression::to_sql(SqlFlavour flavour) const
{
  return m_field.to_sql(flavour) + QLatin1String(" BETWEEN ") +
    ExpTrait::to_sql(m_value1) + QLatin1String(" AND ") + ExpTrait::to_sql(m_value2);
}

/**************************************************************************************************/

QcSqlExpressionPtr
QoSqlField::operator==(const QVariant & value) const
{
  return QcSqlExpressionPtr(new QoSqlFieldExpression<EQUAL>(*this, value));
}

QcSqlExpressionPtr
QoSqlField::operator!=(const QVariant & value) const
{
  return QcSqlExpressionPtr(new QoSqlFieldExpression<NOT_EQUAL>(*this, value));
}

QcSqlExpressionPtr
QoSqlField::operator>(const QVariant & value) const
{
  return QcSqlExpressionPtr(new QoSqlFieldExpression<GREATHER_THAN>(*this, value));
}

QcSqlExpressionPtr
QoSqlField::operator<(const QVariant & value) const
{
  return QcSqlExpressionPtr(new QoSqlFieldExpression<LESS_THAN>(*this, value));
}

QcSqlExpressionPtr
QoSqlField::operator>=(const QVariant & value) const
{
  return QcSqlExpressionPtr(new QoSqlFieldExpression<GREATHER_EQUAL_THAN>(*this, value));
}

QcSqlExpressionPtr
QoSqlField::operator<=(const QVariant & value) const
{
  return QcSqlExpressionPtr(new QoSqlFieldExpression<LESS_EQUAL_THAN>(*this, value));
}

QcSqlExpressionPtr
QoSqlField::in(const QVariantList & values) const
{
  return QcSqlExpressionPtr(new QoSqlInExpression(*this, values));
}

QcSqlExpressionPtr
QoSqlField::between(const QVariant & value_min, const QVariant & value_max) const
{
  return QcSqlExpressionPtr(new QoSqlBetweenExpression(*this, value_min, value_max));
}

QcSqlExpressionPtr
QoSqlField::like(const QString & pattern) const
{
  return QcSqlExpressionPtr(new QoSqlFieldExpression<LIKE>(*this, pattern));
}

QcSqlExpressionPtr
QoSqlField::is_null() const
{
  return QcSqlExpressionPtr(new QoSqlFieldSuffixExpression<IS_NULL>(*this));
}

QcSqlExpressionPtr
QoSqlField::is_not_null() const
{
  return QcSqlExpressionPtr(new QoSqlFieldSuffixExpression<IS_NOT_NULL>(*this));
}

QcSqlExpressionPtr
QoSqlField::desc() const
{
  return QcSqlExpressionPtr(new QoSqlFieldSuffixExpression<DESC>(*this));
}

QcSqlExpressionPtr
QoSqlField::asc() const
{
  return QcSqlExpressionPtr(new QoSqlFieldSuffixExpression<ASC>(*this));
}

/**************************************************************************************************/

/*
QcSqlExpressionPtr
operator!(const QcSqlExpressionPtr & expression)
{
  return QcSqlExpressionPtr(new QoSqlUnaryExpression<NOT>(expression));
}
*/

// Fixme: name clash

QcSqlExpressionPtr
Not(const QcSqlExpressionPtr & expression)
{
  return QcSqlExpressionPtr(new QoSqlUnaryExpression<NOT>(expression));
}

QcSqlExpressionPtr
Count(const QcSqlExpressionPtr & expression)
{
  return QcSqlExpressionPtr(new QoSqlFunctionExpression<COUNT>(expression));
}

QcSqlExpressionPtr
Min(const QcSqlExpressionPtr & expression)
{
  return QcSqlExpressionPtr(new QoSqlFunctionExpression<MIN>(expression));
}

QcSqlExpressionPtr
Max(const QcSqlExpressionPtr & expression)
{
  return QcSqlExpressionPtr(new QoSqlFunctionExpression<MAX>(expression));
}

QcSqlExpressionPtr
Avg(const QcSqlExpressionPtr & expression)
{
  return QcSqlExpressionPtr(new QoSqlFunctionExpression<AVG>(expression));
}

QcSqlExpressionPtr
Sum(const QcSqlExpressionPtr & expression)
{
  return QcSqlExpressionPtr(new QoSqlFunctionExpression<SUM>(expression));
}

/**************************************************************************************************/

QcSqlExpressionPtr operator&&(const QcSqlExpressionPtr & expression1,
                              const QcSqlExpressionPtr & expression2)
{
  return QcSqlExpressionPtr(new QoSqlBinaryExpression<AND>(expression1, expression2));
}

QcSqlExpressionPtr operator||(const QcSqlExpressionPtr & expression1,
                              const QcSqlExpressionPtr & expression2)
{
  return QcSqlExpressionPtr(new QoSqlBinaryExpression<OR>(expression1, expression2));
}

/**************************************************************************************************/

QcSqlExpressionPtr
ST_GeomFromText()
{
  return ST_GeomFromText(QoSqlPrepareValue());
}

QcSqlExpressionPtr
ST_GeomFromText(const QcSqlExpressionPtr & expression)
{
  return QcSqlExpressionPtr(new QoSqlSpatialFunctionExpression<__ST_GeomFromText__>(expression));
}

QcSqlExpressionPtr
ST_AsText(const QcSqlExpressionPtr & expression)
{
  return QcSqlExpressionPtr(new QoSqlFunctionExpression<__ST_AsText__>(expression));
}

QcSqlExpressionPtr
ST_GeomFromWKB()
{
  return ST_GeomFromWKB(QoSqlPrepareValue());
}

QcSqlExpressionPtr
ST_GeomFromWKB(const QcSqlExpressionPtr & expression)
{
  return QcSqlExpressionPtr(new QoSqlSpatialFunctionExpression<__ST_GeomFromWKB__>(expression));
}

QcSqlExpressionPtr
ST_AsBinary(const QcSqlExpressionPtr & expression)
{
  return QcSqlExpressionPtr(new QoSqlFunctionExpression<__ST_AsBinary__>(expression));
}

/**************************************************************************************************/

QoSqlQuery::QoSqlQuery()
  : m_table(nullptr),
    m_flags(static_cast<int>(Flags::NumberOfFlags)),
    m_fields(),
    m_value_expressions(),
    m_where(nullptr),
    m_group_by(),
    m_order_by()
{}

QoSqlQuery::QoSqlQuery(QoDatabaseTable * table)
  : m_table(table),
    m_flags(static_cast<int>(Flags::NumberOfFlags)),
    m_fields(),
    m_value_expressions(),
    m_where(nullptr),
    m_group_by(),
    m_order_by()
{}

/*
QoSqlQuery::QoSqlQuery(const QcSqlTable & table)
  : m_table_name(table.table_name())
{}
*/

QoSqlQuery::QoSqlQuery(const QoSqlQuery & other)
  : m_table(other.m_table),
    m_query_type(other.m_query_type),
    m_select_type(other.m_select_type),
    m_flags(other.m_flags),
    m_fields(other.m_fields),
    m_where(other.m_where),
    m_group_by(other.m_group_by),
    m_having(other.m_having),
    m_order_by(other.m_order_by),
    m_limit(other.m_limit),
    m_offset(other.m_offset)
{}

QoSqlQuery::~QoSqlQuery()
{}

QoSqlQuery &
QoSqlQuery::operator=(const QoSqlQuery & other)
{
  if (this != &other) {
    m_table = other.m_table;
    m_query_type = other.m_query_type;
    m_select_type = other.m_select_type;
    m_flags = other.m_flags;
    m_fields = other.m_fields;
    m_where = other.m_where;
    m_group_by = other.m_group_by;
    m_having = other.m_having;
    m_order_by = other.m_order_by;
    m_limit = other.m_limit;
    m_offset = other.m_offset;
  }

  return *this;
}

const QString &
QoSqlQuery::table_name() const
{
  return m_table->name();
}

SqlFlavour
QoSqlQuery::sql_flavour() const
{
  return m_table->sql_flavour();
}

QoSqlQuery &
QoSqlQuery::distinct()
{
  m_query_type = QueryType::Select;
  set_flags(Flags::SelectDistinct);

  return *this;
}

QoSqlQuery &
QoSqlQuery::count()
{
  m_query_type = QueryType::Select;
  set_flags(Flags::SelectCount);

  return *this;
}

QoSqlQuery &
QoSqlQuery::exists()
{
  m_query_type = QueryType::Select;
  set_flags(Flags::SelectExists);

  return *this;
}

QoSqlQuery &
QoSqlQuery::insert()
{
  m_query_type = QueryType::Insert;

  return *this;
}

QoSqlQuery &
QoSqlQuery::update()
{
  m_query_type = QueryType::Update;

  return *this;
}

QoSqlQuery &
QoSqlQuery::delete_()
{
  m_query_type = QueryType::Delete;

  return *this;
}

QoSqlQuery &
QoSqlQuery::add_column(const QcSqlExpressionPtr & expression)
{
  m_fields << expression;

  return *this;
}

QoSqlQuery &
QoSqlQuery::add_columns(const QStringList & names)
{
  for (const auto & name : names)
    m_fields << QoSqlField(name); // Fixme: table_name()

  return *this;
}

QoSqlQuery &
QoSqlQuery::add_column(const QcSqlExpressionPtr & expression, const QcSqlExpressionPtr & value_expression)
{
  m_fields << expression;

  const QcSqlExpressionPtr & _expression = m_fields.last();
  m_value_expressions.insert(_expression, value_expression);

  return *this;
}

QoSqlQuery &
QoSqlQuery::filter(const QcSqlExpressionPtr & expression)
{
  if (m_where.isNull())
    m_where = expression;
  else
    m_where = m_where and expression;

  return *this;
}

QoSqlQuery &
QoSqlQuery::group_by(const QoSqlField & field)
{
  m_group_by << field;

  return *this;
}

QoSqlQuery &
QoSqlQuery::having(const QcSqlExpressionPtr & expression)
{
  m_having = expression;

  return *this;
}

QoSqlQuery &
QoSqlQuery::order_by(const QcSqlExpressionPtr & expression)
{
  m_order_by << expression;

  return *this;
}

QoSqlQuery &
QoSqlQuery::limit(int value)
{
  m_limit = value;
  m_query_type = QueryType::Select;
  m_select_type = SelectType::None;

  return *this;
}

QoSqlQuery &
QoSqlQuery::offset(int value)
{
  m_offset = value;
  m_query_type = QueryType::Select;
  // m_select_type = SelectType::None;

  return *this;
}

QoSqlQuery &
QoSqlQuery::slice(int start, int stop)
{
  m_offset = start;
  m_limit = stop - start;

  m_query_type = QueryType::Select;
  m_select_type = SelectType::None;

  return *this;
}

QoSqlQuery &
QoSqlQuery::one()
{
  m_limit = 1;
  m_select_type = SelectType::SelectOne;

  return *this;
}

QStringList
QoSqlQuery::field_names(const QcSqlExpressionList & fields) const
{
  SqlFlavour flavour = sql_flavour();
  QStringList field_names;

  for (const auto & field : fields)
    field_names << field->to_sql(flavour);

  return field_names;
}

QStringList
QoSqlQuery::field_names(const QcFieldList & fields) const
{
  // Fixme: cf. infra

  SqlFlavour flavour = sql_flavour();
  QStringList field_names;

  for (const auto & field : fields)
    field_names << field.to_sql(flavour);

  return field_names;
}

QStringList
QoSqlQuery::fields_for_update() const
{
  SqlFlavour flavour = sql_flavour();
  QStringList field_names;

  for (const auto & field : m_fields)
    field_names << field->to_sql(flavour) + QLatin1String(" = ?");

  return field_names;
}

QString
QoSqlQuery::comma_interrogation_list(int count)
{
  QString query;

  for (int i = 0; i < count; i++) {
    if (not query.isEmpty())
      query += QLatin1String(", ");
    query += '?';
  }

  return query;
}

QString
QoSqlQuery::insert_values(const SqlFlavour & flavour) const
{
  // Fixme: API ???
  if (m_value_expressions.isEmpty())
    return comma_interrogation_list(m_fields.size());
  else {
    QString query;
    for (const auto & field : m_fields) {
      if (not query.isEmpty())
        query += QLatin1String(", ");
      if (m_value_expressions.contains(field)) {
        const QcSqlExpressionPtr & ctor = m_value_expressions[field];
        if (ctor.isNull())
          qATCritical() << QLatin1String("SQL value ctor is null for") << field->to_sql();
        else
          query += ctor->to_sql(flavour); // Fixme: ? is implicit
      } else
        query += '?';
    }
    return query;
  }
}

QString
QoSqlQuery::table_name_as(const QString & name) const
{
  return quote_sql_identifier(table_name()) + QLatin1String(" AS ") + name;
}

QString
QoSqlQuery::to_sql() const
{
  /*
   * SELECT *
   * FROM table
   * WHERE condition
   * GROUP BY expression
   * HAVING condition
   * { UNION | INTERSECT | EXCEPT }
   * ORDER BY expression
   * LIMIT count
   * OFFSET start
   */

  QString query;

  if (m_query_type == QueryType::None)
    return query;

  SqlFlavour flavour = sql_flavour();

  switch (m_query_type) {
  case QueryType::Select: query = QLatin1String("SELECT"); break;
  case QueryType::Insert: query = QLatin1String("INSERT"); break;
  case QueryType::Update: query = QLatin1String("UPDATE"); break;
  case QueryType::Delete: query = QLatin1String("DELETE"); break;
  case QueryType::None: break;
  }

  if (get_flags(Flags::SelectCount))
    // Generates the SQL for this Query as follows:
    // SELECT count(1) AS count_1 FROM (
    //   SELECT <rest of query follows...>
    // ) AS anon_1
    query += QLatin1String("SELECT count(1) AS count_1 FROM ( SELECT ");

  if (get_flags(Flags::SelectExists))
    // Generates the SQL for this Query as follows:
    // SELECT EXISTS FROM (
    //   SELECT <rest of query follows...>
    // ) AS anon_1
    query += QLatin1String("SELECT EXISTS ( SELECT ");

  if (m_query_type == QueryType::Select and
      get_flags(Flags::SelectDistinct)) {
    if (flavour == SqlFlavour::Oracle)
      query += QLatin1String(" UNIQUE");
    else
      // Fixme: PostgreSQL: DISTINCT ON
      query += QLatin1String(" DISTINCT");
  }

  query += ' ';

  if (m_query_type == QueryType::Select) {
    if (m_fields.isEmpty())
      query += '*';
    else
      query += ExpTrait::comma_join(field_names(m_fields));
  }

  if (m_query_type == QueryType::Select)
      query += ' ';

  if (m_query_type == QueryType::Select or
      m_query_type == QueryType::Delete) {
    query += QLatin1String("FROM ");
  }

  if (m_query_type == QueryType::Insert)
    query += QLatin1String("INTO ");

  query += quote_sql_identifier(table_name());

  if (m_query_type == QueryType::Update) {
    query += QLatin1String(" SET ");
      query += ExpTrait::comma_join(fields_for_update());
  }

  if (m_query_type == QueryType::Insert) {
    query += QLatin1String(" (");
    query += ExpTrait::comma_join(field_names(m_fields));
    query += QLatin1String(") VALUES (");
    query += insert_values(flavour);
    query += ')';
  } else { // Not INSERT
    if (not m_where.isNull()) {
      query += QLatin1String(" WHERE ");
      query += m_where->to_sql(flavour);
    }
  }

  if (m_query_type == QueryType::Select) {
    if (not m_group_by.isEmpty())
      query += QLatin1String(" GROUP BY ") + ExpTrait::comma_join(field_names(m_group_by));

    if (not m_having.isNull())
      query += QLatin1String(" HAVING ") + m_having->to_sql(flavour);

    if (not m_order_by.isEmpty())
      query += QLatin1String(" ORDER BY ") + ExpTrait::comma_join(m_order_by, flavour);

    // MySQL syntax: LIMIT limit, offset
    // but also support ANSI
    if (m_limit > 0)
      query += QLatin1String(" LIMIT ") + m_limit; // ?
    if (m_offset > 0)
      query += QLatin1String(" OFFSET ") + m_offset; // ?
  }

  if (get_flags(Flags::SelectCount) or
      get_flags(Flags::SelectExists))
    query += QLatin1String(") AS anon_1)");

  query += ';';

  return query;
}

QSqlQuery
QoSqlQuery::exec()
{
  return m_table->exec(*this);
}

/**************************************************************************************************/

/*
QString
QoMySqlQuery::quote_sql_identifier(const QString & name) const
{
  return '`' + name + '`';
}

QString
QoSqlServerQuery::quote_sql_identifier(const QString & name) const
{
  return '[' + name + ']';
}
*/
