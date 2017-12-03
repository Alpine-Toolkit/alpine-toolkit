// -*- mode: c++ -*-

/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
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

#ifndef __SETTINGS_DATABASE_H__
#define __SETTINGS_DATABASE_H__

/**************************************************************************************************/

#include "orm/database_schema.h"
#include "orm/database_table.h"
#include "orm/json_adaptator.h"
#include "orm/sqlite_database.h"
#include "settings/settings_tree.h"

#include <QString>
#include <QVariant>
#include <QHash>

/**************************************************************************************************/

class SettingsDatabase : public QoDatabaseSchema, public QoJsonSchemaTraits
{
public:
  typedef QHash<QString, QVariant> KeyValueMap;

private:
  typedef QHash<int, QString> PathCache;

public:
  SettingsDatabase(QoDatabase & database);
  ~SettingsDatabase();

  void register_tables();

  bool contains(const QString & key);
  QVariant value(const QString & key);
  void set_value(const QString & key, const QVariant & value);
  void remove(const QString & key);

  void delete_all();

  int number_of_directories() const;
  int number_of_keys() const;

  QStringList keys(const QString & path);

  void load();
  void clear_cache();
  const KeyValueMap & cache() const { return m_key_cache; }

  void load_json_document(const QJsonDocument & json_document);
  QJsonDocument to_json_document(); // const

  // void vacuum(); // Fixme: implement vacuum directory table

private:
  QString directory_part(const QString & key) const;
  QString name_part(const QString & key) const;

  QVariantHash directory_kwargs(const QString & directory, int parent);
  int add_directory(const QString & directory, int parent);
  int lookup_path(const QString & directory, bool create = true);
  int directory_rowid(const QString & directory, int parent);

  int parent_of(const QString & key, bool create = true);
  QVariantHash key_kwargs(const QString & key);
  QString parent_to_path(int parent);

  void load_directory();
  void save_directory(const SettingsDatabaseDirectory & directory);

private:
  QoDatabaseTable * m_directory_table;
  QoDatabaseTable * m_key_value_table;

  // Fixme: implement as a tree ?
  QHash<int, QString> m_rowid_path_cache;
  QHash<QString, int> m_path_cache;
  KeyValueMap m_key_cache;

  SettingsDatabaseDirectory m_root;
};

/**************************************************************************************************/

class SqliteSettingsDatabase : public QoSqliteDatabase // , public SettingsDatabase
{
public:
  SqliteSettingsDatabase(const QString & sqlite_path);
  ~SqliteSettingsDatabase();

  // SettingsDatabase API
  // Fixme: better ?

  bool contains(const QString & key) { return m_settings_database.contains(key); }
  QVariant value(const QString & key)  { return m_settings_database.value(key); }
  void set_value(const QString & key, const QVariant & value)  { return m_settings_database.set_value(key, value); }
  void remove(const QString & key)  { return m_settings_database.remove(key); }

  void delete_all() { m_settings_database.delete_all(); }

  QStringList keys(const QString & path)  { return m_settings_database.keys(path); }

  void load() { return m_settings_database.load(); }
  void clear_cache() { return m_settings_database.clear_cache(); }
  SettingsDatabase::KeyValueMap cache() const { return m_settings_database.cache(); }

  int number_of_directories() const { return m_settings_database.number_of_directories(); }
  int number_of_keys() const { return m_settings_database.number_of_keys(); }

  void load_json_document(const QJsonDocument & json_document) { m_settings_database.load_json_document(json_document); }
  QJsonDocument to_json_document() { return m_settings_database.to_json_document(); } // const

  void from_json(const QString & json_path) { m_settings_database.load_json(json_path); }
  void to_json(const QString & json_path) { m_settings_database.to_json(json_path); }

private:
  SettingsDatabase m_settings_database;
};

/**************************************************************************************************/

#endif /* __SETTINGS_DATABASE_H__ */
