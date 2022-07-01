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

#ifndef __BLEAU_SQLITE_DATABASE_H__
#define __BLEAU_SQLITE_DATABASE_H__

/**************************************************************************************************/

#include "orm/sqlite_database.h"
#include "bleaudb/bleau_schema.h"

/**************************************************************************************************/

class BleauSqliteDatabase : public QoSqliteDatabase
{
public:
  BleauSqliteDatabase(const QString & sqlite_path);
  ~BleauSqliteDatabase();

  BleauSchema & schema() { return *m_schema; }

private:
  BleauSchema * m_schema = nullptr; // database must be opened before to instanciate DatabaseSchema
};

/**************************************************************************************************/

#endif /* __BLEAU_SQLITE_DATABASE_H__ */
