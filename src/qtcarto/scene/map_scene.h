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

#ifndef MAP_SCENE_H
#define MAP_SCENE_H

/**************************************************************************************************/

#include "cache/file_tile_cache.h"
#include "map/decorated_path.h"
#include "map/location_circle_data.h"
#include "map/viewport.h"
#include "wmts/tile_matrix_set.h"
#include "wmts/tile_spec.h"
#include "wmts/wmts_plugin.h"

#include <QHash>
#include <QObject>
#include <QQuickWindow>
#include <QSGNode>
#include <QString>

#include <QSGClipNode>
#include <QSGFlatColorMaterial>
#include <QSGGeometry>
#include <QSGSimpleTextureNode>
#include <QSGTransformNode>
#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcMapLayerRootNode;

/**************************************************************************************************/

/// The QcMapLayerScene class implements a map layer scene.
class QcMapLayerScene : public QObject
{
  Q_OBJECT

public:
  QcMapLayerScene(const QcWmtsPluginLayer * plugin_layer, const QcViewport * viewport, QObject * parent = nullptr);
  ~QcMapLayerScene();

  QString name() const { return m_plugin_layer->hash_name(); }
  const QcWmtsPluginLayer * plugin_layer() const { return m_plugin_layer; }

  float width() { return m_viewport->width(); }
  float height() { return m_viewport->height(); }

  float opacity() const { return m_opacity; };
  void set_opacity(float opacity) { m_opacity = opacity; };

  void add_tile(const QcTileSpec & tile_spec, QSharedPointer<QcTileTexture> texture);

  void set_visible_tiles(const QcTileSpecSet & tile_specs,
                         const QcTileSpecSet & west_tile_specs,
                         const QcTileSpecSet & central_tile_specs,
                         const QcTileSpecSet & east_tile_specs);
  const QcTileSpecSet & visible_tiles() const { return m_visible_tiles; };
  QcTileSpecSet textured_tiles() const;

  QcMapLayerRootNode * make_node();
  void update_scene_graph(QcMapLayerRootNode * map_root_node, QQuickWindow * window);
  QcPolygon transform_polygon(const QcPolygon & polygon) const;
  bool build_geometry(const QcTileSpec & tile_spec, QSGGeometry::TexturedPoint2D * vertices, const QcPolygon & polygon);

  // Fixme: protected
  QcMapLayerRootNode * scene_graph_node() { return m_scene_graph_node; }

private:
  void remove_tiles(const QcTileSpecSet & old_tiles);

public:
  QHash<QcTileSpec, QSharedPointer<QcTileTexture> > m_tile_textures;

private:
  const QcWmtsPluginLayer * m_plugin_layer;
  const QcViewport * m_viewport; // Fixme: &

  const QcTileMatrixSet & m_tile_matrix_set;

  QcTileSpecSet m_visible_tiles;
  QcTileSpecSet m_west_visible_tiles;
  QcTileSpecSet m_central_visible_tiles;
  QcTileSpecSet m_east_visible_tiles;

  float m_opacity;

  QcMapLayerRootNode * m_scene_graph_node;
};

/**************************************************************************************************/

/// The QcMapScene class implements a map scene.
/// This is the top class of the map scene.
class QcMapScene : public QObject
{
  Q_OBJECT

public:
  QcMapScene(const QcViewport * viewport,
             const QcLocationCircleData & location_circle_data,
             QObject * parent = nullptr);
  ~QcMapScene();

  QSGNode * update_scene_graph(QSGNode * old_node, QQuickWindow * window);

  QcMapLayerScene * add_layer(const QcWmtsPluginLayer * plugin_layer);
  void remove_layer(const QcWmtsPluginLayer * plugin_layer);

  void update_path(const QcDecoratedPathDouble * path);
  void set_dirty_path(); // Fixme: name

private:
  float width() { return m_viewport->width(); }
  float height() { return m_viewport->height(); }

private slots:
  void set_location_circle_data_dirty();

private:
  const QcViewport * m_viewport; // Fixme: &
  QList<QcMapLayerScene *> m_layers;
  QHash<QString, QcMapLayerScene *> m_layer_map;
  QList<QSGNode *> m_scene_graph_nodes_to_remove;

  const QcDecoratedPathDouble * m_path;
  bool m_dirty_path;

  const QcLocationCircleData & m_location_circle_data;
  bool m_dirty_location_circle;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif // MAP_SCENE_H
