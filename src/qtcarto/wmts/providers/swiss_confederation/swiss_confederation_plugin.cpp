/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "swiss_confederation_plugin.h"
#include "qtcarto.h"

/**************************************************************************************************/

QcSwissConfederationLayer::QcSwissConfederationLayer(QcSwissConfederationPlugin * plugin,
                                                     int map_id,
                                                     int position,
                                                     const QString & title,
                                                     const QString & name,
                                                     const QString & image_format)
  : QcWmtsPluginLayer(plugin, map_id, position, title, name, image_format)
{}

// QcSwissConfederationLayer::QcSwissConfederationLayer(const QcSwissConfederationLayer & other)
//   : QcWmtsPluginLayer(other)
// {}

QUrl
QcSwissConfederationLayer::url(const QcTileSpec & tile_spec) const
{
  // http://wmts20.geo.admin.ch/1.0.0/' + layername + '/default/' + timestamp + '/3857/{z}/{x}/{y}.jpeg'
  // http://wmts20.geo.admin.ch/1.0.0/ch.swisstopo.pixelkarte-farbe/default/20151231/3857/15/17122/11501.jpeg
  // http://wmts20.geo.admin.ch/1.0.0/ch.swisstopo.pixelkarte-farbe/default/current/3857/10/532/361.jpeg
  // https://wmts20.geo.admin.ch/1.0.0/ch.astra.wanderland/default/20160315/21781/10/527/362.png
  return QUrl(QStringLiteral("https://wmts20.geo.admin.ch/1.0.0/") +
              name()  + QLatin1Char('/') +
              QStringLiteral("default/") +
              // QStringLiteral("20151231") + QLatin1Char('/') +
              QStringLiteral("20160315") + QLatin1Char('/') +
              // QStringLiteral("current") + QLatin1Char('/') +
              // QStringLiteral("3857/") +
              QStringLiteral("21781/") +
              QString::number(tile_spec.level()) + QLatin1Char('/') +
              QString::number(tile_spec.x()) + QLatin1Char('/') +
              QString::number(tile_spec.y()) +
              QLatin1Char('.') + image_format());
}

/**************************************************************************************************/

const QString QcSwissConfederationPlugin::PLUGIN_NAME = "swiss";
const QString PLUGIN_TITLE = "Swiss Confederation";
constexpr int NUMBER_OF_LEVELS = 20;
constexpr int TILE_SIZE = 256;

QcSwissConfederationPlugin::QcSwissConfederationPlugin()
  : QcWmtsPlugin(PLUGIN_NAME, PLUGIN_TITLE,
                 new QcMercatorTileMatrixSet(NUMBER_OF_LEVELS, TILE_SIZE))
{
  int map_id = -1;
  // add_layer(new QcSwissConfederationLayer(this,
  //                                         ++map_id, // 1
  //                                         1,
  //                                         QStringLiteral("Carte nationale 1:25'000 | CN25"),
  //                                         QStringLiteral("ch.swisstopo.pixelkarte-farbe"),
  //                                         QStringLiteral("jpeg")
  //                                         ));
  add_layer(new QcSwissConfederationLayer(this,
                                          ++map_id, // 1
                                          1,
                                          QStringLiteral("La Suisse à pieds"),
                                          QStringLiteral("ch.astra.wanderland"),
                                          QStringLiteral("png")
                                          ));
}

QcSwissConfederationPlugin::~QcSwissConfederationPlugin()
{}

/**************************************************************************************************/

// #include "swiss_plugin.moc"
