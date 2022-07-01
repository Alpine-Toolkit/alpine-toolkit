/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "settings_tree.h"
#include "alpine_toolkit.h"

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
operator==(const SettingsDatabaseKey & a, const SettingsDatabaseKey & b)
{
  return
    a.m_name == b.m_name and
    a.m_value == b.m_value and
    a.m_parent == b.m_parent;
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
operator==(const SettingsDatabaseDirectory & a, const SettingsDatabaseDirectory & b)
{
  return a.m_name == b.m_name and
    a.m_directories == b.m_directories and
    a.m_keys == b.m_keys and
    a.m_parent == b.m_parent;
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
