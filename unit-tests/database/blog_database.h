// -*- mode: c++ -*-
/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire
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
 * $QTCARTO_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#ifndef __BLOG_DATABASE_H__
#define __BLOG_DATABASE_H__

/**************************************************************************************************/

#include "orm/sqlite_database.h"
#include "blog.h"

/**************************************************************************************************/

class BlogDatabase : public QcSqliteDatabase
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

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
