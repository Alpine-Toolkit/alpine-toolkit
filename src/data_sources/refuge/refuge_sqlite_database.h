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

#ifndef __REFUGE_SQLITE_DATABASE_H__
#define __REFUGE_SQLITE_DATABASE_H__

/**************************************************************************************************/

#include "orm/sqlite_database.h"
#include "refuge/refuge_schema.h"

/**************************************************************************************************/

class RefugeSqliteDatabase : public QoSqliteDatabase
{
public:
  RefugeSqliteDatabase(const QString & sqlite_path);
  ~RefugeSqliteDatabase();

  RefugeDatabaseSchema & schema() { return *m_schema; }

private:
  RefugeDatabaseSchema * m_schema = nullptr; // database must be opened before to instanciate DatabaseSchema
};

/**************************************************************************************************/

#endif /* __REFUGE_SQLITE_DATABASE_H__ */
