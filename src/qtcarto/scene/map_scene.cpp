/***************************************************************************************************
 **
 ** $QTCARTO_BEGIN_LICENSE:GPL3$
 **
 ** Copyright (C) 2016 Fabrice Salvaire
 ** Contact: http://www.fabrice-salvaire.fr
 **
 ** This file is part of the Alpine Toolkit software.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 ** $QTCARTO_END_LICENSE$
 **
 ***************************************************************************************************/

/**************************************************************************************************/

#include "map_scene.h"
#include "map_scene_private.h"
#include "qtcarto.h"

#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

/// Constructs a QcMapScene
QcMapScene::QcMapScene(const QcViewport * viewport,
                       const QcLocationCircleData & location_circle_data,
                       QObject * parent)
  : QObject(parent),
    m_viewport(viewport),
    m_layers(),
    m_layer_map(),
    m_scene_graph_nodes_to_remove(),
    m_path(nullptr),
    m_dirty_path(false),
    m_location_circle_data(location_circle_data),
    m_dirty_location_circle(false)
{
  qQCDebug();

  // Connect signals
  // connect(&m_location_circle_data, QcLocationCircleData::horizontal_precisionChanged,
  //         this, QcMapScene::set_location_circle_data_dirty);
  connect(&m_location_circle_data, &QcLocationCircleData::visible_changed,
          this, &QcMapScene::set_location_circle_data_dirty);
  connect(&m_location_circle_data, &QcLocationCircleData::coordinate_changed,
          this, &QcMapScene::set_location_circle_data_dirty);
  connect(&m_location_circle_data, &QcLocationCircleData::horizontal_precision_changed,
          this, &QcMapScene::set_location_circle_data_dirty);
  connect(&m_location_circle_data, &QcLocationCircleData::bearing_changed,
          this, &QcMapScene::set_location_circle_data_dirty);
}

QcMapScene::~QcMapScene()
{}

/// Add a plugin layer to the scene.
QcMapLayerScene *
QcMapScene::add_layer(const QcWmtsPluginLayer * plugin_layer)
{
  qQCDebug();

  QcMapLayerScene * layer = new QcMapLayerScene(plugin_layer, m_viewport);
  m_layers << layer;
  m_layer_map.insert(plugin_layer->hash_name(), layer);
  return layer;
}

/// Remove a plugin layer to the scene.
void
QcMapScene::remove_layer(const QcWmtsPluginLayer * plugin_layer)
{
  qQCDebug();

  QString name = plugin_layer->hash_name();
  if (m_layer_map.contains(name)) {
    QcMapLayerScene * layer = m_layer_map[name];
    m_layers.removeOne(layer);
    m_layer_map.remove(name);
    m_scene_graph_nodes_to_remove << layer->scene_graph_node();
    layer->deleteLater();
  }
}

void
QcMapScene::update_path(const QcDecoratedPathDouble * path) {
  qQCDebug();

  m_path = path;
  m_dirty_path = true;
}

void
QcMapScene::set_dirty_path()
{
  qQCDebug();
  m_dirty_path = true;
}

void
QcMapScene::set_location_circle_data_dirty()
{
  qQCDebug();
  m_dirty_location_circle = true;
}

/// Update the scene graph.
/// This is the top method to build the scene from the QML item, it must be called in
/// \ref QcMapItem::updatePaintNode(QSGNode *, UpdatePaintNodeData *) via a call to
/// \ref QcMapView::update_scene_graph(QSGNode *, QQuickWindow *).
QSGNode *
QcMapScene::update_scene_graph(QSGNode * old_node, QQuickWindow * window)
{
  qQCDebug() << old_node;

  // QSize viewport_size = m_viewport->viewport_size();
  // qQCDebug() << "viewport size" << viewport_size;

  // Fixme: qt6 looks wrong
  // Check viewport has a rectangular shape
  float width = m_viewport->width();
  float height = m_viewport->height();
  if (width <= 0 || height <= 0) {
    delete old_node;
    return nullptr;
  }

  auto map_root_node = static_cast<QcMapRootNode *>(old_node);
  if (!map_root_node) {
    // qQCDebug() << "map_root_node is null";
    map_root_node = new QcMapRootNode(m_viewport);
  }

  // Fixme: ok ?
  map_root_node->update_clip_rect();

  // Fixme: useless, set matrix to identity ???
  /* Reset matrix to physical pixel
   * | 2S/W   0     -1 |
   * |  0    2S/H   -1 |
   */
  QMatrix4x4 item_space_matrix;
  // qreal device_pixel_ratio_inverse = 1.; // / window->devicePixelRatio();
  // item_space_matrix.scale(device_pixel_ratio_inverse, device_pixel_ratio_inverse);
  // root is QSGTransformNode
  map_root_node->root->setMatrix(item_space_matrix);
  qQCDebug() << "item_space_matrix" << item_space_matrix;

  // Remove disabled layers
  for (auto * node : m_scene_graph_nodes_to_remove)
    map_root_node->root->removeChildNode(node);
  m_scene_graph_nodes_to_remove.clear();

  // update map layers
  for (auto * layer : m_layers) {
    QcMapLayerRootNode * layer_node = nullptr;
    QString name = layer->name();
    if (map_root_node->layers.contains(name))
      layer_node = map_root_node->layers[name];
    else {
      layer_node = layer->make_node();
      map_root_node->layers.insert(name, layer_node);
      map_root_node->root->insertChildNodeBefore(layer_node, map_root_node->location_circle_node);
    }
    layer->update_scene_graph(layer_node, window);
  }

  // Update path
  if (m_dirty_path) {
    // Fixme: m_path is null
    map_root_node->path_node->update(m_path);
    m_dirty_path = false;
  }

  // Update location circle
  if (m_dirty_location_circle) {
    qQCDebug() << "Location circle is dirty";
    map_root_node->location_circle_node->update(m_location_circle_data);
    m_dirty_location_circle = false;
  }

  // Fixme: map_root_node->grid_node->update();

  return map_root_node;
}

/**************************************************************************************************/

/// Constructs a QcMapRootNode instance
QcMapRootNode::QcMapRootNode(const QcViewport * viewport)
  : m_viewport(viewport),
    geometry(QSGGeometry::defaultAttributes_Point2D(), 4),
    root(new QSGTransformNode()),
    location_circle_node(new QcLocationCircleNode(viewport)),
    path_node(new QcPathNode(viewport))
{
  qQCDebug();

  // https://doc.qt.io/qt-6/qsgclipnode.html#setClipRect
  // This is an optimization hint which means that the renderer
  // can use scissoring instead of stencil, which is significantly faster.
  setIsRectangular(true);
  setGeometry(&geometry);

  appendChildNode(root);
  root->appendChildNode(location_circle_node);
  root->appendChildNode(path_node);
}

QcMapRootNode::~QcMapRootNode()
{}

void
QcMapRootNode::update_clip_rect()
{
  // Fixme: func
  int width = m_viewport->width();
  int height = m_viewport->height();
  QRect rect = QRect(0, 0, width, height);
  qQCDebug() << "clip rect" << rect;
  if (rect != m_clip_rect) {
    QSGGeometry::updateRectGeometry(&geometry, rect);
    QSGClipNode::setClipRect(rect);
    m_clip_rect = rect;
    markDirty(DirtyGeometry);
  }
}

/**************************************************************************************************/

// #include "map_scene.moc"

// QC_END_NAMESPACE
