/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine Toolkit software.
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

#include "third_party_license_sqlite_database.h"
#include "alpine_toolkit.h"

#include <QtDebug>

/**************************************************************************************************/

ThirdPartyLicenseSqliteDatabase::ThirdPartyLicenseSqliteDatabase(const QString & sqlite_path)
  : QoSqliteDatabase(sqlite_path, true), // use Spatialite
    m_schema(nullptr)
{
  m_schema = new ThirdPartyLicenseDatabaseSchema(*this);
}

ThirdPartyLicenseSqliteDatabase::~ThirdPartyLicenseSqliteDatabase()
{
  if (m_schema)
    delete m_schema;
}
