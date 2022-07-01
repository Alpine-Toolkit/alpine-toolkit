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

#ifndef __QC_SWISS_CONFEDERATION_PLUGIN_H__
#define __QC_SWISS_CONFEDERATION_PLUGIN_H__

/**************************************************************************************************/

#include "wmts/wmts_plugin.h"
#include "wmts/wmts_network_tile_fetcher.h"

#include <QString>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class QcSwissConfederationPlugin;

/**************************************************************************************************/

class QcSwissConfederationLayer : public QcWmtsPluginLayer
{
public:
  QcSwissConfederationLayer(QcSwissConfederationPlugin * plugin,
                              int map_id,
                              int position,
                              const QString & title,
                              const QString & name,
                              const QString & image_format);

  QUrl url(const QcTileSpec & tile_spec) const override;
};

/**************************************************************************************************/

class QcSwissConfederationPlugin : public QcWmtsPlugin
{
  Q_OBJECT

public:
  static const QString PLUGIN_NAME;

public:
  QcSwissConfederationPlugin();
  ~QcSwissConfederationPlugin();
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_SWISS_CONFEDERATION_PLUGIN_H__ */
