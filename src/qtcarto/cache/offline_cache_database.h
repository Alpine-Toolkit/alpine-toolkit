// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __QC_OFFLINE_CACHE_DATABASE_H__
#define __QC_OFFLINE_CACHE_DATABASE_H__

/**************************************************************************************************/

#include "wmts/tile_spec.h"
#include "database/database.h"

#include <QHash>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcOfflineCacheDatabase : public QcSqliteDatabase
{
public:
  QcOfflineCacheDatabase(const QString & sqlite_path);
  ~QcOfflineCacheDatabase();

  void insert_tile(const QcTileSpec & tile_spec);
  int has_tile(const QcTileSpec & tile_spec);
  void delete_tile(const QcTileSpec & tile_spec);

private:
  void create_tables();

  void init_cache();
  void load_providers();
  void load_map_levels();
  void init_version();
  int get_provider_id(const QString & provider);
  unsigned int hash_tile_spec(int provider_id, int map_id, int level);
  int get_map_level_id(const QcTileSpec & tile_spec);
  QString tile_where_clause(const QcTileSpec & tile_spec);

private:
  QHash<QString, int> m_providers;
  QHash<unsigned int, int> m_map_levels;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_OFFLINE_CACHE_DATABASE_H__ */
