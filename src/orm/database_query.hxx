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

#include "database_query.h" // for checker

/**************************************************************************************************/

#ifndef __DATABASE_QUERY_HXX__
#define __DATABASE_QUERY_HXX__

/**************************************************************************************************/

template<const char * Symbol>
QoSqlFunctionExpression<Symbol>::QoSqlFunctionExpression(const QcSqlExpressionPtr & expression)
  : m_expression(expression)
{}

template<const char * Symbol>
QString
QoSqlFunctionExpression<Symbol>::to_sql(SqlFlavour flavour) const
{
  return Symbol + QString('(') + m_expression->to_sql(flavour) + ')';
};

/**************************************************************************************************/

template<const char * Symbol>
QoSqlFieldExpression<Symbol>::QoSqlFieldExpression(const QoSqlField & field,
                                                   const QVariant & value)
  : m_field(field),
    m_value(value)
{}

template<const char * Symbol>
QString
QoSqlFieldExpression<Symbol>::to_sql(SqlFlavour flavour) const
{
  return m_field.to_sql(flavour) + ' ' + Symbol + ' ' + QoSqlExpressionTrait::to_sql(m_value);
};

/**************************************************************************************************/

template<const char * Suffix>
QoSqlFieldSuffixExpression<Suffix>::QoSqlFieldSuffixExpression(const QoSqlField & field)
  : m_field(field)
{}

template<const char * Suffix>
QString
QoSqlFieldSuffixExpression<Suffix>::to_sql(SqlFlavour flavour) const
{
  return m_field.to_sql(flavour) + ' ' + Suffix;
};

/**************************************************************************************************/

template<const char * Symbol>
QoSqlUnaryExpression<Symbol>::QoSqlUnaryExpression(const QcSqlExpressionPtr & expression)
  : m_expression(expression)
{}

template<const char * Symbol>
QString
QoSqlUnaryExpression<Symbol>::to_sql(SqlFlavour flavour) const
{
  return QString('(') + Symbol + ' ' + m_expression->to_sql(flavour) + ')';
};

/**************************************************************************************************/

template<const char * Symbol>
QoSqlBinaryExpression<Symbol>::QoSqlBinaryExpression(const QcSqlExpressionPtr & expression1,
                                                     const QcSqlExpressionPtr & expression2)
  : m_expression1(expression1),
    m_expression2(expression2)
{}

template<const char * Symbol>
QString
QoSqlBinaryExpression<Symbol>::to_sql(SqlFlavour flavour) const
{
  // QLatin1String(") ")
  // QLatin1String(" (")
  return '(' + m_expression1->to_sql(flavour) + ' ' + Symbol + ' ' + m_expression2->to_sql(flavour) + ')';
};

/**************************************************************************************************/

template<const char * Symbol>
QoSqlSpatialFunctionExpression<Symbol>::QoSqlSpatialFunctionExpression(const QcSqlExpressionPtr & expression, int srid)
  : m_expression(expression),
    m_srid(srid)
{}

template<const char * Symbol>
QString
QoSqlSpatialFunctionExpression<Symbol>::to_sql(SqlFlavour flavour) const
{
  return Symbol + QString('(') + m_expression->to_sql(flavour) +
    QLatin1String(", ") + QString::number(m_srid) + ')';
};

/**************************************************************************************************/

#endif /* __DATABASE_QUERY_HXX__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
