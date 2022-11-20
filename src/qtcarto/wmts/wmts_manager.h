// -*- mode: c++ -*-

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

#ifndef __QC_WMTS_MANAGER_H__
#define __QC_WMTS_MANAGER_H__

/**************************************************************************************************/

#include <QHash>
#include <QObject>
#include <QPair>
#include <QSet>
#include <QSize>

#include "cache/file_tile_cache.h"
#include "qtcarto_global.h"
#include "wmts/wmts_tile_fetcher.h"
// #include "map_view.h" // circular

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcMapViewLayer;
typedef QSet<QcMapViewLayer *> QcMapViewLayerPointerSet;

/**************************************************************************************************/

/// The QcWmtsManager class implements a WMTS Manager for a WTMS provider.
///
/// It manages requests from several concurrent map views and dispatch
/// them to the WTMS Tile Fetcher and store tile images in a cache.
///
/// It notify the WTMS Request Manager when a tile is fetched or failed.
class QC_EXPORT QcWmtsManager : public QObject
{
  Q_OBJECT

 public:
  enum CacheArea {
    DiskCache = 0x01,
    MemoryCache = 0x02,
    AllCaches = 0xFF
  };
  Q_DECLARE_FLAGS(CacheAreas, CacheArea)

 public:
  explicit QcWmtsManager(const QString & plugin_name);
  virtual ~QcWmtsManager();

  void release_map(QcMapViewLayer * map_view_layer);

  QcWmtsTileFetcher * tile_fetcher() { return m_tile_fetcher; }
  QcFileTileCache * tile_cache();

  void update_tile_requests(QcMapViewLayer * map_view_layer,
			    const QcTileSpecSet & tiles_added,
			    const QcTileSpecSet & tiles_removed);

  /// Return a tile texture from the tile cache
  QSharedPointer<QcTileTexture> get_tile_texture(const QcTileSpec & tile_spec);

  void dump() const;

 private slots:
  // Fixme: name
  void fetcher_tile_finished(const QcTileSpec & tile_spec, const QByteArray & bytes, const QString & format);
  void fetcher_tile_error(const QcTileSpec & tile_spec, const QString & error_string);

 signals:
  void tile_error(const QcTileSpec & tile_spec, const QString & error_string);
  void tile_version_changed();

  // protected:
 public:
  void set_tile_fetcher(QcWmtsTileFetcher * tile_fetcher);
  // Fixme: unused
  void set_tile_cache(QcFileTileCache * cache);

 private:
  void remove_tile_spec(const QcTileSpec & tile_spec);

  Q_DISABLE_COPY(QcWmtsManager);

  friend class QcWmtsTileFetcher;

 private:
  QString m_plugin_name; // needed by cache directory
  QcFileTileCache * m_tile_cache;
  QcWmtsTileFetcher * m_tile_fetcher;
  /// Dictionary to store the list of requested tiles by map view
  QHash<QcMapViewLayer *, QcTileSpecSet > m_map_view_layer_dict;
  /// Dictionary to store the list of map view using a tile
  QHash<QcTileSpec, QcMapViewLayerPointerSet > m_tile_dict;
};

// Q_DECLARE_OPERATORS_FOR_FLAGS(QcWmtsManager::CacheAreas)

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_WMTS_MANAGER_H__ */
