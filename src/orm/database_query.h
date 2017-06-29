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

class QcDatabaseTable;

/**************************************************************************************************/

class QcSqlExpressionTrait;

typedef QSharedPointer<QcSqlExpressionTrait> QcSqlExpressionPtr;
typedef QList<QcSqlExpressionPtr> QcSqlExpressionList;

class QcSqlExpressionTrait
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
class QcSqlExpressionTraitCrtp : public QcSqlExpressionTrait
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

class QcSqlAsExpression : public QcSqlExpressionTraitCrtp<QcSqlAsExpression>
{
public:
  QcSqlAsExpression(const QcSqlExpressionPtr & expression, const QString & label);
  virtual ~QcSqlAsExpression() {}

  operator QcSqlExpressionPtr () const { return QcSqlExpressionPtr(new QcSqlAsExpression(*this)); }

  const QcSqlExpressionPtr & expression() const { return m_expression; }
  const QString & label() const { return m_label; }

  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QcSqlExpressionPtr m_expression;
  QString m_label;
};

/**************************************************************************************************/

class QcSqlField : public QcSqlExpressionTraitCrtp<QcSqlField>
{
public:
  // QcSqlField();
  QcSqlField(const QString & name);
  QcSqlField(const QString & name, const QString & table_name);
  QcSqlField(const QcSqlField & other);
  virtual ~QcSqlField();

  QcSqlField & operator=(const QcSqlField & other);

  const QString & name() const { return m_name; }
  void set_name(const QString & name) { m_name = name; }

  const QString & table_name() const { return m_table_name; }
  void set_table_name(const QString & table_name) { m_table_name = table_name; }

  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

  // Fixme: cf. QcSqlAsExpression
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

typedef QSharedPointer<QcSqlField> QcSqlFieldPtr;
typedef QList<QcSqlField> QcFieldList;

/**************************************************************************************************/

class QcSqlPrepareValue : public QcSqlExpressionTraitCrtp<QcSqlPrepareValue>
{
public:
  // QcSqlPrepareValue();
  QcSqlPrepareValue();
  QcSqlPrepareValue(const QcSqlPrepareValue & other);
  virtual ~QcSqlPrepareValue();

  QcSqlPrepareValue & operator=(const QcSqlPrepareValue & other);

  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;
};

/**************************************************************************************************/

/* Field Expression
 * e.g. field operator value
 */
template<const char * Symbol>
class QcSqlFieldExpression : public QcSqlExpressionTraitCrtp<QcSqlFieldExpression<Symbol>>
{
public:
  QcSqlFieldExpression(const QcSqlField & field, const QVariant & value);
  virtual ~QcSqlFieldExpression() {}

  const QcSqlField & field() const { return m_field; }
  const QVariant & value() const { return m_value; }

  QString symbol() const { return Symbol; }
  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QcSqlField m_field; // Ptr ?
  QVariant m_value;
};

/**************************************************************************************************/

template<const char * Symbol>
class QcSqlFunctionExpression : public QcSqlExpressionTraitCrtp<QcSqlFunctionExpression<Symbol>>
{
public:
  QcSqlFunctionExpression(const QcSqlExpressionPtr & expression);
  virtual ~QcSqlFunctionExpression() {}

  const QcSqlExpressionPtr & expression() const { return m_expression; }

  QString symbol() const { return Symbol; }
  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QcSqlExpressionPtr m_expression;
};

/**************************************************************************************************/

class QcSqlFieldExpressionTwoValue : public QcSqlExpressionTrait // Crtp<QcSqlFieldExpressionTwoValue>
{
public:
  QcSqlFieldExpressionTwoValue(const QcSqlField & field, const QVariant & value1, const QVariant & value2);
  virtual ~QcSqlFieldExpressionTwoValue() {}

  const QcSqlField & field() const { return m_field; }
  const QVariant & value1() const { return m_value1; }
  const QVariant & value2() const { return m_value2; }

protected:
  QcSqlField m_field; // Ptr ?
  QVariant m_value1;
  QVariant m_value2;
};

/**************************************************************************************************/

class QcSqlBetweenExpression : public QcSqlFieldExpressionTwoValue
{
public:
  using QcSqlFieldExpressionTwoValue::QcSqlFieldExpressionTwoValue;

  CloneableExpression(QcSqlBetweenExpression);

  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;
};

/**************************************************************************************************/

class QcSqlFieldExpressionValueList : public QcSqlExpressionTrait // Crtp<QcSqlFieldExpressionValueList>
{
public:
  QcSqlFieldExpressionValueList(const QcSqlField & field, const QVariantList & values);
  virtual ~QcSqlFieldExpressionValueList() {}

  const QcSqlField & field() const { return m_field; }
  const QVariantList & values() const { return m_values; }

  QStringList string_values() const;

protected:
  QcSqlField m_field; // Ptr ?
  QVariantList m_values;
};

/**************************************************************************************************/

class QcSqlInExpression : public QcSqlFieldExpressionValueList
{
public:
  using QcSqlFieldExpressionValueList::QcSqlFieldExpressionValueList;

