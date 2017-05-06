// -*- mode: c++ -*-

/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the QtCarto library.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __SCHEMA_H__
#define __SCHEMA_H__

/**************************************************************************************************/

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

// Fixme: template ?
class QcSchemaFieldTrait
{
protected:
  enum FieldType {
    Normal,
    PrimaryKey,
    ForeignKey
  };

public:
  QcSchemaFieldTrait(FieldType field_type = FieldType::Normal);
  QcSchemaFieldTrait(FieldType field_type,
                     const QString & name,
                     const QString & qt_type, // ???
                     const QString & sql_type,
                     const QString & sql_name,
                     const QString & json_name,
                     const QString & title,
                     const QString & description
                     );
  QcSchemaFieldTrait(const QcSchemaFieldTrait & other);
  virtual ~QcSchemaFieldTrait();

  virtual QcSchemaFieldTrait * clone() const = 0;

  QcSchemaFieldTrait & operator=(const QcSchemaFieldTrait & other);

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

  int position() const { return m_position; }
  void set_position(int value) { m_position = value; }

  QString to_sql_definition(const QStringList & parts) const;
  virtual QString to_sql_definition() const = 0;

  int qt_type_id() const { return QMetaType::type(m_qt_type.toLatin1()); } // Fixme: cache ?
  QVariant * variant() const { return new QVariant(qt_type_id()); };
  // QMetaType qt_metatype() const { return QMetaType(qt_type_id()); } // private ctor ?
  // void * create() const { return QMetaType::create(qt_type_id()); }
  // T * create() const { ... }

protected:
  // Fixme: need by ForeignKey
  void set_field_type(FieldType field_type) { m_field_type = field_type; }

private:
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
};

/**************************************************************************************************/

class QcSchemaField : public QcSchemaFieldTrait
{
public:
  QcSchemaField();
  QcSchemaField(const QString & name,
                const QString & qt_type, // ???
                const QString & sql_type,
                const QString & sql_name = QString(),
                const QString & json_name = QString(),
                const QString & title = QString(),
                const QString & description = QString()
                );
  QcSchemaField(const QcSchemaField & other);
  ~QcSchemaField();

  QcSchemaFieldTrait * clone() const { return new QcSchemaField(*this); };

  QcSchemaField & operator=(const QcSchemaField & other);

  QVariant default_value() const { return m_default; }
  void set_default_value(QVariant & value) { m_default = value; }

  QString to_sql_definition() const;

private:
  QVariant m_default = QVariant();
};

/**************************************************************************************************/

class QcSchemaPrimaryKey : public QcSchemaFieldTrait
{
public:
  QcSchemaPrimaryKey();
  QcSchemaPrimaryKey(const QString & name,
                     const QString & qt_type, // ???
                     const QString & sql_type,
                     const QString & sql_name = QString(),
                     const QString & json_name = QString(),
                     const QString & title = QString(),
                     const QString & description = QString()
                     );
  QcSchemaPrimaryKey(const QcSchemaPrimaryKey & other);
  ~QcSchemaPrimaryKey();

  QcSchemaFieldTrait * clone() const { return new QcSchemaPrimaryKey(*this); };

  QcSchemaPrimaryKey & operator=(const QcSchemaPrimaryKey & other);

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

class QcSchemaForeignKey : public QcSchemaField
{
public:
  QcSchemaForeignKey();
  QcSchemaForeignKey(const QString & name,
                     const QString & qt_type, // ???
                     const QString & sql_type,
                     const QString & sql_name = QString(),
                     const QString & json_name = QString(),
                     const QString & title = QString(),
                     const QString & description = QString()
                     );
  QcSchemaForeignKey(const QcSchemaForeignKey & other);
  ~QcSchemaForeignKey();

  QcSchemaFieldTrait * clone() const { return new QcSchemaForeignKey(*this); };

  QcSchemaForeignKey & operator=(const QcSchemaForeignKey & other);

  //  QString to_sql_definition() const;
};

/**************************************************************************************************/

class QcSchema
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
  QcSchema();
  QcSchema(const QString & name,
           const QString & table_name = QString(),
           bool without_rowid = false
           // const QString & sql_table_option = QString()
           );
  QcSchema(const QcSchema & other);
  ~QcSchema();

  QcSchema & operator=(const QcSchema & other);

  int schema_id() const { return m_schema_id; }
  void request_schema_id() { m_schema_id = new_schema_id(); } // to update a cloned schema

  // Fixme: pass & and copy ?
  void add_field(const QcSchemaFieldTrait & field); // field pth is managed by QSharedPointer
  QcSchema & operator<<(const QcSchemaFieldTrait & field);

  const QString & name() const { return m_name; }
  const QString & table_name() const { return m_table_name; }
  // const QString & sql_table_option() const { return m_sql_table_option; }

  bool without_rowid() const { return m_without_rowid; }
  bool has_rowid_primary_key() const { return m_has_rowid_primary_key; }
  bool has_foreign_keys() const {  return m_has_foreign_keys; }

  int number_of_fields() { return m_fields.size(); } // Fixme: cf. NUMBER_OF_FIELDS
  const QList<QSharedPointer<QcSchemaFieldTrait>> & fields() const { return m_fields; } // Fixme: const QcSchemaField
  QStringList field_names() { return m_field_map.keys(); }
  QStringList & field_names_witout_rowid() { return m_field_names_without_rowid; }

  QString to_sql_definition() const;

  const QcSchemaFieldTrait & operator[](int position) const { return *m_fields[position]; }
  const QcSchemaFieldTrait & operator[](const QString & name) const { return *m_field_map[name]; }

  QList<QSharedPointer<QcSchemaFieldTrait>>::iterator begin() { return m_fields.begin(); }
  QList<QSharedPointer<QcSchemaFieldTrait>>::iterator end() { return m_fields.end(); }
  QList<QSharedPointer<QcSchemaFieldTrait>>::const_iterator cbegin() const { return m_fields.cbegin(); }
  QList<QSharedPointer<QcSchemaFieldTrait>>::const_iterator cend() const { return m_fields.cend(); }

private:
  int m_schema_id;
  QString m_name;
  QString m_table_name;
  bool m_without_rowid = false;
  bool m_has_rowid_primary_key = false;
  // QString m_sql_table_option;
  bool m_has_foreign_keys = false;
  QList<QSharedPointer<QcSchemaFieldTrait>> m_fields;
  QHash<QString, QcSchemaFieldTrait *> m_field_map;
  QStringList m_field_names_without_rowid;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __SCHEMA_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
