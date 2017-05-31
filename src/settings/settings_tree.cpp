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

#include "settings_tree.h"

/**************************************************************************************************/

SettingsDatabaseKey::SettingsDatabaseKey()
{}

SettingsDatabaseKey::SettingsDatabaseKey(const QString & name,
                                         const QVariant & value,
                                         const SettingsDatabaseDirectory * parent)
  : m_name(name),
    m_value(value),
    m_parent(parent)
{}

SettingsDatabaseKey::SettingsDatabaseKey(const SettingsDatabaseKey & other)
  : m_name(other.m_name),
    m_value(other.m_value),
    m_parent(other.m_parent)
{}

SettingsDatabaseKey::~SettingsDatabaseKey()
{}

SettingsDatabaseKey &
SettingsDatabaseKey::operator=(const SettingsDatabaseKey & other)
{
  if (this != &other) {
    m_name = other.m_name;
    m_value = other.m_value;
    m_parent = other.m_parent;
  }

  return *this;
}

bool
SettingsDatabaseKey::operator==(const SettingsDatabaseKey & other)
{
  return
    m_name == other.m_name and
    m_value == other.m_value and
    m_parent == other.m_parent;
}

QString
SettingsDatabaseKey::path() const
{
  // Fixme: cache
  if (m_parent)
    return m_parent->path() + '/' + m_name;
  else
    return m_name;
}

/**************************************************************************************************/

SettingsDatabaseDirectory::SettingsDatabaseDirectory()
  : m_name(),
    m_directories(),
    m_keys()
{}

SettingsDatabaseDirectory::SettingsDatabaseDirectory(const QString & name,
                                                     const SettingsDatabaseDirectory * parent)
  : m_name(name),
    m_directories(),
    m_keys(),
    m_parent(parent)
{}

SettingsDatabaseDirectory::SettingsDatabaseDirectory(const SettingsDatabaseDirectory & other)
  : m_name(other.m_name),
    m_directories(other.m_directories),
    m_keys(other.m_keys),
    m_parent(other.m_parent)
{}

SettingsDatabaseDirectory &
SettingsDatabaseDirectory::operator=(const SettingsDatabaseDirectory & other)
{
  if (this != &other) {
    m_name = other.m_name;
    m_directories = other.m_directories;
    m_keys = other.m_keys;
    m_parent = other.m_parent;
  }

  return *this;
}

bool
SettingsDatabaseDirectory::operator==(const SettingsDatabaseDirectory & other)
{
  return
    m_name == other.m_name and
    m_directories == other.m_directories and
    m_keys == other.m_keys and
    m_parent == other.m_parent;
}

QString
SettingsDatabaseDirectory::path() const
{
  if (m_parent)
    return m_parent->path() + '/' + m_name;
  else
    return m_name;
}

SettingsDatabaseDirectory &
SettingsDatabaseDirectory::add_directory(const QString & name)
{
  m_directories << SettingsDatabaseDirectory(name, this);
  return m_directories.last();
}


SettingsDatabaseKey &
SettingsDatabaseDirectory::add_key(const QString & name, const QVariant value)
{
  m_keys << SettingsDatabaseKey(name, value, this);
  return m_keys.last();
}

QJsonObject
SettingsDatabaseDirectory::to_json() const
{
  QJsonObject json_dictionary;

  QJsonObject keys;
  for (const auto & key : m_keys) {
    const QVariant & value = key.value();
    // Qt issue: key.value().toJsonValue() don't work with numerical types
    keys[key.name()] = QJsonValue::fromVariant(value);
  }
  // place keys a dedicated dict so as to permit dict values
  json_dictionary[QLatin1String("keys")] = keys;

  for (const auto & directory : m_directories)
    json_dictionary[directory.name()] = directory.to_json();

  return json_dictionary;
}

void
SettingsDatabaseDirectory::from_json(const QJsonObject & json_dictionary)
{
  // for (const auto & obj : keys) -> QJsonValueRef
  for (QJsonObject::ConstIterator it = json_dictionary.begin(); it != json_dictionary.end(); ++it) {
    const QString & name = it.key();
    const QJsonObject & json_object = it->toObject();
    if (name == QLatin1String("keys")) {
      for (QJsonObject::ConstIterator it = json_object.begin(); it != json_object.end(); ++it)
        add_key(it.key(), it->toVariant());
    } else {
      SettingsDatabaseDirectory & directory = add_directory(name);
      directory.from_json(json_object);
    }
  }
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
