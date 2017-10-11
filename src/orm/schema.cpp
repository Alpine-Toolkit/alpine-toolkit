/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
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
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "schema.h"
#include "alpine_toolkit.h"

#include<utility>

#include<QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QoSchemaFieldTrait::QoSchemaFieldTrait(FieldType field_type)
  : m_field_type(field_type),
    // m_external_creation(false),
    m_name(),
    m_sql_name(),
    m_json_name(),
    m_qt_type(),
    m_sql_type(),
    m_title(),
    m_description()
{}

QoSchemaFieldTrait::QoSchemaFieldTrait(FieldType field_type,
                                       const QString & name,
                                       const QString & qt_type,
                                       const QString & sql_type,
                                       const QString & sql_name,
                                       const QString & json_name,
                                       const QString & title,
                                       const QString & description
                                       )
  : m_field_type(field_type),
    // m_external_creation(false),
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

QoSchemaFieldTrait::QoSchemaFieldTrait(const QoSchemaFieldTrait & other)
  : m_schema(other.m_schema),
    m_field_type(other.m_field_type),
    m_position(other.m_position),
    m_name(other.m_name),
    m_sql_name(other.m_sql_name),
    m_json_name(other.m_json_name),
    m_qt_type(other.m_qt_type),
    m_sql_type(other.m_sql_type),
    m_title(other.m_title),
    m_description(other.m_description),
    m_nullable(other.m_nullable),
    m_sql_column_ctor(other.m_sql_column_ctor),
    m_sql_value_ctor(other.m_sql_value_ctor),
    m_sql_value_getter(other.m_sql_value_getter)
{}

QoSchemaFieldTrait::~QoSchemaFieldTrait()
{
  // qATInfo() << "~QoSchemaFieldTrait" << m_name;
}

QoSchemaFieldTrait &
QoSchemaFieldTrait::operator=(const QoSchemaFieldTrait & other)
{
  if (this != &other) {
    m_schema = other.m_schema;
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
    m_sql_column_ctor = other.m_sql_column_ctor;
    m_sql_value_ctor = other.m_sql_value_ctor;
    m_sql_value_getter = other.m_sql_value_getter;
  }

  return *this;
}

void
QoSchemaFieldTrait::set_position(QoSchema * schema, int value)
{
  m_schema = schema;
  m_position = value;
}

bool
QoSchemaFieldTrait::is_rowid() const
{
  return is_primary_key()
    and m_position == 0
    and m_sql_type == QLatin1String("integer");
}

QoSqlField
QoSchemaFieldTrait::to_sql_field() const
{
  if (m_schema)
    return QoSqlField(m_schema->name(), m_name);
  else
    return QoSqlField(QString(), m_name);
}

QString
QoSchemaFieldTrait::to_sql_definition(const QStringList & parts) const
{
  QStringList _parts;
  _parts << m_sql_name << m_sql_type;
  if (not m_nullable)
    _parts << QLatin1String("NOT NULL");
  _parts << parts;
  return _parts.join(' ');
}

/**************************************************************************************************/

QoSchemaField::QoSchemaField()
  : QoSchemaFieldTrait()
{}

QoSchemaField::QoSchemaField(const QString & name,
                             const QString & qt_type,
                             const QString & sql_type,
                             const QString & sql_name,
                             const QString & json_name,
                             const QString & title,
                             const QString & description
                             )
  : QoSchemaFieldTrait(FieldType::Normal,
                       name,
                       qt_type,
                       sql_type,
                       sql_name,
                       json_name,
                       title,
                       description)
{}

QoSchemaField::QoSchemaField(const QoSchemaField & other)
  : QoSchemaFieldTrait(other),
    m_default(other.m_default)
{}

QoSchemaField::~QoSchemaField()
{}

QoSchemaField &
QoSchemaField::operator=(const QoSchemaField & other)
{
  if (this != &other) {
    QoSchemaFieldTrait::operator=(other);
    m_default = other.m_default;
  }

  return *this;
}

QString
QoSchemaField::to_sql_definition() const
{
  QStringList parts;
  if (m_default.isValid())
    parts << m_default.toString(); // Fixme: could fail !
  return QoSchemaFieldTrait::to_sql_definition(parts);
}

/**************************************************************************************************/

QoSchemaPrimaryKey::QoSchemaPrimaryKey()
  : QoSchemaFieldTrait(FieldType::PrimaryKey)
{}

