/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
** Copyright (C) 2015 The Qt Company Ltd.
** Qt Location QGeoTiledMappingManagerEngine qgeotiledmappingmanagerengine.cpp
**
***************************************************************************************************/

/**************************************************************************************************/

#include "wmts_manager.h"
#include "qtcarto.h"

#include "map/map_view.h" // circular

#include <QDir>
#include <QLocale>
#include <QStandardPaths>
#include <QTimer>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

QcWmtsManager::QcWmtsManager(const QString & plugin_name)
  : QObject(),
    m_plugin_name(plugin_name),
    m_tile_cache(nullptr), // lazy instantiated in tile_cache()
    m_tile_fetcher(nullptr) // must call set_tile_fetcher() !!!
{}

/// Destroys this mapping manager.
QcWmtsManager::~QcWmtsManager()
{
  if (m_tile_cache)
    delete m_tile_cache;
}

void
QcWmtsManager::set_tile_fetcher(QcWmtsTileFetcher * tile_fetcher)
{
  m_tile_fetcher = tile_fetcher;

  qRegisterMetaType<QcTileSpec>();

  // Connect tile fetcher signals
  connect(m_tile_fetcher, &QcWmtsTileFetcher::tile_finished,
	  this, &QcWmtsManager::fetcher_tile_finished,
	  Qt::QueuedConnection);
  connect(m_tile_fetcher, &QcWmtsTileFetcher::tile_error,
	  this, &QcWmtsManager::fetcher_tile_error,
	  Qt::QueuedConnection);
}

// Fixme: unused
void
QcWmtsManager::set_tile_cache(QcFileTileCache * cache)
{
  Q_ASSERT_X(!m_tile_cache, Q_FUNC_INFO, "This should be called only once");
  m_tile_cache = cache;
}

QcFileTileCache *
QcWmtsManager::tile_cache()
{
  if (!m_tile_cache) {
    QString cache_directory = QcFileTileCache::base_cache_directory() + QDir::separator() + m_plugin_name;
    m_tile_cache = new QcFileTileCache(cache_directory);
  }
  return m_tile_cache;
}

void
QcWmtsManager::remove_tile_spec(const QcTileSpec & tile_spec)
{
  // Remove tile_spec in sets

  auto map_view_layers = m_tile_dict.value(tile_spec);

  // Fixme: inplace update ?
  for (auto map_view_layer : map_view_layers) {
    auto tile_set = m_map_view_layer_dict.value(map_view_layer);
    tile_set.remove(tile_spec);
    if (tile_set.isEmpty())
      m_map_view_layer_dict.remove(map_view_layer);
    else
      m_map_view_layer_dict.insert(map_view_layer, tile_set);
  }

  m_tile_dict.remove(tile_spec);
}

void
QcWmtsManager::release_map(QcMapViewLayer * map_view_layer)
{
  m_map_view_layer_dict.remove(map_view_layer);

  // Update m_tile_dict
  QHash<QcTileSpec, QcMapViewLayerPointerSet > new_tile_dict = m_tile_dict;
  // for (auto & tile_spec : m_tile_dict.keys())
  typedef QHash<QcTileSpec, QcMapViewLayerPointerSet >::const_iterator hash_iterator;
  hash_iterator iter = m_tile_dict.constBegin();
  hash_iterator iter_end = m_tile_dict.constEnd();
  for (; iter != iter_end; ++iter) { // Fixme: cxx11
    QcMapViewLayerPointerSet map_view_layers = iter.value();
    if (map_view_layers.contains(map_view_layer)) {
      map_view_layers.remove(map_view_layer);
      if (map_view_layers.isEmpty())
	new_tile_dict.remove(iter.key());
      else
	new_tile_dict.insert(iter.key(), map_view_layers); // Fixme: inplace update ?
    }
  }
  m_tile_dict = new_tile_dict;
}

