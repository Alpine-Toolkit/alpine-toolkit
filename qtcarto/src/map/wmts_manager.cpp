/***************************************************************************************************
 **
 ** $QTCARTO_BEGIN_LICENSE:GPL3$
 **
 ** Copyright (C) 2016 Fabrice Salvaire
 ** Contact: http://www.fabrice-salvaire.fr
 **
 ** This file is part of the QtCarto library.
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
 ** $QTCARTO_END_LICENSE$
 **
 ***************************************************************************************************/

/****************************************************************************
 **
 ** Copyright (C) 2015 The Qt Company Ltd.
 ** Contact: http://www.qt.io/licensing/
 **
 ** This file is part of the QtLocation module of the Qt Toolkit.
 **
 ** $QT_BEGIN_LICENSE:LGPL3$
 ** Commercial License Usage
 ** Licensees holding valid commercial Qt licenses may use this file in
 ** accordance with the commercial license agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and The Qt Company. For licensing terms
 ** and conditions see http://www.qt.io/terms-conditions. For further
 ** information use the contact form at http://www.qt.io/contact-us.
 **
 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 3 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPLv3 included in the
 ** packaging of this file. Please review the following information to
 ** ensure the GNU Lesser General Public License version 3 requirements
 ** will be met: https://www.gnu.org/licenses/lgpl.html.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 2.0 or later as published by the Free
 ** Software Foundation and appearing in the file LICENSE.GPL included in
 ** the packaging of this file. Please review the following information to
 ** ensure the GNU General Public License version 2.0 requirements will be
 ** met: http://www.gnu.org/licenses/gpl-2.0.html.
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

/**************************************************************************************************/

#include "wmts_manager.h"

#include <QDir>
#include <QLocale>
#include <QStandardPaths>
#include <QTimer>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

QcWmtsManager::QcWmtsManager()
  : QObject(),
    // m_tileVersion(-1),
    // cacheHint_(QcWmtsManager::AllCaches),
    m_tile_cache(nullptr),
    m_tile_fetcher(nullptr)
{
}

/*!
  Destroys this mapping manager.
*/
QcWmtsManager::~QcWmtsManager()
{
  delete m_tile_cache;
}

void
QcWmtsManager::set_tile_fetcher(QcWmtsTileFetcher * tile_fetcher)
{
  qRegisterMetaType<QcTileSpec>();

  // Connect tile fetcher signals
  connect(m_tile_fetcher, SIGNAL(tile_finished(QcTileSpec, QByteArray, QString)),
	  this, SLOT(engine_tile_finished(QcTileSpec, QByteArray, QString)),
	  Qt::QueuedConnection);
  connect(m_tile_fetcher, SIGNAL(tile_error(QcTileSpec, QString)),
	  this, SLOT(engine_tile_error(QcTileSpec, QString)),
	  Qt::QueuedConnection);

  // engine_initialized();
}

QcWmtsTileFetcher *
QcWmtsManager::tile_fetcher()
{
  return m_tile_fetcher;
}

QcMapView *
QcWmtsManager::create_map()
{
  return nullptr;
}

void
QcWmtsManager::release_map(QcMapView * map_view)
{
  m_map_view_hash.remove(map_view);

  // Update m_tile_hash
  QHash<QcTileSpec, QSet<QcMapView *> > new_tile_hash = m_tile_hash;
  typedef QHash<QcTileSpec, QSet<QcMapView *> >::const_iterator hash_iterator;
  hash_iterator iter = m_tile_hash.constBegin();
  hash_iterator iter_end = m_tile_hash.constEnd();
  for (; iter != iter_end; ++iter) { // Fixme: cxx11
    QSet<QcMapView *> map_views = iter.value();
    if (map_views.contains(map_view)) {
      map_views.remove(map_view);
      if (map_views.isEmpty())
	new_tile_hash.remove(iter.key());
      else
	new_tile_hash.insert(iter.key(), map_views); // Fixme: inplace update ?
    }
  }
  m_tile_hash = new_tile_hash;
}

