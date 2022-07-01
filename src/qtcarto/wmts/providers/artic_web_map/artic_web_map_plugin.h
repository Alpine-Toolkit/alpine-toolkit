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

#ifndef __QC_ARTIC_WEB_MAP_PLUGIN_H__
#define __QC_ARTIC_WEB_MAP_PLUGIN_H__

/**************************************************************************************************/

#include "wmts/wmts_plugin.h"
#include "wmts/wmts_network_tile_fetcher.h"

#include <QString>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class QcArticWebMapPlugin;

/**************************************************************************************************/

class QcArticWebMapLayer : public QcWmtsPluginLayer
{
public:
  QcArticWebMapLayer(QcArticWebMapPlugin * plugin,
                     int map_id,
                     int position,
                     const QString & title,
                     const QString & name);
  QcArticWebMapLayer(const QcArticWebMapLayer & other);
  ~QcArticWebMapLayer();

  QUrl url(const QcTileSpec & tile_spec) const;
};

/**************************************************************************************************/

class QcArticWebMapPlugin : public QcWmtsPlugin
{
  Q_OBJECT

public:
  static const QString PLUGIN_NAME;

public:
  QcArticWebMapPlugin();
  ~QcArticWebMapPlugin();
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_ARTIC_WEB_MAP_PLUGIN_H__ */
