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

#ifndef __DATABASE_QUERY_H__
#define __DATABASE_QUERY_H__

/**************************************************************************************************/

/* To Be Implemented
 * - CREATE / ALTER TABLE ...
 * - CREATE INDEX
 * - INSERT INTO table VALUES (...)
 * - CASE
 * - EXCEPT / MINUS
 * - MySQL: ON DUPLICATE KEY UPDATE
 * - EXISTS, ALL, ANY, SOME
 * - INNER JOIN — SELECT * FROM A INNER JOIN B ON A.key = B.key
 * - CROSS JOIN — SELECT * FROM table1 CROSS JOIN table2
 * - LEFT JOIN  — SELECT * FROM A LEFT JOIN B ON A.key = B.key
 *                SELECT * FROM A LEFT JOIN B ON A.key = B.key WHERE B.key IS NULL
 * - RIGHT JOIN — SELECT * FROM A RIGHT JOIN B ON A.key = B.key
 *                SELECT * FROM A RIGHT JOIN B ON A.key = B.key WHERE B.key IS NULL
 * - FULL JOIN —  SELECT * FROM A FULL JOIN B ON A.key = B.key WHERE A.key IS NULL OR B.key IS NULL
 * - SELF JOIN
 * - NATURAL JOIN — SELECT * FROM table1 NATURAL JOIN table2
 *
 * - from_self
 * - session.query(User).get(5)
 * - intersect — SELECT * FROM `table1` INTERSECT SELECT * FROM `table2`
 * - intersect_all
 * - join
 * - one
 * - one_or_none
 * - outerjoin
 * - prefix_with
 * - scalar
 * - select_from
 * - subquery
 * - union
 * - union_all
 */

/**************************************************************************************************/

// #include "orm/database_table.h"
#include "orm/sql_flavour.h"

#include <QBitArray>
#include <QList>
#include <QSharedPointer>
#include <QSqlQuery>
#include <QString>
#include <QVariant>

/**************************************************************************************************/

class QoDatabaseTable;

/**************************************************************************************************/

class QoSqlExpressionTrait;

typedef QSharedPointer<QoSqlExpressionTrait> QcSqlExpressionPtr;
typedef QList<QcSqlExpressionPtr> QcSqlExpressionList;

class QoSqlExpressionTrait
{
public:
  static QString quote_sql_identifier(const QString & name, SqlFlavour flavour);
  static QString to_sql(const QVariant & value);
  static QString comma_join(const QStringList & strings);
  static QString comma_join(const QcSqlExpressionList & expressions, SqlFlavour flavour);

public:
  virtual QcSqlExpressionPtr clone() const = 0;
  operator QcSqlExpressionPtr () const { return clone(); }

  // Fixme: Min(...)->as(...)
  //   since Function return a pointer
  QcSqlExpressionPtr as(const QString & label) const;

  virtual QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const = 0;
};

/**************************************************************************************************/

// Curiously Recurring Template Pattern
template <typename Derived>
class QoSqlExpressionTraitCrtp : public QoSqlExpressionTrait
{
public:
  virtual QcSqlExpressionPtr clone() const {
    return QcSqlExpressionPtr(new Derived(static_cast<Derived const&>(*this)));
  }
};

// Fixme: for abstract-derived classes
#define CloneableExpression(Class)                      \
  virtual QcSqlExpressionPtr clone() const {            \
    return QcSqlExpressionPtr(new Class(*this));        \
  }

/**************************************************************************************************/

class QoSqlAsExpression : public QoSqlExpressionTraitCrtp<QoSqlAsExpression>
{
public:
  QoSqlAsExpression(const QcSqlExpressionPtr & expression, const QString & label);
  virtual ~QoSqlAsExpression() {}

  operator QcSqlExpressionPtr () const { return QcSqlExpressionPtr(new QoSqlAsExpression(*this)); }

  const QcSqlExpressionPtr & expression() const { return m_expression; }
  const QString & label() const { return m_label; }

  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QcSqlExpressionPtr m_expression;
  QString m_label;
};

/**************************************************************************************************/

class QoSqlField : public QoSqlExpressionTraitCrtp<QoSqlField>
{
public:
  // QoSqlField();
  QoSqlField(const QString & name);
  QoSqlField(const QString & name, const QString & table_name);
  QoSqlField(const QoSqlField & other);
  virtual ~QoSqlField();

  QoSqlField & operator=(const QoSqlField & other);

  const QString & name() const { return m_name; }
  void set_name(const QString & name) { m_name = name; }

  const QString & table_name() const { return m_table_name; }
  void set_table_name(const QString & table_name) { m_table_name = table_name; }

  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

