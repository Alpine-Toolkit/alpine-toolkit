// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __SCHEMA_H__
#define __SCHEMA_H__

/**************************************************************************************************/

#include "orm/database_query.h"

#include <QHash>
#include <QList>
#include <QMetaType>
#include <QSharedPointer>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QVariant>

#include <atomic>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

/*
 * To complete:
 *  field enum to get position efficiently
 *
 */

/**************************************************************************************************/

class QoSchema;
typedef QSharedPointer<QoSchema> QoSchemaPtr;

/**************************************************************************************************/

// Fixme: template ?
class QoSchemaFieldTrait
{
protected:
  enum FieldType {
    Normal,
    PrimaryKey,
    ForeignKey
  };

public:
  QoSchemaFieldTrait(FieldType field_type = FieldType::Normal);
  QoSchemaFieldTrait(FieldType field_type,
                     const QString & name,
                     const QString & qt_type, // ???
                     const QString & sql_type,
                     const QString & sql_name,
                     const QString & json_name,
                     const QString & title,
                     const QString & description
                     );
  QoSchemaFieldTrait(const QoSchemaFieldTrait & other);
  virtual ~QoSchemaFieldTrait();

  virtual QoSchemaFieldTrait * clone() const = 0;

  QoSchemaFieldTrait & operator=(const QoSchemaFieldTrait & other);

  bool is_rowid() const;

  bool is_normal_type() const {
    return m_field_type == FieldType::Normal;
  }

  bool is_primary_key() const {
    return m_field_type == FieldType::PrimaryKey;
  }

  bool is_foreign_key() const {
    return m_field_type == FieldType::ForeignKey;
  }

  const QString & name() const { return m_name; }
  void set_name(const QString & value) { m_name = value; }

  const QString & qt_type() const { return m_qt_type; }
  void set_qt_type(const QString & value) { m_qt_type = value; }

  const QString & json_name() const { return m_json_name; }
  void set_json_name(const QString & value) { m_json_name = value; }

  const QString & sql_name() const { return m_sql_name; }
  void set_sql_name(const QString & value) { m_sql_name = value; }

  const QString & sql_type() const { return m_sql_type; }
  void set_sql_type(const QString & value) { m_sql_type = value; }

  bool nullable() const { return m_nullable; }
  void set_nullable(bool value) { m_nullable = value; }

  const QString & title() const { return m_title; }
  void set_title(const QString & value) { m_title = value; }

  const QString & description() const { return m_description; }
  void set_description(const QString & value) { m_description = value; }

  bool has_sql_column_ctor() const { return not m_sql_column_ctor.isEmpty(); }
  const QString & sql_column_ctor() const { return m_sql_column_ctor; }
  void set_sql_column_ctor(const QString & sql_ctor) { m_sql_column_ctor = sql_ctor; }

  bool has_sql_value_ctor() const { return not m_sql_value_ctor.isNull(); }
  const QcSqlExpressionPtr & sql_value_ctor() const { return m_sql_value_ctor; }
  void set_sql_value_ctor(const QcSqlExpressionPtr & sql_ctor) { m_sql_value_ctor = sql_ctor; }

  bool has_sql_value_getter() const { return not m_sql_value_getter.isNull(); }
  const QcSqlExpressionPtr & sql_value_getter() const { return m_sql_value_getter; }
  void set_sql_value_getter(const QcSqlExpressionPtr & sql_getter) { m_sql_value_getter = sql_getter; }

  const QoSchema * schema() const { return m_schema; }
  int position() const { return m_position; }
  void set_position(QoSchema * schema, int value);

  QString to_sql_definition(const QStringList & parts) const;
  virtual QString to_sql_definition() const = 0;

  QoSqlField to_sql_field() const;

