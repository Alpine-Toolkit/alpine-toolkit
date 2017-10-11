// -*- mode: c++ -*-
/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
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
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef __THIRD_PARTY_LICENSE_SQLITE_DATABASE_H__
#define __THIRD_PARTY_LICENSE_SQLITE_DATABASE_H__

/**************************************************************************************************/

#include "orm/sqlite_database.h"
#include "third_party_license/third_party_license_schema.h"

/**************************************************************************************************/

class ThirdPartyLicenseSqliteDatabase : public QoSqliteDatabase
{
public:
  ThirdPartyLicenseSqliteDatabase(const QString & sqlite_path);
  ~ThirdPartyLicenseSqliteDatabase();

  ThirdPartyLicenseDatabaseSchema & schema() { return *m_schema; }

private:
  ThirdPartyLicenseDatabaseSchema * m_schema = nullptr; // database must be opened before to instanciate DatabaseSchema
};

/**************************************************************************************************/

#endif /* __THIRD_PARTY_LICENSE_SQLITE_DATABASE_H__ */
