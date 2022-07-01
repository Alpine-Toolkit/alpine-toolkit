/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

/**************************************************************************************************/

#include "bleau_sqlite_database.h"
#include "alpine_toolkit.h"

#include <QtDebug>

/**************************************************************************************************/

BleauSqliteDatabase::BleauSqliteDatabase(const QString & sqlite_path)
  : QoSqliteDatabase(sqlite_path),
    m_schema(nullptr)
{
  m_schema = new BleauSchema(*this);
}

BleauSqliteDatabase::~BleauSqliteDatabase()
{
  if (m_schema)
    delete m_schema;
}