  // Fixme: https://www.qt.io/blog/whats-new-in-qmetatype-qvariant
  int qt_type_id() const { return QMetaType::fromName(m_qt_type.toLatin1()).id(); } // Fixme: cache ?
  QVariant * variant() const { return new QVariant(qt_type_id()); };
  // QMetaType qt_metatype() const { return QMetaType(qt_type_id()); } // private ctor ?
  // void * create() const { return QMetaType::create(qt_type_id()); }
  // T * create() const { ... }

protected:
  // Fixme: need by ForeignKey
  void set_field_type(FieldType field_type) { m_field_type = field_type; }

private:
  QoSchema * m_schema = nullptr;
  FieldType m_field_type = FieldType::Normal;
  int m_position = -1;
  QString m_name;
  QString m_sql_name;
  QString m_json_name;
  QString m_qt_type;
  QString m_sql_type;
  QString m_title;
  QString m_description;
  bool m_primary_key = false;
  bool m_autoincrement = false;
  bool m_nullable = true;
  bool m_unique = false;
  QVariant m_default = QVariant();
  QString m_sql_column_ctor = QString();
  QcSqlExpressionPtr m_sql_value_ctor = nullptr;
  QcSqlExpressionPtr m_sql_value_getter = nullptr;
};

typedef QSharedPointer<QoSchemaFieldTrait> QoSchemaFieldPtr;
typedef QList<QoSchemaFieldPtr> QoSchemaFieldList;

/**************************************************************************************************/

class QoSchemaField : public QoSchemaFieldTrait
{
public:
  QoSchemaField();
  QoSchemaField(const QString & name,
                const QString & qt_type, // ???
                const QString & sql_type,
                const QString & sql_name = QString(),
                const QString & json_name = QString(),
                const QString & title = QString(),
                const QString & description = QString()
                );
  QoSchemaField(const QoSchemaField & other);
  ~QoSchemaField();

  QoSchemaFieldTrait * clone() const { return new QoSchemaField(*this); };

  QoSchemaField & operator=(const QoSchemaField & other);

  QVariant default_value() const { return m_default; }
  void set_default_value(QVariant & value) { m_default = value; }

  QString to_sql_definition() const;

private:
  QVariant m_default = QVariant();
};

/**************************************************************************************************/

class QoSchemaPrimaryKey : public QoSchemaFieldTrait
{
public:
  QoSchemaPrimaryKey();
  QoSchemaPrimaryKey(const QString & name,
                     const QString & qt_type, // ???
                     const QString & sql_type,
                     const QString & sql_name = QString(),
                     const QString & json_name = QString(),
                     const QString & title = QString(),
                     const QString & description = QString()
                     );
  QoSchemaPrimaryKey(const QoSchemaPrimaryKey & other);
  ~QoSchemaPrimaryKey();

  QoSchemaFieldTrait * clone() const { return new QoSchemaPrimaryKey(*this); };

  QoSchemaPrimaryKey & operator=(const QoSchemaPrimaryKey & other);

  bool autoincrement() const { return m_autoincrement; }
  void set_autoincrement(bool value) { m_autoincrement = value; }

  bool unique() const { return m_unique; }
  void set_unique(bool value) { m_unique = value; }

  QString to_sql_definition() const;

private:
  bool m_autoincrement = false;
  bool m_unique = false;
};

/**************************************************************************************************/

class QoSchemaForeignKey : public QoSchemaField
{
public:
  QoSchemaForeignKey();
  QoSchemaForeignKey(const QString & name,
                     const QString & reference,
                     const QString & qt_type, // ???
                     const QString & sql_type,
                     const QString & sql_name = QString(),
                     const QString & json_name = QString(),
                     const QString & title = QString(),
                     const QString & description = QString()
                     );
  QoSchemaForeignKey(const QoSchemaForeignKey & other);
  ~QoSchemaForeignKey();

  QoSchemaFieldTrait * clone() const { return new QoSchemaForeignKey(*this); };

  QoSchemaForeignKey & operator=(const QoSchemaForeignKey & other);

  const QString & referenced_table() const { return m_referenced_table; }
  void set_referenced_table(const QString & value) { m_referenced_table = value; }

  const QString & referenced_field_name() const { return m_referenced_field_name; }
  void set_referenced_field_name(const QString & value) { m_referenced_field_name = value; }

