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

#ifndef __QC_WMTS_TILE_FETCHER_H__
#define __QC_WMTS_TILE_FETCHER_H__

/**************************************************************************************************/

#include <QHash>
#include <QList>
#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QSize>
#include <QTimer>

#include "qtcarto_global.h"
#include "wmts/tile_spec.h"
#include "wmts/wmts_reply.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

/// The QcWmtsTileFetcher class implements a WMTS Tile Fetcher abstract class for WMTS providers.
///
/// It must be subclassed for each provider in order to provide an implementation for the get_tile_image method.
/// It manages a request queue, schedule requests and emit a signal when a request finishes or fails.
class QC_EXPORT QcWmtsTileFetcher : public QObject
{
  Q_OBJECT

 public:
  QcWmtsTileFetcher();
  virtual ~QcWmtsTileFetcher();

 public slots:
  // Fixme: why ???
  // void update_tile_requests(const QcTileSpecSet & tiles_added, const QcTileSpecSet & tiles_removed);
  void update_tile_requests(const QSet<QcTileSpec> & tiles_added, const QSet<QcTileSpec> & tiles_removed);

 private slots:
  void cancel_tile_requests(const QcTileSpecSet & tile_specs);
  void request_next_tile();
  void finished();

 signals:
  void tile_finished(const QcTileSpec & tile_spec, const QByteArray & bytes, const QString & format);
  void tile_error(const QcTileSpec & tile_spec, const QString & errorString);

 protected:
  void timerEvent(QTimerEvent * event);
  // QGeoTiledMappingManagerEngine::CacheAreas cache_hint() const;

 private:
  /// abstract method to return a future for the tile request
  virtual QcWmtsReply * get_tile_image(const QcTileSpec & tile_spec) = 0;
  void handle_reply(QcWmtsReply * wmts_reply, const QcTileSpec & tile_spec);

  // Q_DECLARE_PRIVATE(QcWmtsTileFetcher);
  // Q_DISABLE_COPY(QcWmtsTileFetcher);

 private:
  bool m_enabled;
  QBasicTimer m_timer;
  QMutex m_queue_mutex;
  QList<QcTileSpec> m_queue;
  QHash<QcTileSpec, QcWmtsReply *> m_invmap;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_WMTS_TILE_FETCHER_H__ */
