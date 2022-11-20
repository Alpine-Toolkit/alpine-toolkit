`// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
** Copyright (C) 2015 The Qt Company Ltd.
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __QC_FILE_TILE_CACHE_H__
#define __QC_FILE_TILE_CACHE_H__

/**************************************************************************************************/

#include <QCache>
#include <QDir>
#include <QImage>
#include <QMutex>
#include <QObject>
#include <QSet>
#include <QTimer>

#include "cache/cache3q.h"
#include "cache/offline_cache.h"
#include "qtcarto_global.h"
#include "wmts/tile_spec.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class QcCachedTileMemory;
class QcFileTileCache;

/**************************************************************************************************/

// Fixme: QcTileTexture -> QcTextureImage ???

/// The QcTileTexture class encapsulates a tile spec and its image.
class QC_EXPORT QcTileTexture
{
 public:
  QcTileTexture();
  ~QcTileTexture();

 public:
  QcTileSpec tile_spec;
  QImage image;
  bool texture_bound;
};

/**************************************************************************************************/

/// This would be internal except that the eviction policy can't be defined without it being concrete here
class QcCachedTileDisk
{
 public:
  ~QcCachedTileDisk();

  QcTileSpec tile_spec;
  QString filename;
  QString format;
  QcFileTileCache * cache;
};

/**************************************************************************************************/

/// Custom eviction policy for the disk cache, to avoid deleting all the files when the application closes
class QCache3QTileEvictionPolicy : public QcCache3QDefaultEvictionPolicy<QcTileSpec, QcCachedTileDisk>
{
 protected:
  void about_to_be_removed(const QcTileSpec & key, QSharedPointer<QcCachedTileDisk> obj);
  void about_to_be_evicted(const QcTileSpec & key, QSharedPointer<QcCachedTileDisk> obj);
};

/**************************************************************************************************/

/// The QcFileTileCache class implements a tile cache.
///
/// The cache implements 3 + 1 levels:
/// * texture
/// * encoded image
/// * image on disk
/// * as well as a persistent offline cache on disk.
class QC_EXPORT QcFileTileCache : public QObject
{
  Q_OBJECT

 public:
  QcFileTileCache(const QString & directory = QString());
  ~QcFileTileCache();

  static QString base_cache_directory();

  void set_max_disk_usage(int disk_usage);
  int max_disk_usage() const;
  int disk_usage() const;

  void set_max_memory_usage(int memory_usage);
  int max_memory_usage() const;
  int memory_usage() const;

  void set_min_texture_usage(int texture_usage);
  void set_extra_texture_usage(int texture_usage);
  int max_texture_usage() const;
  int min_texture_usage() const;
  int texture_usage() const;

  void clear_all();

  QcOfflineTileCache * offline_cache() { return m_offline_cache; }

  // Fixme: encapsulate
  void insert(const QcTileSpec & tile_spec, const QByteArray & bytes, const QString & format);

  QSharedPointer<QcTileTexture> get(const QcTileSpec & tile_spec);

  // Fixme: public ???
  // QSharedPointer<QcTileTexture> load_from_disk(const QSharedPointer<QcCachedTileDisk> & tile_directory);
  QSharedPointer<QcTileTexture> load_from_disk(const QcTileSpec & tile_spec, const QString & filename);

  void handle_error(const QcTileSpec & tile_spec, const QString & error);

  // Fixme: public ???
  // can be called without a specific tileCache pointer
  static void evict_from_disk_cache(QcCachedTileDisk * td);
  static void evict_from_memory_cache(QcCachedTileMemory * tm);

  // ???
  // QcTiledMappingManagerEngine::CacheAreas areas = QcTiledMappingManagerEngine::AllCaches

 private:
  QString directory() const { return m_directory; } // Fixme: ???
  QString queue_filename(int i) const;

  void load_tiles();

  void print_stats();

  QSharedPointer<QcTileTexture> load_from_memory(const QSharedPointer<QcCachedTileMemory> & tile_memory);

  QSharedPointer<QcCachedTileDisk> add_to_disk_cache(const QcTileSpec & tile_spec, const QString & filename);
  QSharedPointer<QcCachedTileMemory> add_to_memory_cache(const QcTileSpec & tile_spec, const QByteArray & bytes, const QString & format);
  QSharedPointer<QcTileTexture> add_to_texture_cache(const QcTileSpec & tile_spec, const QImage & image);

 private:
  QString m_directory;
  int m_min_texture_usage;
  int m_extra_texture_usage;

  QcOfflineTileCache * m_offline_cache;

  /// Store image on disk
  QcCache3Q<QcTileSpec, QcCachedTileDisk, QCache3QTileEvictionPolicy > m_disk_cache;
  /// Store encoded images on memory : PNG, JPEG
  QcCache3Q<QcTileSpec, QcCachedTileMemory > m_memory_cache;
  /// Store decoded images
  QcCache3Q<QcTileSpec, QcTileTexture > m_texture_cache;
};

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_FILE_TILE_CACHE_H__ */