  QoSchemaPtr referenced_schema() const { return m_referenced_schema; }
  void set_referenced_schema(QoSchemaPtr schema) { m_referenced_schema = schema; }

  QSharedPointer<const QoSchemaFieldTrait> referenced_field() const;

  // QString to_sql_definition() const;

private:
  QString m_referenced_table;
  QString m_referenced_field_name;
  QoSchemaPtr m_referenced_schema;
};

/**************************************************************************************************/

class QoSchema
{
  // Followings are defined in subclasses:
  //
  // enum Fields { // by order
  //   FIELD_NAME,
  //   ...
  // };
  // static const int NUMBER_OF_FIELDS = ...;

private:
  static std::atomic<int> m_last_schema_id;

  static int new_schema_id() { return m_last_schema_id++; }

public:
  QoSchema();
  QoSchema(const QString & name,
           const QString & table_name = QString(),
           bool without_rowid = false
           // const QString & sql_table_option = QString()
           );
  QoSchema(const QoSchema & other);
  ~QoSchema();

  QoSchema & operator=(const QoSchema & other);

  int schema_id() const { return m_schema_id; }
  void request_schema_id() { m_schema_id = new_schema_id(); } // to update a cloned schema

  // Fixme: pass & and copy ?
  void add_field(const QoSchemaFieldTrait & field); // field pth is managed by QSharedPointer
  QoSchema & operator<<(const QoSchemaFieldTrait & field);

  const QString & name() const { return m_name; }
  const QString & table_name() const { return m_table_name; }
  // const QString & sql_table_option() const { return m_sql_table_option; }

  bool without_rowid() const { return m_without_rowid; }
  bool has_rowid_primary_key() const { return m_has_rowid_primary_key; }
  bool has_foreign_keys() const {  return m_has_foreign_keys; }
  bool has_sql_value_ctor() const {  return m_has_sql_value_ctor; }

  int number_of_fields() { return m_fields.size(); } // Fixme: cf. NUMBER_OF_FIELDS
  const QoSchemaFieldList & fields() const { return m_fields; } // Fixme: const QoSchemaField
  const QStringList & field_names() const { return m_field_names; }
  const QStringList & field_names_witout_rowid() const { return m_field_names_without_rowid; }
  QStringList prefixed_field_names() const;

  QStringList to_sql_definition() const;

  const QoSchemaFieldPtr operator[](int position) const { return m_fields[position]; }
  const QoSchemaFieldPtr operator[](const QString & name) const { return m_field_map[name]; }

  // Note: Subclasses can define field shortcuts
  // Fixme: Merge QoSqlField with QoSchemaFieldTrait ???
  QoSqlField sql_field(int position) const { return m_fields[position]->to_sql_field(); }
  //!!!// QoSqlField sql_field(const QString & name) const { return QoSqlField(name, m_name); } // Fixme: check name ?

  QoSchemaFieldList::iterator begin() { return m_fields.begin(); }
  QoSchemaFieldList::iterator end() { return m_fields.end(); }
  QoSchemaFieldList::const_iterator cbegin() const { return m_fields.cbegin(); }
  QoSchemaFieldList::const_iterator cend() const { return m_fields.cend(); }

  const QoSchemaFieldList & fields_without_row_id() const { return m_fields_without_rowid; }

private:
  void copy_fields(const QoSchema & other);

private:
  int m_schema_id;
  QString m_name;
  QString m_table_name;
  bool m_without_rowid = false;
  bool m_has_rowid_primary_key = false;
  // QString m_sql_table_option;
  bool m_has_foreign_keys = false;
  bool m_has_sql_value_ctor = false;
  QoSchemaFieldList m_fields;
  QoSchemaFieldList m_fields_without_rowid;
  QHash<QString, QoSchemaFieldPtr> m_field_map;
  QStringList m_field_names;
  QStringList m_field_names_without_rowid; // Fixme: cf. m_fields_without_rowid
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __SCHEMA_H__ */
