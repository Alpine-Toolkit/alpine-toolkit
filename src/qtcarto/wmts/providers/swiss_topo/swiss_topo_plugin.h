// -*- mode: c++ -*-

/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2022 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#ifndef __QC_SWISS_TOPO_PLUGIN_H__
#define __QC_SWISS_TOPO_PLUGIN_H__

/**************************************************************************************************/

#include "wmts/wmts_plugin.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class QcSwissTopoPlugin;

/**************************************************************************************************/

class QcSwissTopoLayer : public QcWmtsPluginLayer
{
public:
  QcSwissTopoLayer(QcSwissTopoPlugin * plugin,
                   int map_id,
                   int position,
                   const QString & title,
                   const QString & name,
                   const QString & image_format);
  // const QString & style
  QcSwissTopoLayer(const QcSwissTopoLayer & other);
  ~QcSwissTopoLayer();

  QcSwissTopoLayer & operator=(const QcSwissTopoLayer & other);

  // const QString & style() const { return m_style; }

  QUrl url(const QcTileSpec & tile_spec) const override;

private:
  // QString m_style;
};

/**************************************************************************************************/

class QcSwissTopoPlugin : public QcWmtsPlugin
{
  Q_OBJECT

public:
  static const QString PLUGIN_NAME;

public:
  QcSwissTopoPlugin();
  ~QcSwissTopoPlugin();

  bool has_location_service() override { return false; }

  bool has_coordinate_elevation_service() override { return false; }
  bool has_sampling_elevation_service() override { return false; }
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_SWISS_TOPO_PLUGIN_H__ */
