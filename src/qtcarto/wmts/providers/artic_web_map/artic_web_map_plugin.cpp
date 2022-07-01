/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "artic_web_map_plugin.h"
#include "qtcarto.h"

/**************************************************************************************************/

QcArticWebMapLayer::QcArticWebMapLayer(QcArticWebMapPlugin * plugin,
                                       int map_id,
                                       int position,
                                       const QString & title,
                                       const QString & name)
  : QcWmtsPluginLayer(plugin, map_id, position, title, name, QStringLiteral("png"))
{}

QcArticWebMapLayer::QcArticWebMapLayer(const QcArticWebMapLayer & other)
  : QcWmtsPluginLayer(other)
{}

QcArticWebMapLayer::~QcArticWebMapLayer()
{}

QUrl
QcArticWebMapLayer::url(const QcTileSpec & tile_spec) const
{
  /* http://{s}.tiles.arcticconnect.org/osm_{projection}/{z}/{x}/{y}.png
   *
   * where {s} is either a, b or c, {projection} is one of 3571, 3572,
   * 3573, 3574, 3575 or 3576, {z} is the zoom level, {x} is the tile
   * x-index, and {y} is the tile y-index.
   */

  return QUrl(QStringLiteral("http://a.tiles.arcticconnect.org/osm_3571/") +
              QString::number(tile_spec.level()) + QLatin1Char('/') +
              QString::number(tile_spec.x()) + QLatin1Char('/') +
              QString::number(tile_spec.y()) +
              QLatin1Char('.') + image_format());
}

/**************************************************************************************************/

const QString QcArticWebMapPlugin::PLUGIN_NAME = "artic-web-map-3571";
const QString PLUGIN_TITLE = "Artic Web Map";
constexpr int NUMBER_OF_LEVELS = 20;
constexpr int TILE_SIZE = 256;

QcArticWebMapPlugin::QcArticWebMapPlugin()
  : QcWmtsPlugin(PLUGIN_NAME, PLUGIN_TITLE,
                 new  QcTileMatrixSet(QcProjection::by_srid(QStringLiteral("epsg:3571")),
                                      QcVectorDouble(1., -1.),
                                      QcVectorDouble(-HALF_EQUATORIAL_PERIMETER, HALF_EQUATORIAL_PERIMETER), // Fixme: use projection
                                      QcWgsCoordinate(180., 90.),
                                      NUMBER_OF_LEVELS,
                                      TILE_SIZE))
{
  int map_id = -1;
  add_layer(new QcArticWebMapLayer(this,
                                   ++map_id, // 1
                                   1,
                                   QStringLiteral("Bearing Sea Map ESPG:3571"),
                                   QStringLiteral("espg-3571")));
}

QcArticWebMapPlugin::~QcArticWebMapPlugin()
{}
