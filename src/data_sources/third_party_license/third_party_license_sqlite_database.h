// -*- mode: c++ -*-
/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
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
