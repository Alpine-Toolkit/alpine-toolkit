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

#ifndef __QC_OFFLINE_CACHE_H__
#define __QC_OFFLINE_CACHE_H__

/**************************************************************************************************/

#include <QHash>
#include <QSharedPointer>
#include <QString>

#include "qtcarto_global.h"
#include "cache/offline_cache_database.h"
#include "wmts/tile_spec.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

/*
 * count tile
 * per layer
 *
 */

class QcOfflineCachedTileDisk
{
public:
  QcOfflineCachedTileDisk();
  QcOfflineCachedTileDisk(const QcOfflineCachedTileDisk & other);

  QcOfflineCachedTileDisk & operator=(const QcOfflineCachedTileDisk & other);

public:
  QcTileSpec tile_spec;
  QString filename;
  QString format;
};

class QC_EXPORT QcOfflineTileCache // : public QObject
{
  // Q_OBJECT

 public:
  QcOfflineTileCache(const QString & directory = QString());
  ~QcOfflineTileCache();

  void clear_all();

  bool contains(const QcTileSpec & tile_spec) const;
  // QSharedPointer<QcOfflineCachedTileDisk> get(const QcTileSpec & tile_spec); //  const
  QcOfflineCachedTileDisk get(const QcTileSpec & tile_spec); //  const
  void insert(const QcTileSpec & tile_spec, const QByteArray & bytes, const QString & format);

 private:
  void load_tiles();
  void add_to_disk_cache(const QcTileSpec & tile_spec, const QString & filename);

 private:
  QString m_directory;
  QcOfflineCacheDatabase * m_database;
  // QHash<QcTileSpec, QSharedPointer<QcOfflineCachedTileDisk>> m_offline_cache;
  QHash<QcTileSpec, QcOfflineCachedTileDisk> m_offline_cache;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

#endif /* __QC_OFFLINE_CACHE_H__ */
