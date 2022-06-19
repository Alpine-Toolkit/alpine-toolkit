/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "blog_database.h"

#include <QtDebug>

/**************************************************************************************************/

BlogDatabase::BlogDatabase(const QString & sqlite_path)
  : QoSqliteDatabase(sqlite_path),
    m_schema(nullptr)
{
  m_schema = new DatabaseSchema(*this);
}

BlogDatabase::~BlogDatabase()
{
  if (m_schema)
    delete m_schema;
}
