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

#ifndef __QC_WMTS_REQUEST_MANAGER_H__
#define __QC_WMTS_REQUEST_MANAGER_H__

/**************************************************************************************************/

#include "qtcarto_global.h"
#include "cache/file_tile_cache.h"
#include "wmts/tile_spec.h"
#include "wmts/wmts_manager.h"

#include <QHash>
#include <QObject>
#include <QPointer>
#include <QSet>
#include <QSharedPointer>
#include <QSize>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class QcMapViewLayer; // circular

/**************************************************************************************************/

/// The QcRetryFuture class represents a tile that needs to be retried after a certain period of time.
class QcRetryFuture : public QObject
{
  Q_OBJECT

 public:
  QcRetryFuture(const QcTileSpec & tile_spec, QcMapViewLayer * map_view_layer, QcWmtsManager * wmts_manager);

 public slots:
  void retry();

 private:
  QcTileSpec m_tile_spec;
  QcMapViewLayer * m_map_view_layer;
  QPointer<QcWmtsManager> m_wmts_manager;
};

/**************************************************************************************************/

/// The QcWmtsRequestManager class implements a WMTS Request Manager for a map view.
///
/// It works as a proxy between the map view and WTMS Request Manager.
class QcWmtsRequestManager : public QObject
{
  Q_OBJECT;

 public:
  explicit QcWmtsRequestManager(QcMapViewLayer * map_view_layer, QcWmtsManager * wmts_manager);
  ~QcWmtsRequestManager();

  /// Request a new tile sets
  QList<QSharedPointer<QcTileTexture> > request_tiles(const QcTileSpecSet & tile_specs);

  /// Notify the map view that a tile is fetched.
  void tile_fetched(const QcTileSpec & tile_spec);
  /// Retry to fetch an errored tile request.
  void tile_error(const QcTileSpec & tile_spec, const QString & error_string);

  /// Get the tile texture from the WTMS Manager cache.
  QSharedPointer<QcTileTexture> tile_texture(const QcTileSpec & tile_spec);

 private:
  Q_DISABLE_COPY(QcWmtsRequestManager)

 private:
  QcMapViewLayer * m_map_view_layer;
  QPointer<QcWmtsManager> m_wmts_manager;
  QcTileSpecSet m_requested;
  QHash<QcTileSpec, int> m_retries;
  QHash<QcTileSpec, QSharedPointer<QcRetryFuture> > m_futures;
};

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_WMTS_REQUEST_MANAGER_H__ */