void
QcWmtsManager::update_tile_requests(QcMapViewLayer * map_view_layer,
				    const QcTileSpecSet & tiles_added,
				    const QcTileSpecSet & tiles_removed)
{
  // Update tile set for this map view
  auto old_tiles = m_map_view_layer_dict.value(map_view_layer);
  old_tiles -= tiles_removed;
  old_tiles += tiles_added;
  m_map_view_layer_dict.insert(map_view_layer, old_tiles);

  // Update map view dict

  // Fixme: it only makes sense if we have several map views...
  // Fixme: duplicated code, inplace update ?
  QcTileSpecSet canceled_tiles;
  for (auto & tile_spec : tiles_removed) {
    // Fixme: ok if set is small
    auto map_view_layer_set = m_tile_dict.value(tile_spec); // QcMapViewLayerPointerSet
    map_view_layer_set.remove(map_view_layer);
    if (map_view_layer_set.isEmpty()) {
      m_tile_dict.remove(tile_spec);
      canceled_tiles.insert(tile_spec);
    } else
      m_tile_dict.insert(tile_spec, map_view_layer_set);
  }

  QcTileSpecSet requested_tiles;
  for (auto & tile_spec : tiles_added) {
    auto map_view_layer_set = m_tile_dict.value(tile_spec);
    if (map_view_layer_set.isEmpty())
      requested_tiles.insert(tile_spec);
    map_view_layer_set.insert(map_view_layer);
    m_tile_dict.insert(tile_spec, map_view_layer_set);
  }

  // Fixme: why ?
  canceled_tiles -= requested_tiles;

  // async call
  // qQCInfo() << "async call update_tile_requests +" << requested_tiles << "-" << canceled_tiles;1
  QMetaObject::invokeMethod(m_tile_fetcher, "update_tile_requests",
                            // Fixme: segfault in the past
                            Qt::QueuedConnection,
  			    Q_ARG(QSet<QcTileSpec>, requested_tiles), // QcTileSpecSet
  			    Q_ARG(QSet<QcTileSpec>, canceled_tiles));
  // qQCInfo() << "end of";
}

// Fixme: name
void
QcWmtsManager::fetcher_tile_finished(const QcTileSpec & tile_spec, const QByteArray & bytes, const QString & format)
{
  // qQCInfo();
  // Is tile requested by a map view ?
  if (m_tile_dict.contains(tile_spec)) {
    auto map_view_layers = m_tile_dict.value(tile_spec);
    remove_tile_spec(tile_spec);
    tile_cache()->insert(tile_spec, bytes, format);
    for (QcMapViewLayer * map_view_layer : map_view_layers)
      map_view_layer->request_manager()->tile_fetched(tile_spec);
  }
  // else
  //   qQCInfo() << "any client" << tile_spec;
}

void
QcWmtsManager::fetcher_tile_error(const QcTileSpec & tile_spec, const QString & error_string)
{
  // qQCInfo();
  auto map_view_layers = m_tile_dict.value(tile_spec);
  remove_tile_spec(tile_spec);

  for (QcMapViewLayer * map_view_layer : map_view_layers)
    map_view_layer->request_manager()->tile_error(tile_spec, error_string);

  emit tile_error(tile_spec, error_string);
}

QSharedPointer<QcTileTexture>
QcWmtsManager::get_tile_texture(const QcTileSpec & tile_spec)
{
  return m_tile_cache->get(tile_spec);
}

void
QcWmtsManager::dump() const
{
  qQCInfo() << "Dump";
  for (auto & tile_spec : m_tile_dict.keys())
    qQCInfo() << tile_spec << "--->" << m_tile_dict[tile_spec];
  for (auto & map_view_layer : m_map_view_layer_dict.keys())
    qQCInfo() << map_view_layer << "--->" << m_map_view_layer_dict[map_view_layer];
}

/**************************************************************************************************/

// #include "wmts_manager.moc"

// QC_END_NAMESPACE
