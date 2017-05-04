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

#include<utility>

#include<QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QcSchemaFieldTrait::QcSchemaFieldTrait(FieldType field_type)
  : m_field_type(field_type),
    m_name(),
    m_sql_name(),
    m_json_name(),
    m_qt_type(),
    m_sql_type(),
    m_title(),
    m_description()
{}

QcSchemaFieldTrait::QcSchemaFieldTrait(FieldType field_type,
                                       const QString & name,
                                       const QString & qt_type,
                                       const QString & sql_type,
                                       const QString & sql_name,
                                       const QString & json_name,
                                       const QString & title,
                                       const QString & description
                                       )
  : m_field_type(field_type),
    m_name(name),
    m_sql_name(),
    m_json_name(),
    m_qt_type(qt_type),
    m_sql_type(sql_type),
    m_title(title),
    m_description(description)
{
  m_sql_name = sql_name.isEmpty() ? name : sql_name;
  m_json_name = json_name.isEmpty() ? name : json_name;
}

QcSchemaFieldTrait::QcSchemaFieldTrait(const QcSchemaFieldTrait & other)
  : m_field_type(other.m_field_type),
    m_position(other.m_position),
    m_name(other.m_name),
    m_sql_name(other.m_sql_name),
    m_json_name(other.m_json_name),
    m_qt_type(other.m_qt_type),
    m_sql_type(other.m_sql_type),
    m_title(other.m_title),
    m_description(other.m_description),
    m_nullable(other.m_nullable)
{}

QcSchemaFieldTrait::~QcSchemaFieldTrait()
{
  // qInfo() << "~QcSchemaFieldTrait" << m_name;
}

QcSchemaFieldTrait &
QcSchemaFieldTrait::operator=(const QcSchemaFieldTrait & other)
{
  if (this != &other) {
    m_field_type = other.m_field_type;
    m_position = other.m_position;
    m_name = other.m_name;
    m_sql_name = other.m_sql_name;
    m_json_name = other.m_json_name;
    m_qt_type = other.m_qt_type;
    m_sql_type = other.m_sql_type;
    m_title = other.m_title;
    m_description = other.m_description;
    m_nullable = other.m_nullable;
  }

  return *this;
}

QString
QcSchemaFieldTrait::to_sql_definition(const QStringList & parts) const
{
  QStringList _parts;
  _parts << m_sql_name << m_sql_type;
  if (not m_nullable)
    _parts << QLatin1String("NOT NULL");
  _parts << parts;
  return _parts.join(' ');
}

/**************************************************************************************************/

QcSchemaField::QcSchemaField()
  : QcSchemaFieldTrait()
{}

QcSchemaField::QcSchemaField(const QString & name,
                             const QString & qt_type,
                             const QString & sql_type,
                             const QString & sql_name,
                             const QString & json_name,
                             const QString & title,
                             const QString & description
                             )
  : QcSchemaFieldTrait(FieldType::Normal,
                       name,
                       qt_type,
                       sql_type,
                       sql_name,
                       json_name,
                       title,
                       description)
{}

QcSchemaField::QcSchemaField(const QcSchemaField & other)
  : QcSchemaFieldTrait(other),
    m_default(other.m_default)
{}

QcSchemaField::~QcSchemaField()
{}

QcSchemaField &
QcSchemaField::operator=(const QcSchemaField & other)
{
  if (this != &other) {
    QcSchemaFieldTrait::operator=(other);
    m_default = other.m_default;
  }

  return *this;
}

QString
QcSchemaField::to_sql_definition() const
{
  QStringList parts;
  if (m_default.isValid())
    parts << m_default.toString(); // Fixme: could fail !
  return QcSchemaFieldTrait::to_sql_definition(parts);
}

/**************************************************************************************************/

QcSchemaPrimaryKey::QcSchemaPrimaryKey()
  : QcSchemaFieldTrait(FieldType::PrimaryKey)
{}

QcSchemaPrimaryKey::QcSchemaPrimaryKey(const QString & name,
                                       const QString & qt_type,
                                       const QString & sql_type,
                                       const QString & sql_name,
                                       const QString & json_name,
                                       const QString & title,
                                       const QString & description
                                       )
  : QcSchemaFieldTrait(FieldType::PrimaryKey,
                       name,
                       qt_type,
                       sql_type,
                       sql_name,
                       json_name,
                       title,
                       description)
{}

QcSchemaPrimaryKey::QcSchemaPrimaryKey(const QcSchemaPrimaryKey & other)
  : QcSchemaFieldTrait(other),
    m_autoincrement(other.m_autoincrement),
    m_unique(other.m_unique)
{}

QcSchemaPrimaryKey::~QcSchemaPrimaryKey()
{}