void
QcWmtsManager::update_tile_requests(QcMapView * map_view,
				    const QSet<QcTileSpec> & tiles_added,
				    const QSet<QcTileSpec> & tiles_removed)
{
  typedef QSet<QcTileSpec>::const_iterator tile_iter;
  tile_iter iter, iter_end;

  // add and remove tiles from tileset for this map_view

  QSet<QcTileSpec> old_tiles = m_map_view_hash.value(map_view);

  iter = tiles_removed.constBegin();
  iter_end = tiles_removed.constEnd();
  for (; iter != iter_end; ++iter) {
    old_tiles.remove(*iter);
  }

  iter = tiles_added.constBegin();
  iter_end = tiles_added.constEnd();
  for (; iter != iter_end; ++iter) {
    old_tiles.insert(*iter);
  }

  m_map_view_hash.insert(map_view, old_tiles);

  // add and remove map from mapset for the tiles

  QSet<QcTileSpec> requested_tiles;
  QSet<QcTileSpec> canceled_tiles;

  iter = tiles_removed.constBegin();
  for (; iter != iter_end; ++iter) {
    QSet<QcMapView *> map_view_set = m_tile_hash.value(*iter);
    map_view_set.remove(map_view);
    if (map_view_set.isEmpty()) {
      canceled_tiles.insert(*iter);
      m_tile_hash.remove(*iter);
    } else {
      m_tile_hash.insert(*iter, map_view_set);
    }
  }

  iter = tiles_added.constBegin();
  for (; iter != iter_end; ++iter) {
    QSet<QcMapView *> map_view_set = m_tile_hash.value(*iter);
    if (map_view_set.isEmpty()) {
      requested_tiles.insert(*iter);
    }
    map_view_set.insert(map_view);
    m_tile_hash.insert(*iter, map_view_set);
  }

  canceled_tiles -= requested_tiles;

  QMetaObject::invokeMethod(m_tile_fetcher, "update_tile_requests",
			    Qt::QueuedConnection,
			    Q_ARG(QSet<QcTileSpec>, requested_tiles),
			    Q_ARG(QSet<QcTileSpec>, canceled_tiles));
}

void
QcWmtsManager::engine_tile_finished(const QcTileSpec & tile_spec, const QByteArray & bytes, const QString & format)
{
  QSet<QcMapView *> map_views = m_tile_hash.value(tile_spec);

  // Remove tile_spec in sets
  // Fixme: duplicated code, inplace update ?
  for (QcMapView * map_view : map_views) {
    QSet<QcTileSpec> tile_set = m_map_view_hash.value(map_view);
    tile_set.remove(tile_spec);
    if (tile_set.isEmpty())
      m_map_view_hash.remove(map_view);
    else
      m_map_view_hash.insert(map_view, tile_set);
  }
  m_tile_hash.remove(tile_spec);

  tile_cache()->insert(tile_spec, bytes, format); // , m_cache_hint

  // Fixme:
  // for (QcMapView * map_view : map_views)
  //   (*map_view)->request_manager()->tile_fetched(tile_spec);
}

void
QcWmtsManager::engine_tile_error(const QcTileSpec & tile_spec, const QString & error_string)
{
  QSet<QcMapView *> map_views = m_tile_hash.value(tile_spec);

  // Remove tile_spec in sets
  // Fixme: duplicated code, inplace update ?
  for (QcMapView * map_view : map_views) {
    QSet<QcTileSpec> tile_set = m_map_view_hash.value(map_view);
    tile_set.remove(tile_spec);
    if (tile_set.isEmpty())
      m_map_view_hash.remove(map_view);
    else
      m_map_view_hash.insert(map_view, tile_set);
  }
  m_tile_hash.remove(tile_spec);

  // Fixme:
  // for (QcMapView * map_view : map_views)
  //   (*map_view)->requestManager()->tile_error(spec, error_string);

  emit tile_error(tile_spec, error_string);
}

/*
  void
  QcWmtsManager::set_tile_size(const QSize & tile_size)
  {
  m_tile_size = tile_size;
  }

  void QcWmtsManager::set_tile_version(int version)
  {
  if (m_tile_version != version) {
  m_tile_version = version;
  emit tile_version_changed();
  }
  }

  QSize
  QcWmtsManager::tile_size() const
  {
  return m_tile_size;
  }

  int QcWmtsManager::tile_version() const
  {
  return m_tile_version;
  }

  QcWmtsManager::CacheAreas
  QcWmtsManager::cache_hint() const
  {
  return m_cache_hint;
  }

  void
  QcWmtsManager::set_cache_hint(QcWmtsManager::CacheAreas cache_hint)
  {
  m_cache_hint = cache_hint;
  }
*/

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
    // QString cache_directory;
    // if (!manager_name().isEmpty())
    //   cache_directory = QcFileTileCache::base_cache_directory() + manager_name();
    m_tile_cache = new QcFileTileCache(); // cache_directory
  }
  return m_tile_cache;
}

QSharedPointer<QcTileTexture>
QcWmtsManager::get_tile_texture(const QcTileSpec & tile_spec)
{
  return m_tile_cache->get(tile_spec);
}

// QC_END_NAMESPACE

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
