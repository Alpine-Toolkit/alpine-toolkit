/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "austria_plugin.h"
#include "qtcarto.h"

/**************************************************************************************************/

QcAustriaLayer::QcAustriaLayer(QcAustriaPlugin * plugin,
                               int map_id,
                               int position,
                               const QString & title,
                               const QString & name,
                               const QString & image_format)
  : QcWmtsPluginLayer(plugin, map_id, position, title, name, image_format)
{}

// QcAustriaLayer::QcAustriaLayer(const QcAustriaLayer & other)
//   : QcWmtsPluginLayer(other)
// {}

QUrl
QcAustriaLayer::url(const QcTileSpec & tile_spec) const
{
  // http://basemap.at/application
  // http://maps.wien.gv.at/basemap/geolandbasemap/normal/google3857/8/90/135.png
  // http://maps3.wien.gv.at/basemap/bmaphidpi/normal/google3857/14/5721/8846.jpeg

  return QUrl(QStringLiteral("http://maps.wien.gv.at/basemap/") +
              name() + QLatin1Char('/') +
              QStringLiteral("normal/") +
              QStringLiteral("google3857/") +
              QString::number(tile_spec.level()) + QLatin1Char('/') +
              QString::number(tile_spec.x()) + QLatin1Char('/') +
              QString::number(tile_spec.y()) +
              QLatin1Char('.') + image_format());
}

/**************************************************************************************************/

const QString QcAustriaPlugin::PLUGIN_NAME = "austria";
const QString PLUGIN_TITLE = "Austria";
constexpr int NUMBER_OF_LEVELS = 20;
constexpr int TILE_SIZE = 512; // 256

QcAustriaPlugin::QcAustriaPlugin()
  : QcWmtsPlugin(PLUGIN_NAME, PLUGIN_TITLE,
                 new QcMercatorTileMatrixSet(NUMBER_OF_LEVELS, TILE_SIZE)) // Fixme: offset ?
{
  int map_id = -1;
  add_layer(new QcAustriaLayer(this,
                               ++map_id, // 1
                               1,
                               QStringLiteral("Standard Map"),
                               QStringLiteral("geolandbasemap"),
                               QStringLiteral("png")
                               ));
}

QcAustriaPlugin::~QcAustriaPlugin()
{}
