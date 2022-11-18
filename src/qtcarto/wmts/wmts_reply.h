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

/// The QcWmtsReply class implements an abstract class to manage a tile fetch operation
/// started by an instance of.
class QC_EXPORT QcWmtsReply : public QcNetworkReply
{
  Q_OBJECT

 public:
  QcWmtsReply(QNetworkReply * reply, const QcTileSpec & tile_spec);
  virtual ~QcWmtsReply();

  /// Returns the request which corresponds to this reply.
  QcTileSpec tile_spec() const { return m_tile_spec; }

  /// Returns the tile image data.
  QByteArray map_image_data() const { return m_map_image_data; }
  /// Returns the format of the tile image.
  QString map_image_format() const { return m_map_image_format; }

 protected:
  /// Sets the tile image data to \a data.
  void set_map_image_data(const QByteArray & data) { m_map_image_data = data; }
  /// Sets the format of the tile image to \a format.
  void set_map_image_format(const QString & format) { m_map_image_format = format; }

 private:
  Q_DISABLE_COPY(QcWmtsReply);

 private:
  QcTileSpec m_tile_spec;
  QByteArray m_map_image_data;
  QString m_map_image_format;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_WMTS_REPLY_H__ */
