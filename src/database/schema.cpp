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

#include "database/schema.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QcSchemaField::QcSchemaField()
  : m_name(),
    m_sql_name(),
    m_json_name(),
    m_qt_type(),
    m_sql_type(),
    m_sql_qualifier(),
    m_title(),
    m_description(),
    m_position(-1)
{}

QcSchemaField::QcSchemaField(const QString & name,
                             const QString & qt_type,
                             const QString & sql_type,
                             const QString & sql_qualifier,
                             const QString & sql_name,
                             const QString & json_name,
                             const QString & title,
                             const QString & description
                             )
  : m_name(name),
    m_sql_name(),
    m_json_name(),
    m_qt_type(qt_type),
    m_sql_type(sql_type),
    m_sql_qualifier(sql_qualifier),
    m_title(title),
    m_description(description),
    m_position(-1)
{
  m_sql_name = sql_name.isEmpty() ? name : sql_name;
  m_json_name = json_name.isEmpty() ? name : json_name;
}

QcSchemaField::QcSchemaField(const QcSchemaField & other)
  : m_name(other.m_name),
    m_sql_name(other.m_sql_name),
    m_json_name(other.m_json_name),
    m_qt_type(other.m_qt_type),
    m_sql_type(other.m_sql_type),
    m_sql_qualifier(other.m_sql_qualifier),
    m_title(other.m_title),
    m_description(other.m_description),
    m_position(other.m_position)
{}

QcSchemaField::~QcSchemaField()
{}

QcSchemaField &
QcSchemaField::operator=(const QcSchemaField & other)
{
  if (this != &other) {
    m_name = other.m_name;
    m_sql_name = other.m_sql_name;
    m_json_name = other.m_json_name;
    m_qt_type = other.m_qt_type;
    m_sql_type = other.m_sql_type;
    m_sql_qualifier = other.m_sql_qualifier;
    m_title = other.m_title;
    m_description = other.m_description;
    m_position = other.m_position;
  }

  return *this;
}

QString
QcSchemaField::to_sql_definition() const
{
  QStringList parts;
  parts << m_sql_name << m_sql_type;
  if (not m_sql_qualifier.isEmpty())
    parts << m_sql_qualifier;
  return parts.join(' ');
}

/**************************************************************************************************/

QcSchema::QcSchema()
  : m_name(),
    m_fields()
{}

QcSchema::QcSchema(const QString & name)
  : m_name(name),
    m_fields()
{}

QcSchema::QcSchema(const QcSchema & other)
  : m_name(other.m_name),
    m_fields(other.m_fields)
{}

QcSchema::~QcSchema()
{}

QcSchema &
QcSchema::operator=(const QcSchema & other)
{
  if (this != &other) {
    m_name = other.m_name;
    m_fields = other.m_fields;
  }

  return *this;
}

void
QcSchema::add_field(const QcSchemaField & field)
{
  m_fields << field;
  m_fields.last().set_position(m_fields.size() -1);
}

QcSchema &
QcSchema::operator<<(const QcSchemaField & field)
{
  add_field(field);
  return *this;
}

/**************************************************************************************************/

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
