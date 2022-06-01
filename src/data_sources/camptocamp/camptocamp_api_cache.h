// -*- mode: c++ -*-

/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
** $ALPINE_TOOLKIT_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __CAMPTOCAMP_API_CACHE_H__
#define __CAMPTOCAMP_API_CACHE_H__

/**************************************************************************************************/

#include "orm/sqlite_database.h"
#include "orm/database_schema.h"
#include "camptocamp/camptocamp_login.h"
#include "camptocamp/camptocamp_document.h"

#include <QString>

/**************************************************************************************************/

class C2cApiCache : public QoSqliteDatabase, public QoDatabaseSchema
{
public:
  C2cApiCache(const QString & sqlite_path);
  ~C2cApiCache();

  C2cLogin login(); // const
  void save_login(const C2cLogin & login);

  void save_document(const C2cDocumentPtr & document);
  bool has_document(unsigned int document_id) const;
  C2cDocumentPtr get_document(unsigned int document_id) const;

  C2cDocumentList get_documents() const;
  int number_of_documents() const;

private:
  void init();
  QString read_metadata(const QString & key);
  void init_metadata(const QString & key, const QString & value);
  void update_metadata(const QString & key, const QString & value);

private:
  QoDatabaseTable * m_metadata_table;
  QoDatabaseTable * m_document_table;
};

/**************************************************************************************************/

#endif /* __CAMPTOCAMP_API_CACHE_H__ */