QoSchemaPrimaryKey::QoSchemaPrimaryKey(const QString & name,
                                       const QString & qt_type,
                                       const QString & sql_type,
                                       const QString & sql_name,
                                       const QString & json_name,
                                       const QString & title,
                                       const QString & description
                                       )
  : QoSchemaFieldTrait(FieldType::PrimaryKey,
                       name,
                       qt_type,
                       sql_type,
                       sql_name,
                       json_name,
                       title,
                       description)
{}

QoSchemaPrimaryKey::QoSchemaPrimaryKey(const QoSchemaPrimaryKey & other)
  : QoSchemaFieldTrait(other),
    m_autoincrement(other.m_autoincrement),
    m_unique(other.m_unique)
{}

QoSchemaPrimaryKey::~QoSchemaPrimaryKey()
{}

QoSchemaPrimaryKey &
QoSchemaPrimaryKey::operator=(const QoSchemaPrimaryKey & other)
{
  if (this != &other) {
    QoSchemaFieldTrait::operator=(other);
    m_autoincrement = other.m_autoincrement;
    m_unique = other.m_unique;
  }

  return *this;
}

QString
QoSchemaPrimaryKey::to_sql_definition() const
{
  QStringList parts;
  // parts << QLatin1String("PRIMARY KEY");
  if (m_autoincrement)
    parts << QLatin1String("AUTOINCREMENT");
  if (m_unique)
    parts << QLatin1String("UNIQUE");
  return QoSchemaFieldTrait::to_sql_definition(parts);
}

/**************************************************************************************************/

QoSchemaForeignKey::QoSchemaForeignKey()
  : QoSchemaField(),
    m_referenced_table(),
    m_referenced_field_name(),
    m_referenced_schema()
{
  set_field_type(FieldType::ForeignKey); // Fixme: overwrite Normal, ok ?
}

QoSchemaForeignKey::QoSchemaForeignKey(const QString & name,
                                       const QString & reference,
                                       const QString & qt_type,
                                       const QString & sql_type,
                                       const QString & sql_name,
                                       const QString & json_name,
                                       const QString & title,
                                       const QString & description
                                       )
  : QoSchemaField(name,
                  qt_type,
                  sql_type,
                  sql_name,
                  json_name,
                  title,
                  description),
    m_referenced_table(),
    m_referenced_field_name(),
    m_referenced_schema()
{
  set_field_type(FieldType::ForeignKey); // Fixme: overwrite Normal, ok ?

  int point_location = reference.indexOf('.');
  if (point_location > 0) {
    m_referenced_table = reference.left(point_location);
    m_referenced_field_name = reference.mid(point_location +1);
  }
}

QoSchemaForeignKey::QoSchemaForeignKey(const QoSchemaForeignKey & other)
  : QoSchemaField(other),
    m_referenced_table(other.m_referenced_table),
    m_referenced_field_name(other.m_referenced_field_name),
    m_referenced_schema(other.m_referenced_schema)
{}

QoSchemaForeignKey::~QoSchemaForeignKey()
{}

QoSchemaForeignKey &
QoSchemaForeignKey::operator=(const QoSchemaForeignKey & other)
{
  if (this != &other) {
    QoSchemaField::operator=(other);
    m_referenced_table = other.m_referenced_table;
    m_referenced_field_name = other.m_referenced_field_name;
    m_referenced_schema = other.m_referenced_schema;
  }

  return *this;
}

QSharedPointer<const QoSchemaFieldTrait>
QoSchemaForeignKey::referenced_field() const
{
  if (m_referenced_schema.isNull())
    return nullptr;
  else
    return (*m_referenced_schema)[m_referenced_field_name];
}

/**************************************************************************************************/

std::atomic<int> QoSchema::m_last_schema_id(0);

QoSchema::QoSchema()
  : m_schema_id(new_schema_id()),
    m_name(),
    m_table_name(),
    // m_sql_table_option(),
    m_fields(),
    m_field_map(),
    m_field_names(),
    m_field_names_without_rowid()
{}

QoSchema::QoSchema(const QString & name,
                   const QString & table_name,
                   bool without_rowid
                   //const QString & sql_table_option
                   )
  : m_schema_id(new_schema_id()),
    m_name(name),
    m_table_name(table_name),
    // m_sql_table_option(sql_table_option),
    m_without_rowid(without_rowid),
    m_fields(),
    m_field_map(),
    m_field_names(),
    m_field_names_without_rowid()
{
  if (table_name.isEmpty())
    m_table_name = m_name;
}

