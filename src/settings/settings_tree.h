// -*- mode: c++ -*-
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

  bool operator==(const SettingsDatabaseKey & other);

  const QString & name() const { return m_name; }
  void set_name(const QString & name) { m_name = name; }

  const QVariant & value() const { return m_value; }
  void set_value(const QVariant & value) { m_value = value; }

  const SettingsDatabaseDirectory * parent() const { return m_parent; }
  void set_parent(const SettingsDatabaseDirectory * parent) { m_parent = parent; }

  QString path() const;

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

  bool operator==(const SettingsDatabaseDirectory & other);

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

private:
  QString m_name;
  DirectoryList m_directories;
  KeyList m_keys;
  const SettingsDatabaseDirectory * m_parent = nullptr;
  // int m_rowid;
};

/**************************************************************************************************/

#endif /* __SETTINGS_TREE_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
