// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
