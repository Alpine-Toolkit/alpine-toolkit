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

#include <QList>
#include <QMetaType>
#include <QString>
#include <QVariant>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

/*
 * To complete:
 *  field enum to get position efficiently
 *  number of fields
 *  field iterator -> position, name, variant
 *
 */

// Fixme: template ?
class QcSchemaField
{
public:
  QcSchemaField();
  QcSchemaField(const QString & name,
                const QString & qt_type, // ???
                const QString & sql_type,
                const QString & sql_qualifier = QString(),
                const QString & sql_name = QString(),
                const QString & json_name = QString(),
                const QString & title = QString(),
                const QString & description = QString()
                );
  QcSchemaField(const QcSchemaField & other);
  ~QcSchemaField();

  QcSchemaField & operator=(const QcSchemaField & other);

  const QString & name() const { return m_name; }
  void set_name(const QString & value) { m_name = value; }

  const QString & sql_name() const { return m_sql_name; }
  void set_sql_name(const QString & value) { m_sql_name = value; }

  const QString & json_name() const { return m_json_name; }
  void set_json_name(const QString & value) { m_json_name = value; }

  const QString & sql_type() const { return m_sql_type; }
  void set_sql_type(const QString & value) { m_sql_type = value; }

  const QString & sql_qualifier() const { return m_sql_qualifier; }
  void set_sql_qualifier(const QString & value) { m_sql_qualifier = value; }

  const QString & qt_type() const { return m_qt_type; }
  void set_qt_type(const QString & value) { m_qt_type = value; }

  const QString & title() const { return m_title; }
  void set_title(const QString & value) { m_title = value; }

  const QString & description() const { return m_description; }
  void set_description(const QString & value) { m_description = value; }

  int position() const { return m_position; }
  void set_position(int value) { m_position = value; }

  QString to_sql_definition() const;

  int qt_type_id() const { return QMetaType::type(m_qt_type.toLatin1()); } // Fixme: cache ?
  QVariant * variant() const { return new QVariant(qt_type_id()); };
  // QMetaType qt_metatype() const { return QMetaType(qt_type_id()); } // private ctor ?
  // void * create() const { return QMetaType::create(qt_type_id()); }
  // T * create() const { ... }

private:
  QString m_name;
  QString m_sql_name;
  QString m_json_name;
  QString m_qt_type;
  QString m_sql_type;
  QString m_sql_qualifier;
  QString m_title;
  QString m_description;
  int m_position;
};

/**************************************************************************************************/

class QcSchema
{
public:
  QcSchema();
  QcSchema(const QString & name);
  QcSchema(const QcSchema & other);
  ~QcSchema();

  QcSchema & operator=(const QcSchema & other);

  const QString & name() const { return m_name; }
  const QList<QcSchemaField> & fields() const { return m_fields; } // Fixme: const QcSchemaField

  void add_field(const QcSchemaField & field);
  QcSchema & operator<<(const QcSchemaField & field);

  const QcSchemaField & operator[](int position) const { return m_fields[position]; }

private:
  QString m_name;
  QList<QcSchemaField> m_fields;
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
