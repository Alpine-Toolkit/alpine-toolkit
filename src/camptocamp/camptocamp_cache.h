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

#ifndef __CAMPTOCAMP_CACHE_H__
#define __CAMPTOCAMP_CACHE_H__

/**************************************************************************************************/

#include "database/database.h"
#include "camptocamp/camptocamp_login.h"

#include <QString>

/**************************************************************************************************/

class C2cCache :  public QcSqliteDatabase
{
public:
  C2cCache(const QString & sqlite_path);
  ~C2cCache();

  C2cLogin login(); // const
  void save_login(const C2cLogin & login);

private:
  void create_tables();
  void init();
  QString read_metadata(const QString & key);
  void init_metadata(const QString & key, const QString & value);
  void update_metadata(const QString & key, const QString & value);

};

/**************************************************************************************************/

#endif /* __CAMPTOCAMP_CACHE_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
