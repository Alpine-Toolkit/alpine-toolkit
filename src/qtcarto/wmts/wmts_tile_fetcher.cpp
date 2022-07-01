/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtLocation module of the Qt Toolkit.
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) None Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
****************************************************************************/

/**************************************************************************************************/

#include "wmts_tile_fetcher.h"
#include "qtcarto.h"

#include <QtCore/QTimerEvent>

#include <QtDebug>

/**************************************************************************************************/

QcWmtsTileFetcher::QcWmtsTileFetcher()
  : QObject(),
    m_enabled(true)
{
  // Fixme: useless ?
  // if (!m_queue.isEmpty())
  //   m_timer.start(0, this);
}

QcWmtsTileFetcher::~QcWmtsTileFetcher()
{}

void
QcWmtsTileFetcher::update_tile_requests(const QcTileSpecSet & tiles_added,
					const QcTileSpecSet & tiles_removed)
{
  // qQCInfo();
  // << tiles_added;
  // << tiles_removed;

  QMutexLocker mutex_locker(&m_queue_mutex);

  cancel_tile_requests(tiles_removed);
  m_queue += QList<QcTileSpec>(tiles_added.begin(), tiles_added.end());

  // Start timer to fetch tiles from queue
  if (m_enabled && !m_queue.isEmpty() && !m_timer.isActive()) {
    m_timer.start(0, this);
  }
}

void
QcWmtsTileFetcher::cancel_tile_requests(const QcTileSpecSet & tiles)
{
  // Delete objects and abort requests if they are still running
  for (const QcTileSpec & tile_spec: tiles) {
    QcWmtsReply * reply = m_invmap.value(tile_spec, nullptr);
    if (reply) {
      m_invmap.remove(tile_spec);
      reply->abort();
      if (reply->is_finished())
	reply->deleteLater();
    }
    // Fixme: else ?
    m_queue.removeAll(tile_spec);
  }
}

void
QcWmtsTileFetcher::request_next_tile()
{
  // qQCInfo();

  QMutexLocker mutex_locker(&m_queue_mutex);

  if (!m_enabled || m_queue.isEmpty())
    return;

  QcTileSpec tile_spec = m_queue.takeFirst();

  // qQCInfo() << tile_spec;
  QcWmtsReply *wmts_reply = get_tile_image(tile_spec);

  // If the request is already finished then handle it
  // Else connect the finished signal
  if (wmts_reply->is_finished()) {
    handle_reply(wmts_reply, tile_spec);
  } else {
    connect(wmts_reply, SIGNAL(finished()),
	    this, SLOT(finished()),
	    Qt::QueuedConnection);
    m_invmap.insert(tile_spec, wmts_reply);
  }

  if (m_queue.isEmpty())
    m_timer.stop();
}

void
QcWmtsTileFetcher::finished()
{
  // qQCInfo();

  QMutexLocker mutex_locker(&m_queue_mutex);

  QcWmtsReply *wmts_reply = qobject_cast<QcWmtsReply *>(sender());
  if (!wmts_reply) // Fixme: when ?
    return;

  QcTileSpec tile_spec = wmts_reply->tile_spec();

  if (!m_invmap.contains(tile_spec)) { // Fixme: when ?
    wmts_reply->deleteLater();
    return;
  }

  m_invmap.remove(tile_spec);

  handle_reply(wmts_reply, tile_spec);
}

void
QcWmtsTileFetcher::timerEvent(QTimerEvent * event)
{
  // qQCInfo();
  if (event->timerId() != m_timer.timerId()) { // Fixme: when ?
    QObject::timerEvent(event);
    return;
  } else if (m_queue.isEmpty()) {
    m_timer.stop();
    return;
  } else
    request_next_tile();
}

void
QcWmtsTileFetcher::handle_reply(QcWmtsReply * wmts_reply, const QcTileSpec & tile_spec)
{
  // qQCInfo();

  if (!m_enabled) {
    wmts_reply->deleteLater();
    return;
  }

  // emit signal according to the reply status
  if (wmts_reply->error() == QcWmtsReply::NoError) {
    // qQCInfo() << "emit tile_finished" << tile_spec;
    emit tile_finished(tile_spec, wmts_reply->map_image_data(), wmts_reply->map_image_format());
  } else {
    // qQCInfo() << "emit tile_error" << tile_spec;
    emit tile_error(tile_spec, wmts_reply->error_string());
  }

  wmts_reply->deleteLater();
}

/**************************************************************************************************/

// #include "wmts_tile_fetcher.moc"
