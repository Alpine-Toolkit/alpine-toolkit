/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
