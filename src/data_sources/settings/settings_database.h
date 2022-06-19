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
