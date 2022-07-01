// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __QC_WMTS_NETWORK_TILE_FETCHER_H__
#define __QC_WMTS_NETWORK_TILE_FETCHER_H__

/**************************************************************************************************/

#include "wmts/wmts_tile_fetcher.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class QcWmtsPlugin; // circular

/**************************************************************************************************/

// Fixme: QcWmtsTileFetcher isn't networking aware, excepted QcWmtsReply relies on QNetworkReply

class QcWmtsNetworkTileFetcher : public QcWmtsTileFetcher
{
  Q_OBJECT

public:
  QcWmtsNetworkTileFetcher(QcWmtsPlugin * plugin);
  ~QcWmtsNetworkTileFetcher();

private:
  QcWmtsReply * get_tile_image(const QcTileSpec & tile_spec);

private:
  QcWmtsPlugin * m_plugin;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_WMTS_NETWORK_TILE_FETCHER_H__ */