QoSchema::QoSchema(const QoSchema & other)
  : m_schema_id(other.m_schema_id),
    m_name(other.m_name),
    m_table_name(other.m_table_name),
    // m_sql_table_option(other.m_sql_table_option),
    m_without_rowid(other.m_without_rowid),
    m_has_rowid_primary_key(other.m_has_rowid_primary_key),
    m_has_foreign_keys(other.m_has_foreign_keys),
    m_has_sql_value_ctor(other.m_has_sql_value_ctor),
    m_fields(),
    m_fields_without_rowid(),
    m_field_map(),
    m_field_names(),
    m_field_names_without_rowid()
{
  copy_fields(other);
}

QoSchema::~QoSchema()
{}

QoSchema &
QoSchema::operator=(const QoSchema & other)
{
  if (this != &other) {
    m_schema_id = other.m_schema_id;
    m_name = other.m_name;
    m_table_name = other.m_table_name;
    // m_sql_table_option = other.m_sql_table_option;
    m_without_rowid = other.m_without_rowid;
    m_has_rowid_primary_key = other.m_has_rowid_primary_key;
    m_has_foreign_keys = other.m_has_foreign_keys;
    m_has_sql_value_ctor = other.m_has_sql_value_ctor;
    copy_fields(other);
  }

  return *this;
}

void
QoSchema::add_field(const QoSchemaFieldTrait & field)
{
  m_fields << QoSchemaFieldPtr(field.clone());
  QoSchemaFieldPtr owned_field = m_fields.last();
  owned_field->set_position(this, m_fields.size() -1);
  m_field_map.insert(owned_field->name(), owned_field);
  const QString & name = owned_field->sql_name();
  m_field_names << name;
  if (owned_field->is_rowid())
    m_has_rowid_primary_key = true;
  else {
    m_fields_without_rowid << owned_field;
    m_field_names_without_rowid << name;
  }
  if (owned_field->has_sql_value_ctor())
    m_has_sql_value_ctor = true;
}

QoSchema &
QoSchema::operator<<(const QoSchemaFieldTrait & field)
{
  add_field(field);
  return *this;
}

void
QoSchema::copy_fields(const QoSchema & other)
{
  m_fields.clear();
  m_fields_without_rowid.clear();
  m_field_map.clear();
  m_field_names.clear();
  m_field_names_without_rowid.clear();

  for (const auto & field : other.m_fields)
    add_field(*field);
}

QStringList
QoSchema::prefixed_field_names() const
{
  QStringList string_list;

  for (const auto & name : m_field_names)
    string_list << m_name + '_' + name;

  return string_list;
}

QStringList
QoSchema::to_sql_definition() const
{
  QStringList sql_queries;

  // CREATE [TEMP|TEMPORARY] TABLE [IF NOT EXISTS]
  QString sql_query = QLatin1String("CREATE TABLE ");
  sql_query += m_table_name;
  sql_query += QLatin1String(" (\n  ");

  QStringList sql_fields;
  QStringList primary_keys;
  QList<QoSchemaForeignKey *> foreign_keys;
  for (const auto & field : m_fields) {
    if (not field->has_sql_column_ctor())
      sql_fields << field->to_sql_definition();
    if (field->is_primary_key())
      primary_keys << field->name();
    else if (field->is_foreign_key())
      foreign_keys << dynamic_cast<QoSchemaForeignKey *>(field.data());
  }
  sql_query += sql_fields.join(QLatin1String(",\n  "));

  if (primary_keys.size())
    sql_query += QLatin1String(",\n  PRIMARY KEY (") + primary_keys.join(QLatin1String(", ")) + QLatin1String(")");
  for (const auto * foreign_key : foreign_keys)
    sql_query += QLatin1String(",\n  FOREIGN KEY (") + foreign_key->name() +
      QLatin1String(") REFERENCES ") + foreign_key->referenced_table() + '(' + foreign_key->referenced_field_name() + QLatin1String(")");
  sql_query += QLatin1String("\n)");

  if (m_without_rowid)
    sql_query += QLatin1String(" WITHOUT ROWID");
  // if (not m_sql_table_option.isEmpty()) {
  //   sql_query += ' ';
  //   sql_query += m_sql_table_option;
  // }

  sql_queries << sql_query;

  for (const auto & field : m_fields) {
    if (field->has_sql_column_ctor())
      sql_queries << field->sql_column_ctor();
  }

  return sql_queries;
}

/**************************************************************************************************/

// QC_END_NAMESPACE
