/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "esri_plugin.h"
#include "qtcarto.h"

#include <QUrlQuery>

/**************************************************************************************************/

QcEsriLayer::QcEsriLayer(QcEsriPlugin * plugin,
                         int map_id,
                         int position,
                         const QString & title,
                         const QString & name,
                         const QString & image_format,
                         const QString & base)
  : QcWmtsPluginLayer(plugin, map_id, position, title, name, image_format),
    m_base(base)
{}

QcEsriLayer::QcEsriLayer(const QcEsriLayer & other)
  : QcWmtsPluginLayer(other),
    m_base(other.m_base)
{}

QcEsriLayer::~QcEsriLayer()
{}

QcEsriLayer &
QcEsriLayer::operator=(const QcEsriLayer & other)
{
  if (this != &other) {
    QcWmtsPluginLayer::operator=(other);
    m_base = other.m_base;
  }

  return *this;
}

QUrl
QcEsriLayer::url(const QcTileSpec & tile_spec) const
{
  QUrlQuery url_query(QStringLiteral("layer=World_Topo_Map&style=default&tilematrixset=GoogleMapsCompatible&Service=WMTS&Request=GetTile&Version=1.0.0&Format=image/jpeg"));
  url_query.addQueryItem(QStringLiteral("TileMatrix"), QString::number(tile_spec.level()));
  url_query.addQueryItem(QStringLiteral("TileCol"), QString::number(tile_spec.x()));
  url_query.addQueryItem(QStringLiteral("TileRow"), QString::number(tile_spec.y()));
  QUrl url(QStringLiteral("https://") + m_base);
  // url.setScheme('https');
  url.setQuery(url_query);
  return url;
}

/**************************************************************************************************/

const QString QcEsriPlugin::PLUGIN_NAME = "esri";
const QString PLUGIN_TITLE = "Esri";
constexpr int NUMBER_OF_LEVELS = 20;
constexpr int TILE_SIZE = 256;

QcEsriPlugin::QcEsriPlugin()
  : QcWmtsPlugin(PLUGIN_NAME, PLUGIN_TITLE,
                 new QcMercatorTileMatrixSet(NUMBER_OF_LEVELS, TILE_SIZE))
{
  int map_id = -1;
  add_layer(new QcEsriLayer(this,
                            ++map_id, // 1
                            1,
                            QStringLiteral("World Topo Map"),
                            QStringLiteral("wolrd_topo_map"),
                            QStringLiteral("jpeg"), // Fixme
                            QStringLiteral("server.arcgisonline.com/arcgis/rest/services/World_Topo_Map/MapServer/WMTS")
                            ));
}

QcEsriPlugin::~QcEsriPlugin()
{}

/**************************************************************************************************/

// #include "esri_plugin.moc"
