// -*- mode: c++ -*-
/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef __BLOG_DATABASE_H__
#define __BLOG_DATABASE_H__

/**************************************************************************************************/

#include "orm/sqlite_database.h"
#include "blog.h"

/**************************************************************************************************/

class BlogDatabase : public QoSqliteDatabase
{
public:
  typedef BlogApplicationSchema DatabaseSchema;

public:
  BlogDatabase(const QString & sqlite_path);
  ~BlogDatabase();

  DatabaseSchema & schema() { return *m_schema; }

private:
  DatabaseSchema * m_schema = nullptr; // database must be opened before to instanciate DatabaseSchema
};

/**************************************************************************************************/

#endif /* __BLOG_DATABASE_H__ */
