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

#ifndef __DOCUMENT_DATABASE_H__
#define __DOCUMENT_DATABASE_H__

/**************************************************************************************************/

#include "orm/sqlite_database.h"
#include "document/document.h"

/**************************************************************************************************/

class DocumentDatabase : public QoSqliteDatabase
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
