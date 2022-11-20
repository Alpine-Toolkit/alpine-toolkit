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

#ifndef __QC_WMTS_REPLY_H__
#define __QC_WMTS_REPLY_H__

/**************************************************************************************************/

#include "qtcarto_global.h"
#include "wmts/network_reply.h"
#include "wmts/tile_spec.h"

#include <QByteArray>
#include <QObject>
#include <QString>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

/*!
    \class QcWmtsReply

    \brief The QcWmtsReply class manages a tile fetch operation started
    by an instance of QGeoTiledManagerEngine.

    Instances of QcWmtsReply manage the state and results of these operations.

    The isFinished(), error() and errorString() methods provide information
    on whether the operation has completed and if it completed successfully.

    The finished() and error(QcWmtsReply::Error,QString)
    signals can be used to monitor the progress of the operation.

    It is possible that a newly created QcWmtsReply may be in a finished
    state, most commonly because an error has occurred. Since such an instance
    will never emit the finished() or
    error(QcWmtsReply::Error,QString) signals, it is
    important to check the result of isFinished() before making the connections
    to the signals.

    If the operation completes successfully the results are accessed by
    mapImageData() and mapImageFormat().
*/

/// The QcWmtsReply class implements an abstract class to manage a tile fetch operation
/// started by the tile fetcher.
///
/// This class encapsulates the image data (network reply) and the tile spec.
class QC_EXPORT QcWmtsReply : public QcNetworkReply
{
  Q_OBJECT

 public:
  /// Constructs a tiled map reply object based on \a request, with parent \a parent.
  QcWmtsReply(QNetworkReply * reply, const QcTileSpec & tile_spec);
  // Fixme: undefined is .cpp is removed... MOC ???
  // : QcNetworkReply(reply)
  // , m_tile_spec(tile_spec)
  // {}

  /// Destroys this tiled map reply object.
  ~QcWmtsReply(); // {}

  /// Returns the request which corresponds to this reply.
  QcTileSpec tile_spec() const { return m_tile_spec; }

  /// Returns the tile image data.
  QByteArray image_data() const { return m_image_data; }
  /// Returns the format of the tile image.
  QString image_format() const { return m_image_format; }

 protected:
  /// Sets the tile image data to \a data.
  void set_image_data(const QByteArray & data) { m_image_data = data; }
  /// Sets the format of the tile image to \a format.
  void set_image_format(const QString & format) { m_image_format = format; }

 private:
  Q_DISABLE_COPY(QcWmtsReply);

 private:
  QcTileSpec m_tile_spec;
  QByteArray m_image_data;
  QString m_image_format;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_WMTS_REPLY_H__ */