  // Fixme: cf. QoSqlAsExpression
  QString as(const QString & name, SqlFlavour flavour = SqlFlavour::ANSI) const;
  QString as(SqlFlavour flavour = SqlFlavour::ANSI) const; // concat tabl_name

  QcSqlExpressionPtr operator==(const QVariant & value) const;
  QcSqlExpressionPtr operator!=(const QVariant & value) const;

  QcSqlExpressionPtr operator>(const QVariant & value) const;
  QcSqlExpressionPtr operator<(const QVariant & value) const;
  QcSqlExpressionPtr operator>=(const QVariant & value) const;
  QcSqlExpressionPtr operator<=(const QVariant & value) const;

  QcSqlExpressionPtr in(const QVariantList & values) const;
  QcSqlExpressionPtr between(const QVariant & value_min, const QVariant & value_max) const;

  QcSqlExpressionPtr like(const QString & pattern) const;

  QcSqlExpressionPtr is_null() const;
  QcSqlExpressionPtr is_not_null() const;

  QcSqlExpressionPtr asc() const;
  QcSqlExpressionPtr desc() const;

public:
  QString m_name;
  QString m_table_name;
};

typedef QSharedPointer<QoSqlField> QoSqlFieldPtr;
typedef QList<QoSqlField> QcFieldList;

/**************************************************************************************************/

class QoSqlPrepareValue : public QoSqlExpressionTraitCrtp<QoSqlPrepareValue>
{
public:
  // QoSqlPrepareValue();
  QoSqlPrepareValue();
  QoSqlPrepareValue(const QoSqlPrepareValue & other);
  virtual ~QoSqlPrepareValue();

  QoSqlPrepareValue & operator=(const QoSqlPrepareValue & other);

  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;
};

/**************************************************************************************************/

/* Field Expression
 * e.g. field operator value
 */
template<const char * Symbol>
class QoSqlFieldExpression : public QoSqlExpressionTraitCrtp<QoSqlFieldExpression<Symbol>>
{
public:
  QoSqlFieldExpression(const QoSqlField & field, const QVariant & value);
  virtual ~QoSqlFieldExpression() {}

  const QoSqlField & field() const { return m_field; }
  const QVariant & value() const { return m_value; }

  QString symbol() const { return Symbol; }
  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QoSqlField m_field; // Ptr ?
  QVariant m_value;
};

/**************************************************************************************************/

template<const char * Symbol>
class QoSqlFunctionExpression : public QoSqlExpressionTraitCrtp<QoSqlFunctionExpression<Symbol>>
{
public:
  QoSqlFunctionExpression(const QcSqlExpressionPtr & expression);
  virtual ~QoSqlFunctionExpression() {}

  const QcSqlExpressionPtr & expression() const { return m_expression; }

  QString symbol() const { return Symbol; }
  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QcSqlExpressionPtr m_expression;
};

/**************************************************************************************************/

class QoSqlFieldExpressionTwoValue : public QoSqlExpressionTrait // Crtp<QoSqlFieldExpressionTwoValue>
{
public:
  QoSqlFieldExpressionTwoValue(const QoSqlField & field, const QVariant & value1, const QVariant & value2);
  virtual ~QoSqlFieldExpressionTwoValue() {}

  const QoSqlField & field() const { return m_field; }
  const QVariant & value1() const { return m_value1; }
  const QVariant & value2() const { return m_value2; }

protected:
  QoSqlField m_field; // Ptr ?
  QVariant m_value1;
  QVariant m_value2;
};

/**************************************************************************************************/

class QoSqlBetweenExpression : public QoSqlFieldExpressionTwoValue
{
public:
  using QoSqlFieldExpressionTwoValue::QoSqlFieldExpressionTwoValue;

  CloneableExpression(QoSqlBetweenExpression);

  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;
};

/**************************************************************************************************/

class QoSqlFieldExpressionValueList : public QoSqlExpressionTrait // Crtp<QoSqlFieldExpressionValueList>
{
public:
  QoSqlFieldExpressionValueList(const QoSqlField & field, const QVariantList & values);
  virtual ~QoSqlFieldExpressionValueList() {}

  const QoSqlField & field() const { return m_field; }
  const QVariantList & values() const { return m_values; }

  QStringList string_values() const;

protected:
  QoSqlField m_field; // Ptr ?
  QVariantList m_values;
};

/**************************************************************************************************/

class QoSqlInExpression : public QoSqlFieldExpressionValueList
{
public:
  using QoSqlFieldExpressionValueList::QoSqlFieldExpressionValueList;

  CloneableExpression(QoSqlInExpression);

  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;
};

/**************************************************************************************************/

/* Suffix Expression
 * e.g. field IS NULL
 */
