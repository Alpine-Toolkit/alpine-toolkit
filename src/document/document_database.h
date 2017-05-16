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

#ifndef __DOCUMENT_DATABASE_H__
#define __DOCUMENT_DATABASE_H__

/**************************************************************************************************/

#include "orm/sqlite_database.h"
#include "document/document.h"

/**************************************************************************************************/

class DocumentDatabase : public QcSqliteDatabase
{
public:
  DocumentDatabase(const QString & sqlite_path);
  ~DocumentDatabase();

  DocumentDatabaseSchema & schema() { return *m_schema; } // Fixme: nullptr?

private:
  DocumentDatabaseSchema * m_schema = nullptr; // database must be opened before to instanciate DatabaseSchema
};

/**************************************************************************************************/

#endif /* __DOCUMENT_DATABASE_H__ */

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
