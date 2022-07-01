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

#ifndef __QC_ESRI_PLUGIN_H__
#define __QC_ESRI_PLUGIN_H__

/**************************************************************************************************/

#include "wmts/wmts_plugin.h"
#include "wmts/wmts_network_tile_fetcher.h"

#include <QString>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

class QcEsriPlugin;

/**************************************************************************************************/

class QcEsriLayer : public QcWmtsPluginLayer
{
public:
  QcEsriLayer(QcEsriPlugin * plugin,
              int map_id,
              int position,
              const QString & title,
              const QString & name,
              const QString & image_format,
              const QString & base);
  QcEsriLayer(const QcEsriLayer & other);
  ~QcEsriLayer();

  QcEsriLayer & operator=(const QcEsriLayer & other);

  const QString & base() const { return m_base; }

  QUrl url(const QcTileSpec & tile_spec) const;

private:
  QString m_base;
};

/**************************************************************************************************/

class QcEsriPlugin : public QcWmtsPlugin
{
  Q_OBJECT

public:
  static const QString PLUGIN_NAME;

public:
  QcEsriPlugin();
  ~QcEsriPlugin();
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_ESRI_PLUGIN_H__ */
