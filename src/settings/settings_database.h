// -*- mode: c++ -*-

/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
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
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __SETTINGS_DATABASE_H__
#define __SETTINGS_DATABASE_H__

/**************************************************************************************************/

#include "database/database.h"

#include <QString>
#include <QVariant>
#include <QHash>

/**************************************************************************************************/

class SettingsDatabase : public QcSqliteDatabase
{
public:
  typedef QHash<QString, QVariant> KeyValueMap;

private:
  typedef QHash<int, QString> PathCache;

public:
  SettingsDatabase(const QString & sqlite_path);
  ~SettingsDatabase();

  bool contains(const QString & key);
  QVariant value(const QString & key);
  void set_value(const QString & key, const QVariant & value);
  void remove(const QString & key);

  QStringList keys(const QString & path);

  KeyValueMap to_map();

  // void vacuum(); // Fixme: implement vacuum directory table

private:
  void create_tables();
  int add_directory(const QString & directory, int parent);
  int get_directory_id(const QString & directory);
  QString directory_part(const QString & key) const;
  QString name_part(const QString & key) const;
  int parent_of(const QString & key);
  int rowid_of(const QString & key);
  QString parent_to_path(int parent, PathCache & paths);

private:
  QcDatabaseTable * m_directory_table;
  QcDatabaseTable * m_key_value_table;
};

/**************************************************************************************************/

#endif /* __SETTINGS_DATABASE_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