template<const char * Suffix>
class QoSqlFieldSuffixExpression : public QoSqlExpressionTraitCrtp<QoSqlFieldSuffixExpression<Suffix>>
{
public:
  QoSqlFieldSuffixExpression(const QoSqlField & field);
  virtual ~QoSqlFieldSuffixExpression() {}

  const QoSqlField & field() const { return m_field; }

  QString suffix() const { return Suffix; }
  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QoSqlField m_field; // Ptr ?
};

/**************************************************************************************************/

/* Unary Expression
 * operator Expression
 * e.g. NOT field like "%foo%"
 */
template<const char * Symbol>
class QoSqlUnaryExpression : public QoSqlExpressionTraitCrtp<QoSqlUnaryExpression<Symbol>>
{
public:
  QoSqlUnaryExpression(const QcSqlExpressionPtr & expression);
  virtual ~QoSqlUnaryExpression() {}

  const QcSqlExpressionPtr & expression() const { return m_expression; }

  QString symbol() const { return Symbol; }
  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QcSqlExpressionPtr m_expression;
};

/**************************************************************************************************/

/* Binary Expression
 *  expression OPERATOR expression
 *  e.g. field1 = 1 AND filed2 = 2
 */
template<const char * Symbol>
class QoSqlBinaryExpression : public QoSqlExpressionTraitCrtp<QoSqlBinaryExpression<Symbol>>
{
public:
  QoSqlBinaryExpression(const QcSqlExpressionPtr & expression1,
                        const QcSqlExpressionPtr & expression2);
  virtual ~QoSqlBinaryExpression() {}

  const QcSqlExpressionPtr & expression1() const { return m_expression1; }
  const QcSqlExpressionPtr & expression2() const { return m_expression2; }

  QString symbol() const { return Symbol; }
  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QcSqlExpressionPtr m_expression1;
  QcSqlExpressionPtr m_expression2;
};

/**************************************************************************************************/

// bool T::operator!() const;
// QcSqlExpressionPtr operator!(const QcSqlExpressionPtr & expression);

// not is a keyword
QcSqlExpressionPtr Not(const QcSqlExpressionPtr & expression);

QcSqlExpressionPtr Count(const QcSqlExpressionPtr & expression);

QcSqlExpressionPtr Min(const QcSqlExpressionPtr & expression);
QcSqlExpressionPtr Max(const QcSqlExpressionPtr & expression);

QcSqlExpressionPtr Sum(const QcSqlExpressionPtr & expression);
QcSqlExpressionPtr Avg(const QcSqlExpressionPtr & expression);

QcSqlExpressionPtr operator&&(const QcSqlExpressionPtr & expression1,
                              const QcSqlExpressionPtr & expression2);
QcSqlExpressionPtr operator||(const QcSqlExpressionPtr & expression1,
                              const QcSqlExpressionPtr & expression2);

/**************************************************************************************************
 *
 * Spatial Functions defined by Open Geospatial Consortium
 *
 */

template<const char * Symbol>
class QoSqlSpatialFunctionExpression : public QoSqlExpressionTraitCrtp<QoSqlFunctionExpression<Symbol>>
{
public:
  QoSqlSpatialFunctionExpression(const QcSqlExpressionPtr & expression, int srid = 4326);
  virtual ~QoSqlSpatialFunctionExpression() {}

  const QcSqlExpressionPtr & expression() const { return m_expression; }

  QString symbol() const { return Symbol; }
  int srid() const { return m_srid; }
  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QcSqlExpressionPtr m_expression;
  int m_srid;
};

QcSqlExpressionPtr ST_GeomFromText();
QcSqlExpressionPtr ST_GeomFromText(const QcSqlExpressionPtr & expression);
QcSqlExpressionPtr ST_AsText(const QcSqlExpressionPtr & expression);

QcSqlExpressionPtr ST_GeomFromWKB();
QcSqlExpressionPtr ST_GeomFromWKB(const QcSqlExpressionPtr & expression);
QcSqlExpressionPtr ST_AsBinary(const QcSqlExpressionPtr & expression);

/**************************************************************************************************/

// Fixme: QoSqlQuery vs QSqlQuery ???
// If we split table / string version
// then we must return this and not *this and we have to deal with -> instead of .
// else we have to use QoDatabaseTable(nullptr, name) and build a fake schema !

class QoSqlQuery
{
public:
  typedef QList<QoSqlQuery> QueryList;

private:
  enum class QueryType {
    None,
    Select,
    Insert,
    Update,
    Delete
  };

  enum class Flags {
    SelectDistinct,
    SelectCount,
    SelectExists,
    NumberOfFlags
  };