  CloneableExpression(QcSqlInExpression);

  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;
};

/**************************************************************************************************/

/* Suffix Expression
 * e.g. field IS NULL
 */
template<const char * Suffix>
class QcSqlFieldSuffixExpression : public QcSqlExpressionTraitCrtp<QcSqlFieldSuffixExpression<Suffix>>
{
public:
  QcSqlFieldSuffixExpression(const QcSqlField & field);
  virtual ~QcSqlFieldSuffixExpression() {}

  const QcSqlField & field() const { return m_field; }

  QString suffix() const { return Suffix; }
  QString to_sql(SqlFlavour flavour = SqlFlavour::ANSI) const;

private:
  QcSqlField m_field; // Ptr ?
};

/**************************************************************************************************/

/* Unary Expression
 * operator Expression
 * e.g. NOT field like "%foo%"
 */
template<const char * Symbol>
class QcSqlUnaryExpression : public QcSqlExpressionTraitCrtp<QcSqlUnaryExpression<Symbol>>
{
public:
  QcSqlUnaryExpression(const QcSqlExpressionPtr & expression);
  virtual ~QcSqlUnaryExpression() {}

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
class QcSqlBinaryExpression : public QcSqlExpressionTraitCrtp<QcSqlBinaryExpression<Symbol>>
{
public:
  QcSqlBinaryExpression(const QcSqlExpressionPtr & expression1,
                        const QcSqlExpressionPtr & expression2);
  virtual ~QcSqlBinaryExpression() {}

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
class QcSqlSpatialFunctionExpression : public QcSqlExpressionTraitCrtp<QcSqlFunctionExpression<Symbol>>
{
public:
  QcSqlSpatialFunctionExpression(const QcSqlExpressionPtr & expression, int srid = 4326);
  virtual ~QcSqlSpatialFunctionExpression() {}

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

// Fixme: QcSqlQuery vs QSqlQuery ???
// If we split table / string version
// then we must return this and not *this and we have to deal with -> instead of .
// else we have to use QcDatabaseTable(nullptr, name) and build a fake schema !

class QcSqlQuery
{
public:
  typedef QList<QcSqlQuery> QueryList;

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
  QcSqlQuery();
  QcSqlQuery(QcDatabaseTable * table);
  QcSqlQuery(const QcSqlQuery & other);
  ~QcSqlQuery();

  QcSqlQuery & operator=(const QcSqlQuery & other);

  const QString & table_name() const;
  SqlFlavour sql_flavour() const;

  QueryType query_type() const { return m_query_type; }
  SelectType select_type() const { return m_select_type; }

  // session.query(func.count(distinct(User.name)))
  QcSqlQuery & distinct();

  QcSqlQuery & count();
  QcSqlQuery & exists();

  QcSqlQuery & add_column(const QcSqlExpressionPtr & expression);
  QcSqlQuery & add_column(const QString & name) {
    return add_column(QcSqlField(name)); // Fixme: , table_name()
  }
  QcSqlQuery & add_columns(const QStringList & names);
  QcSqlQuery & add_column(const QcSqlExpressionPtr & expression, const QcSqlExpressionPtr & value_expression);
  QcSqlQuery & add_column(const QString & name, const QcSqlExpressionPtr & value_expression) {
    return add_column(QcSqlField(name), value_expression);
  }

  QcSqlQuery & filter(const QcSqlExpressionPtr & expression);
  QcSqlQuery & filter_by(const QcSqlField & field, const QVariant & value) {
    return filter(field == value);
  }

  QcSqlQuery & group_by(const QcSqlField & field);
  QcSqlQuery & group_by(const QString & name) {
    return group_by(QcSqlField(name));
  }

  QcSqlQuery & order_by(const QcSqlExpressionPtr & expression);
  QcSqlQuery & order_by(const QcSqlField & field) {
    return order_by(QcSqlExpressionPtr(new QcSqlField(field)));
  }

  QcSqlQuery & having(const QcSqlExpressionPtr & expression);

  int get_limit() const { return m_limit; } // versus limit !
  bool unlimited() const { return m_limit == -1; }

  QcSqlQuery & limit(int value); // not set_limit !
  QcSqlQuery & all() { return limit(-1); }
  QcSqlQuery & first() { return limit(1); }
  QcSqlQuery & offset(int value); // not set_offset !
  QcSqlQuery & slice(int start, int stop);

  QcSqlQuery & one(); // Fixme: ???

  // QcSqlQuery & union_(const QcSqlQuery & query); // union is keyword
  // SELECT * FROM (SELECT * FROM (SELECT * FROM X UNION SELECT * FROM y) UNION SELECT * FROM Z)
  // QcSqlQuery & union_(const QueryList & query);
  // SELECT * FROM (SELECT * FROM X UNION SELECT * FROM y UNION SELECT * FROM Z)
  // QcSqlQuery & union_all(const QcSqlQuery & query); // UNION ALL
  // QcSqlQuery & union_all(const QueryList & query);

  QcSqlQuery & insert();
  QcSqlQuery & update();

  QcSqlQuery & delete_(); // delete is a key word
  // QcSqlQuery & update(const QcSqlField & field, const QVariant & value);

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
    return QcSqlExpressionTrait::quote_sql_identifier(name, sql_flavour());
  }
  QString insert_values(const SqlFlavour & flavour) const;

  // virtual QString quote_sql_identifier(const QString & name) const;

private:
  QcDatabaseTable * m_table;
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

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