QcSchemaPrimaryKey &
QcSchemaPrimaryKey::operator=(const QcSchemaPrimaryKey & other)
{
  if (this != &other) {
    QcSchemaFieldTrait::operator=(other);
    m_autoincrement = other.m_autoincrement;
    m_unique = other.m_unique;
  }

  return *this;
}

QString
QcSchemaPrimaryKey::to_sql_definition() const
{
  QStringList parts;
  parts << QLatin1String("PRIMARY KEY");
  if (m_autoincrement)
    parts << QLatin1String("AUTOINCREMENT");
  if (m_unique)
    parts << QLatin1String("UNIQUE");
  return QcSchemaFieldTrait::to_sql_definition(parts);
}

/**************************************************************************************************/

QcSchemaForeignKey::QcSchemaForeignKey()
  : QcSchemaField()
{
  set_field_type(FieldType::ForeignKey); // Fixme: overwrite Normal, ok ?
}

QcSchemaForeignKey::QcSchemaForeignKey(const QString & name,
                                       const QString & qt_type,
                                       const QString & sql_type,
                                       const QString & sql_name,
                                       const QString & json_name,
                                       const QString & title,
                                       const QString & description
                                       )
  : QcSchemaField(name,
                  qt_type,
                  sql_type,
                  sql_name,
                  json_name,
                  title,
                  description)
{
  set_field_type(FieldType::ForeignKey); // Fixme: overwrite Normal, ok ?
}

QcSchemaForeignKey::QcSchemaForeignKey(const QcSchemaForeignKey & other)
  : QcSchemaField(other)
{}

QcSchemaForeignKey::~QcSchemaForeignKey()
{}

QcSchemaForeignKey &
QcSchemaForeignKey::operator=(const QcSchemaForeignKey & other)
{
  if (this != &other) {
    QcSchemaField::operator=(other);
  }

  return *this;
}

/**************************************************************************************************/

std::atomic<int> QcSchema::m_last_schema_id(0);

QcSchema::QcSchema()
  : m_schema_id(new_schema_id()),
    m_name(),
    m_table_name(),
    // m_sql_table_option(),
    m_fields(),
    m_field_map()
{}

QcSchema::QcSchema(const QString & name,
                   const QString & table_name,
                   bool without_rowid
                   //const QString & sql_table_option
                   )
  : m_schema_id(new_schema_id()),
    m_name(name),
    m_table_name(table_name),
    // m_sql_table_option(sql_table_option),
    m_without_rowid(without_rowid),
    m_has_rowid(not without_rowid),
    m_fields(),
    m_field_map()
{
  if (table_name.isEmpty())
    m_table_name = m_name;
}

QcSchema::QcSchema(const QcSchema & other)
  : m_schema_id(other.m_schema_id),
    m_name(other.m_name),
    m_table_name(other.m_table_name),
    // m_sql_table_option(other.m_sql_table_option),
    m_without_rowid(other.m_without_rowid),
    m_has_rowid(other.m_has_rowid),
    m_fields(other.m_fields),
    m_field_map(other.m_field_map)
{}

QcSchema::~QcSchema()
{}

QcSchema &
QcSchema::operator=(const QcSchema & other)
{
  if (this != &other) {
    m_schema_id = other.m_schema_id;
    m_name = other.m_name;
    m_table_name = other.m_table_name;
    // m_sql_table_option = other.m_sql_table_option;
    m_without_rowid = other.m_without_rowid;
    m_has_rowid = other.m_has_rowid;
    m_fields = other.m_fields;
    m_field_map = other.m_field_map;
  }

  return *this;
}

void
QcSchema::add_field(QcSchemaFieldTrait * field)
{
  m_fields << QSharedPointer<QcSchemaFieldTrait>(field);
  QSharedPointer<QcSchemaFieldTrait> owned_field = m_fields.last();
  owned_field->set_position(m_fields.size() -1);
  m_field_map.insert(owned_field->name(), owned_field);
  if (m_has_rowid and field->is_primary_key())
    m_has_rowid = false;
  if (field->is_foreign_key())
    m_has_rowid = true;
}

QcSchema &
QcSchema::operator<<(QcSchemaFieldTrait * field)
{
  add_field(field);
  return *this;
}

QString
QcSchema::to_sql_definition() const
{
  QString sql_query = QLatin1String("CREATE TABLE ");
  sql_query += m_table_name;
  sql_query += QLatin1String(" (");
  QStringList sql_fields;
  for (const auto & field : m_fields)
    sql_fields << field->to_sql_definition();
  sql_query += sql_fields.join(QLatin1String(", "));
  sql_query += ')';
  if (m_without_rowid)
    sql_query += QLatin1String(" WITHOUT ROWID");
  // if (not m_sql_table_option.isEmpty()) {
  //   sql_query += ' ';
  //   sql_query += m_sql_table_option;
  // }
  return sql_query;
}

/**************************************************************************************************/

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
