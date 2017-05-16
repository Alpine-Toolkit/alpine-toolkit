/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
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
** $ALPINE_TOOLKIT_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#include "settings_database.h"

#include "orm/sql_record_wrapper.h"

#include <QSqlError>
#include <QtDebug>

/**************************************************************************************************/

static const QString DIRECTORY = "directory";
static const QString KEY_VALUE = "key_value";
static const QString NAME = "name";
static const QString PARENT = "parent";
static const QString VALUE = "value";
static const QString ROWID = "rowid";

SettingsDatabase::SettingsDatabase(QcDatabase & database)
  : QcDatabaseSchema(database),
    m_directory_table(nullptr),
    m_key_value_table(nullptr)
{}

SettingsDatabase::~SettingsDatabase()
{}

void
SettingsDatabase::register_tables()
{
  // rowid https://sqlite.org/autoinc.html

  QcSchemaField name_field(NAME, QLatin1String("QString"), QLatin1String("TEXT"));
  name_field.set_nullable(false);

  QcSchema directory_schema(DIRECTORY);
  directory_schema << name_field;
  directory_schema << QcSchemaField(PARENT, QLatin1String("int"), QLatin1String("INTEGER"));
  m_directory_table = &register_table(directory_schema);

  QcSchema key_value_schema(KEY_VALUE);
  key_value_schema << name_field;
  key_value_schema << QcSchemaField(PARENT, QLatin1String("int"), QLatin1String("INTEGER"));
  key_value_schema << QcSchemaField(VALUE, QLatin1String("QByteArray"), QLatin1String("BLOB"));
  m_key_value_table = &register_table(key_value_schema);
}

int
SettingsDatabase::add_directory(const QString & directory, int parent)
{
  QVariantHash kwargs;
  kwargs[NAME] = directory;
  kwargs[PARENT] = parent;
  QSqlQuery query = m_directory_table->insert(kwargs);
  int row_id = query.lastInsertId().toInt();
  qInfo() << "added directory" << directory << parent << row_id;
  return row_id;
}

int
SettingsDatabase::get_directory_id(const QString & directory)
{
  QStringList directories = directory.split('/');

  int parent = 0; // start at root
  for (const auto & directory : directories) {
    QVariantHash kwargs;
    kwargs[NAME] = directory;
    kwargs[PARENT] = parent;
    QSqlRecord record_ = m_directory_table->select_one(QStringList(ROWID), kwargs);
    QcSqlRecordWrapper record(record_); // Fixme: must keep object alive!
    if (record.is_empty())
      parent = add_directory(directory, parent); // not const
    else
      parent = record.to_int(); // Fixme: how to simplify ?
  }

  return parent;
}

QString
SettingsDatabase::directory_part(const QString & key) const
{
  int index = key.lastIndexOf('/');
  if (index != -1)
    return key.left(index);
  else
    return QString();
}

QString
SettingsDatabase::name_part(const QString & key) const
{
  int index = key.lastIndexOf('/');
  if (index != -1)
    return key.mid(index + 1);
  else
    return key;
}

int
SettingsDatabase::parent_of(const QString & key)
{
  QString directory = directory_part(key);
  qInfo() << "parent_of" << key << directory;
  return directory.isEmpty() ? 0 : get_directory_id(directory);
}

bool
SettingsDatabase::contains(const QString & key)
{
  QVariantHash kwargs;
  kwargs[NAME] = name_part(key);
  kwargs[PARENT] = parent_of(key);
  QSqlRecord record_ = m_key_value_table->select_one(QStringList(ROWID), kwargs);
  QcSqlRecordWrapper record(record_);
  return record.is_not_empty();
}

int
SettingsDatabase::rowid_of(const QString & key)
{
  QVariantHash kwargs;
  kwargs[NAME] = name_part(key);
  kwargs[PARENT] = parent_of(key);
  QSqlRecord record_ = m_key_value_table->select_one(QStringList(ROWID), kwargs);
  QcSqlRecordWrapper record(record_);
  if (record.is_empty())
    return -1;
  else
    return record.to_int(0);
}

QVariant
SettingsDatabase::value(const QString & key)
{
  QVariantHash kwargs;
  kwargs[NAME] = name_part(key);
  kwargs[PARENT] = parent_of(key);
  QSqlRecord record = m_key_value_table->select_one(QStringList(VALUE), kwargs);
  return record.value(0);
}

void
SettingsDatabase::set_value(const QString & key, const QVariant & value)
{
  int rowid = rowid_of(key);
  if (rowid == -1) {
    QVariantHash kwargs;
    kwargs[NAME] = name_part(key);
    kwargs[PARENT] = parent_of(key);
    kwargs[VALUE] = value;
    QSqlQuery query = m_key_value_table->insert(kwargs);
    qInfo() << "added key" << key << value;
  } else {
    QVariantHash kwargs_where;
    kwargs_where[ROWID] = rowid;
    QVariantHash kwargs_update;
    qInfo() << "value is of type" << value.typeName();
    kwargs_update[VALUE] = value;
    m_key_value_table->update(kwargs_update, kwargs_where);
    qInfo() << "updated key" << rowid << key << value;
  }
}

void
SettingsDatabase::remove(const QString & key)
{
  QVariantHash kwargs;
  kwargs[NAME] = name_part(key);
  kwargs[PARENT] = parent_of(key);
  m_key_value_table->delete_row(kwargs);
}

QStringList
SettingsDatabase::keys(const QString & path)
{
  QVariantHash kwargs;
  kwargs[PARENT] = parent_of(path + '/'); // Fixme:
  QSqlQuery query = m_key_value_table->select(QStringList(NAME), kwargs);
  QStringList keys;
  while (query.next())
    keys << query.value(0).toString();
  return keys;
}

QString
SettingsDatabase::parent_to_path(int parent, PathCache & paths)
{
  if (parent) {
    QStringList directories;

    QStringList fields;
    fields << NAME << PARENT;
    while (parent) {
      QVariantHash kwargs;
      kwargs[ROWID] = parent;
      QSqlRecord record_ = m_directory_table->select_one(fields, kwargs);
      QcSqlRecordWrapper record(record_);
      // if (record.isEmpty() == false)
      directories.prepend(record.to_string(0));
      parent = record.to_int(1);
      if (paths.contains(parent)) {
        directories.prepend(paths[parent]);
        break;
      }
    }
    QString path = directories.join('/');
    paths.insert(parent, path);
    return path;
  } else
    return QString();
}

SettingsDatabase::KeyValueMap
SettingsDatabase::to_map()
{
  QHash<QString, QVariant> key_values;
  QHash<int, QString> paths;

  QStringList fields;
  fields << NAME << PARENT << VALUE;
  QSqlQuery query = m_key_value_table->select(fields);
  while (query.next()) {
    QString name = query.value(0).toString();
    int parent = query.value(1).toInt();
    QVariant value = query.value(2);
    QString path;
    if (paths.contains(parent))
      path = paths[parent];
    else {
      path = parent_to_path(parent, paths);
      // paths.insert(parent, path);
    }
    QString key = path.isEmpty() ? name : path + '/' + name;
    key_values.insert(key, value);
  }

  return key_values;
}

/**************************************************************************************************/

SqliteSettingsDatabase::SqliteSettingsDatabase(const QString & sqlite_path)
  : QcSqliteDatabase(sqlite_path),
    m_settings_database(*this)
    // SettingsDatabase(*this)
{
  m_settings_database.register_tables();
}

SqliteSettingsDatabase::~SqliteSettingsDatabase()
{}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
