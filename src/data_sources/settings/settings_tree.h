// -*- mode: c++ -*-
/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#ifndef __SETTINGS_TREE_H__
#define __SETTINGS_TREE_H__

/**************************************************************************************************/

#include <QJsonObject>
#include <QString>
#include <QVariant>

/**************************************************************************************************/

class SettingsDatabaseDirectory;

/**************************************************************************************************/

class SettingsDatabaseKey
{
public:
  SettingsDatabaseKey();
  SettingsDatabaseKey(const QString & name, const QVariant & value,
                      const SettingsDatabaseDirectory * parent = nullptr);
  SettingsDatabaseKey(const SettingsDatabaseKey & other);
  ~SettingsDatabaseKey();

  SettingsDatabaseKey & operator=(const SettingsDatabaseKey & other);

  const QString & name() const { return m_name; }
  void set_name(const QString & name) { m_name = name; }

  const QVariant & value() const { return m_value; }
  void set_value(const QVariant & value) { m_value = value; }

  const SettingsDatabaseDirectory * parent() const { return m_parent; }
  void set_parent(const SettingsDatabaseDirectory * parent) { m_parent = parent; }

  QString path() const;

public:
  friend bool operator==(const SettingsDatabaseKey &, const SettingsDatabaseKey &);

private:
  QString m_name;
  QVariant m_value;
  const SettingsDatabaseDirectory * m_parent = nullptr;
};

/**************************************************************************************************/

class SettingsDatabaseDirectory
{
  typedef QList<SettingsDatabaseDirectory> DirectoryList;
  typedef QList<SettingsDatabaseKey> KeyList;

public:
  SettingsDatabaseDirectory();
  SettingsDatabaseDirectory(const QString & name, const SettingsDatabaseDirectory * parent = nullptr);
  SettingsDatabaseDirectory(const SettingsDatabaseDirectory & other);

  SettingsDatabaseDirectory & operator=(const SettingsDatabaseDirectory & other);

  const QString & name() const { return m_name; }
  void set_name(const QString & name) { m_name = name; }

  const SettingsDatabaseDirectory * parent() const { return m_parent; }
  void set_parent(const SettingsDatabaseDirectory * parent) { m_parent = parent; }

  QString path() const;

  SettingsDatabaseDirectory & add_directory(const QString & name);
  SettingsDatabaseKey & add_key(const QString & name, const QVariant value);

  const DirectoryList & directories() const { return m_directories; }
  const KeyList & keys() const { return m_keys; }

  QJsonObject to_json() const;
  void from_json(const QJsonObject & json_dictionary);

public:
  friend bool operator==(const SettingsDatabaseDirectory &, const SettingsDatabaseDirectory &);

private:
  QString m_name;
  DirectoryList m_directories;
  KeyList m_keys;
  const SettingsDatabaseDirectory * m_parent = nullptr;
  // int m_rowid;
};

/**************************************************************************************************/

#endif /* __SETTINGS_TREE_H__ */