  enum class SelectType { // Fixme: ???
    None,
    SelectOne,
    // SelectAll,
  };

public:
  QoSqlQuery();
  QoSqlQuery(QoDatabaseTable * table);
  QoSqlQuery(const QoSqlQuery & other);
  ~QoSqlQuery();

  QoSqlQuery & operator=(const QoSqlQuery & other);

  const QString & table_name() const;
  SqlFlavour sql_flavour() const;

  QueryType query_type() const { return m_query_type; }
  SelectType select_type() const { return m_select_type; }

  // session.query(func.count(distinct(User.name)))
  QoSqlQuery & distinct();

  QoSqlQuery & count();
  QoSqlQuery & exists();

  QoSqlQuery & add_column(const QcSqlExpressionPtr & expression);
  QoSqlQuery & add_column(const QString & name) {
    return add_column(QoSqlField(name)); // Fixme: , table_name()
  }
  QoSqlQuery & add_columns(const QStringList & names);
  QoSqlQuery & add_column(const QcSqlExpressionPtr & expression, const QcSqlExpressionPtr & value_expression);
  QoSqlQuery & add_column(const QString & name, const QcSqlExpressionPtr & value_expression) {
    return add_column(QoSqlField(name), value_expression);
  }

  QoSqlQuery & filter(const QcSqlExpressionPtr & expression);
  QoSqlQuery & filter_by(const QoSqlField & field, const QVariant & value) {
    return filter(field == value);
  }

  QoSqlQuery & group_by(const QoSqlField & field);
  QoSqlQuery & group_by(const QString & name) {
    return group_by(QoSqlField(name));
  }

  QoSqlQuery & order_by(const QcSqlExpressionPtr & expression);
  QoSqlQuery & order_by(const QoSqlField & field) {
    return order_by(QcSqlExpressionPtr(new QoSqlField(field)));
  }

  QoSqlQuery & having(const QcSqlExpressionPtr & expression);

  int get_limit() const { return m_limit; } // versus limit !
  bool unlimited() const { return m_limit == -1; }

  QoSqlQuery & limit(int value); // not set_limit !
  QoSqlQuery & all() { return limit(-1); }
  QoSqlQuery & first() { return limit(1); }
  QoSqlQuery & offset(int value); // not set_offset !
  QoSqlQuery & slice(int start, int stop);

  QoSqlQuery & one(); // Fixme: ???

  // QoSqlQuery & union_(const QoSqlQuery & query); // union is keyword
  // SELECT * FROM (SELECT * FROM (SELECT * FROM X UNION SELECT * FROM y) UNION SELECT * FROM Z)
  // QoSqlQuery & union_(const QueryList & query);
  // SELECT * FROM (SELECT * FROM X UNION SELECT * FROM y UNION SELECT * FROM Z)
  // QoSqlQuery & union_all(const QoSqlQuery & query); // UNION ALL
  // QoSqlQuery & union_all(const QueryList & query);

  QoSqlQuery & insert();
  QoSqlQuery & update();

  QoSqlQuery & delete_(); // delete is a key word
  // QoSqlQuery & update(const QoSqlField & field, const QVariant & value);

  QString to_sql() const;
  operator QString() const { return to_sql(); }

  QSqlQuery exec();

private:
  static QString comma_interrogation_list(int count);
  void set_flags(Flags flag, bool value = true) { m_flags.setBit(static_cast<int>(flag), value); }
  bool get_flags(Flags flag) const { return m_flags[static_cast<int>(flag)]; }
  QStringList field_names(const QcSqlExpressionList & fields) const;
  QStringList field_names(const QcFieldList & fields) const;
  QStringList fields_for_update() const;
  QString table_name_as(const QString & name) const;
  QString quote_sql_identifier(const QString & name) const {
    return QoSqlExpressionTrait::quote_sql_identifier(name, sql_flavour());
  }
  QString insert_values(const SqlFlavour & flavour) const;

  // virtual QString quote_sql_identifier(const QString & name) const;

private:
  QoDatabaseTable * m_table;
  QueryType m_query_type = QueryType::None;
  SelectType m_select_type = SelectType::None;
  QBitArray m_flags;
  QcSqlExpressionList m_fields;
  QHash<QcSqlExpressionPtr, QcSqlExpressionPtr> m_value_expressions;
  QcSqlExpressionPtr m_where = nullptr;
  QcFieldList m_group_by;
  QcSqlExpressionPtr m_having = nullptr;
  QcSqlExpressionList m_order_by;
  int m_limit = -1;
  int m_offset = -1;
};

/**************************************************************************************************/

#ifndef QC_MANUAL_INSTANTIATION
#include "database_query.hxx"
#endif

/**************************************************************************************************/

#endif /* __DATABASE_QUERY_H__ */
