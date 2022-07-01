/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "wmts/wmts_network_tile_fetcher.h"
#include "qtcarto.h"

#include "wmts/wmts_network_reply.h"
#include "wmts/wmts_plugin.h"

#include <QDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QcWmtsNetworkTileFetcher::QcWmtsNetworkTileFetcher(QcWmtsPlugin * plugin)
  : QcWmtsTileFetcher(),
    m_plugin(plugin)
{}

QcWmtsNetworkTileFetcher::~QcWmtsNetworkTileFetcher()
{}

QcWmtsReply *
QcWmtsNetworkTileFetcher::get_tile_image(const QcTileSpec & tile_spec)
{
  const QcWmtsPluginLayer * layer = m_plugin->layer(tile_spec);
  QUrl url = layer->url(tile_spec);
  qQCInfo() << url.toEncoded();

  QNetworkReply *reply = m_plugin->get(url);

  return new QcWmtsNetworkReply(reply, tile_spec, layer->image_format());
}

/**************************************************************************************************/

// QC_END_NAMESPACE
