/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2022 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "swiss_topo_plugin.h"
#include "qtcarto.h"

/**************************************************************************************************/

QcSwissTopoLayer::QcSwissTopoLayer(QcSwissTopoPlugin * plugin,
                                   int map_id,
                                   int position,
                                   const QString & title,
                                   const QString & name,
                                   const QString & image_format)
  : QcWmtsPluginLayer(plugin, map_id, position, title, name, image_format)
{}

QcSwissTopoLayer::QcSwissTopoLayer(const QcSwissTopoLayer & other)
  : QcWmtsPluginLayer(other)
    // , m_style(other.m_style)
{}

QcSwissTopoLayer::~QcSwissTopoLayer()
{}

QcSwissTopoLayer &
QcSwissTopoLayer::operator=(const QcSwissTopoLayer & other)
{
  if (this != &other) {
    QcWmtsPluginLayer::operator=(other);
    // m_style = other.m_style;
  }

  return *this;
}

QUrl
QcSwissTopoLayer::url(const QcTileSpec & tile_spec) const
{
  // https://wmts.geo.admin.ch/1.0.0/ch.swisstopo.pixelkarte-farbe/default/current/3857/16/34064/23307.jpeg

  // http://wmts20.geo.admin.ch/1.0.0/' + layername + '/default/' + timestamp + '/3857/{z}/{x}/{y}.jpeg'
  // http://wmts20.geo.admin.ch/1.0.0/ch.swisstopo.pixelkarte-farbe/default/20151231/3857/15/17122/11501.jpeg
  // http://wmts20.geo.admin.ch/1.0.0/ch.swisstopo.pixelkarte-farbe/default/current/3857/10/532/361.jpeg
  // https://wmts20.geo.admin.ch/1.0.0/ch.astra.wanderland/default/20160315/21781/10/527/362.png

  return QUrl(QStringLiteral("https://wmts.geo.admin.ch/1.0.0/") +
              name()  + QLatin1Char('/') +
              QStringLiteral("default") + QLatin1Char('/') +
              QStringLiteral("current") + QLatin1Char('/') +
              QStringLiteral("3857") + QLatin1Char('/') +
              QString::number(tile_spec.level()) + QLatin1Char('/') +
              QString::number(tile_spec.x()) + QLatin1Char('/') +
              QString::number(tile_spec.y()) +
              QLatin1Char('.') + image_format());
}

/**************************************************************************************************/

const QString QcSwissTopoPlugin::PLUGIN_NAME = "swiss-topo";
const QString PLUGIN_TITLE = "Swiss Topo";
constexpr int NUMBER_OF_LEVELS = 20;
constexpr int TILE_SIZE = 256;

QcSwissTopoPlugin::QcSwissTopoPlugin()
  : QcWmtsPlugin(PLUGIN_NAME, PLUGIN_TITLE,
                 new QcMercatorTileMatrixSet(NUMBER_OF_LEVELS, TILE_SIZE))
{
  // Fixme: to json
  int map_id = -1;
  add_layer(new QcSwissTopoLayer(this,
                                 ++map_id, // 1
                                 1,
                                 QStringLiteral("Carte nationale 1:25'000 | CN25"),
                                 QStringLiteral("ch.swisstopo.pixelkarte-farbe"),
                                 QStringLiteral("jpeg")
              ));
  // add_layer(new QcSwissTopoLayer(this,
  //                                ++map_id, // 1
  //                                1,
  //                                QStringLiteral("La Suisse à pieds"),
  //                                QStringLiteral("ch.astra.wanderland"),
  //                                QStringLiteral("png")
  //             ));
}

QcSwissTopoPlugin::~QcSwissTopoPlugin()
{}

/**************************************************************************************************/

// #include "swiss_plugin.moc"
