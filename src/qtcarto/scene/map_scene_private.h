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

#ifndef MAP_SCENE_PRIVATE_H
#define MAP_SCENE_PRIVATE_H

/**************************************************************************************************/

#include "location_circle_node.h"
#include "path_node.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcMapSideNode : public QSGTransformNode
{
public:
  void add_child(const QcTileSpec & tile_spec, QSGSimpleTextureNode * node);

  QHash<QcTileSpec, QSGSimpleTextureNode *> texture_nodes;
};

/**************************************************************************************************/

class QcMapLayerRootNode : public QSGOpacityNode
{
public:
  QcMapLayerRootNode(const QcTileMatrixSet & tile_matrix_set, const QcViewport * viewport);
  ~QcMapLayerRootNode();

  void update_central_maps();
  void update_tiles(QcMapLayerScene * map_scene,
                    QcMapSideNode * map_side_node, const QcTileSpecSet & visible_tiles, const QcPolygon & polygon,
                    const QcViewportPart & part);

private:
  const QcTileMatrixSet & m_tile_matrix_set;
  const QcViewport * m_viewport;

public:
  // QcGridNode * grid_node;
  QcMapSideNode * west_map_node;
  QcMapSideNode * central_map_node;
  QcMapSideNode * east_map_node;
  QList<QcMapSideNode *> central_map_nodes;
  QHash<QcTileSpec, QSGTexture *> textures;
};

/**************************************************************************************************/

/// The QcMapRootNode class is the top level node of the map scene
class QcMapRootNode : public QSGClipNode
{
public:
  QcMapRootNode(const QcViewport * viewport);
  ~QcMapRootNode();

  void update_clip_rect();

private:
  const QcViewport * m_viewport;
  QRect m_clip_rect;

public:
  QSGGeometry geometry;
  QSGTransformNode * root;
  QcLocationCircleNode * location_circle_node;
  QcPathNode * path_node;
  QHash<QString, QcMapLayerRootNode *> layers;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif // MAP_SCENE_PRIVATE_H
