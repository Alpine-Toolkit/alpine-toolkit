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

#ifndef __QC_MAP_VIEW_H__
#define __QC_MAP_VIEW_H__

/**************************************************************************************************/

#include <QList>
#include <QObject>

#include "map/location_circle_data.h"
#include "map/viewport.h"
#include "qtcarto_global.h"
#include "scene/map_scene.h"
#include "wmts/tile_spec.h"
#include "wmts/wmts_plugin.h" // circular
#include "wmts/wmts_request_manager.h" // circular

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

// class QcWmtsManager;
// class QcWmtsRequestManager;

/**************************************************************************************************/

class QcMapView;

/// The QcMapViewLayer class implements a layer in a map view.
class QC_EXPORT QcMapViewLayer : public QObject
{
  Q_OBJECT

 public:
  QcMapViewLayer(const QcWmtsPluginLayer * plugin_layer, QcViewport * m_viewport, QcMapLayerScene * layer_scene);
  ~QcMapViewLayer();

  const QcWmtsPluginLayer * plugin_layer() const { return m_plugin_layer; }
  QcWmtsPlugin * plugin() { return m_plugin_layer->plugin(); }
  int map_id() const { return m_plugin_layer->map_id(); }

  QcWmtsRequestManager * request_manager() { return m_request_manager; };

  float opacity() const;
  void set_opacity(float opacity);

  void update_tile(const QcTileSpec & tile_spec);
  void update_scene();

 signals:
  void scene_graph_changed();

 private:
  QcPolygon transform_polygon(const QcPolygon & polygon); // Fixme: const;
  QcTileSpecSet intersec_polygon_with_grid(const QcPolygon & polygon, double tile_length_m, int zoom_level);

 private:
  const QcWmtsPluginLayer * m_plugin_layer;
  QcViewport * m_viewport; /// viewport owned by QcMapView
  QcMapLayerScene * m_layer_scene; /// scene of the layer owned by QcMapScene

  QcWmtsRequestManager * m_request_manager;

  QcTileSpecSet m_west_visible_tiles;
  QcTileSpecSet m_central_visible_tiles;
  QcTileSpecSet m_east_visible_tiles;
  QcTileSpecSet m_visible_tiles;
};

// typedef QSet<QcMapViewLayer *> QcMapViewLayerSet;

/**************************************************************************************************/

/// The QcMapView class implements the business logic of the QML map item.
/// The map view holds the viewport, the layers and the scene.
class QC_EXPORT QcMapView : public QObject
{
  Q_OBJECT

 public:
  QcMapView();
  ~QcMapView();

  QcViewport * viewport() { return m_viewport; };
  const QcProjection & projection() const { return m_viewport->projection(); }
  void set_projection(const QcProjection * projection);

  void add_layer(const QcWmtsPluginLayer * plugin_layer);
  void remove_layer(const QcWmtsPluginLayer * plugin_layer);
  void remove_all_layers();
  QList<const QcWmtsPluginLayer *> layers() const;

  float opacity(const QcWmtsPluginLayer * plugin_layer);
  void set_opacity(const QcWmtsPluginLayer * plugin_layer, float opacity);

  QSGNode * update_scene_graph(QSGNode * old_node, QQuickWindow * window) {
    return m_map_scene->update_scene_graph(old_node, window);
  }

  void update_path(const QcDecoratedPathDouble * path) {
    m_map_scene->update_path(path);
  }

  QcLocationCircleData & location_circle_data() { return m_location_circle_data; }
  const QcLocationCircleData & location_circle_data() const { return m_location_circle_data; }

 signals:
  void scene_graph_changed();

 public slots:
  void update_scene();

 private:
  QcMapViewLayer * get_layer(const QcWmtsPluginLayer * plugin_layer);
  void update_zoom_level_interval();

 private:
  QcViewport * m_viewport; /// viewport of the map
  QcMapScene * m_map_scene; /// scene of the map
  QcLocationCircleData m_location_circle_data;
  QList<QcMapViewLayer *> m_layers; /// list of map layers
  QHash<QString, QcMapViewLayer *> m_layer_map; /// hash of map layers
};

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif /* __QC_MAP_VIEW_H__ */
