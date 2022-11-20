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

// Fixme: implement a filesystem scan to fix/update the database

/// The QcOfflineCacheDatabase class implements a database to query if a tile is cached.
///
/// It purpose is to provide a fast way to know if a tile is available on disk.
///
/// Alternative Solutions:
/// * query the filesystem: could be slow if there is a lot of entries in a directory
/// * scan the filesystem and build an index: slower startup ?
/// * load the SQL database in an index: faster indexing vs memory ???
class QcOfflineCacheDatabase : public QcSqliteDatabase
{
 public:
  QcOfflineCacheDatabase(const QString & sqlite_path);
  ~QcOfflineCacheDatabase();

  void insert_tile(const QcTileSpec & tile_spec);
  int has_tile(const QcTileSpec & tile_spec); // Fixme: bool ? offline_count purpose ???
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
