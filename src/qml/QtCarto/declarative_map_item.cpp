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

#include "declarative_map_item.h"
#include "qtcarto.h"

#include "earth.h"
#include "coordinate/wgs84.h"

#include <cmath>

#include <QSGSimpleRectNode>
#include <QtDebug>
// #include <QtQuick/qsgnode.h>

// Fixme: Use QtQuick Private API !!!
#include <private/qquickwindow_p.h>

/**************************************************************************************************/

/*!
  \qmlproperty MapGestureArea QtLocation::Map::gesture

  Contains the MapGestureArea created with the Map. This covers pan, flick and pinch gestures.
  Use \c{gesture.enabled: true} to enable basic gestures, or see \l{MapGestureArea} for
  further details.
*/

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

/// The QcMapItem class implements a map QML Item.
QcMapItem::QcMapItem(QQuickItem * parent)
  : QQuickItem(parent),
    m_color(),
    m_gesture_area(new QcMapGestureArea(this)),
    m_plugin_manager(QcWmtsPluginManager::instance()),
    m_map_view(nullptr),
    m_viewport(nullptr)
{
  // Created when the map page is loaded (click on map item in the application menu)
  qQCDebug() << "Create QcMapItem";

  // Item will not receive any hover events through the hoverEnterEvent(), hoverMoveEvent() and hoverLeaveEvent() functions
  setAcceptHoverEvents(false);
  setAcceptedMouseButtons(Qt::LeftButton);
  setFlags(QQuickItem::ItemHasContents | QQuickItem::ItemClipsChildrenToShape);
  // Filter mouse and touch events of child items
  //   childMouseEventFilter() will be called when a mouse event is triggered for a child item.
  setFiltersChildMouseEvents(true);

  m_map_view = new QcMapView();
  m_viewport = m_map_view->viewport();

  // Fixme: direct ptr
  // Fixme: in map_view ?
  m_path_editor = new QcMapPathEditor(m_map_view);
  connect(m_path_editor, &QcMapPathEditor::path_changed, this, &QQuickItem::update);
  m_event_router.register_client(QcMapEventRouter::ClientSharedPointer(m_path_editor));

  for (const auto & plugin_name : m_plugin_manager.plugin_names())
    m_plugin_layers.insert(plugin_name, make_plugin_layers(plugin_name));

  connect(m_map_view, &QcMapView::scene_graph_changed, this, &QQuickItem::update);
  connect(location_circle_data(), &QcLocationCircleData::bearing_changed, this, &QQuickItem::update);

  // Fixme: remove
  // Set default viewport center and zoom level
  int level = 10;
  double longitude =  2.3491; // Paris Notre-Dame
  double latitude  = 48.8533;
  QcWgsCoordinate coordinate(longitude, latitude);
  m_viewport->zoom_at(coordinate, level);
}

QcMapItem::~QcMapItem()
{
  // qQCDebug();
  // delete m_plugin, m_viewport
}

void
QcMapItem::set_color(const QColor & color)
{
  if (color != m_color) {
    m_color = color;
    update();
    emit colorChanged(m_color);
  }
}

void
QcMapItem::componentComplete()
{
  // qQCDebug();
  // m_component_completed = true;
  QQuickItem::componentComplete();
}

/**************************************************************************************************/

bool
QcMapItem::is_interactive()
{
  // clang-format off
  return (
          ( m_gesture_area->enabled() and m_gesture_area->accepted_gestures() )
          or
          m_gesture_area->is_active()
          );
  // clang-format on
}

void
QcMapItem::mousePressEvent(QMouseEvent * event)
{
  // Never called when a child (MouseArea) should receive the event
  qQCDebug() << event;
  if (is_interactive())
    m_gesture_area->handle_mouse_press_event(event);
  else
    QQuickItem::mousePressEvent(event);
}

void
QcMapItem::mouseMoveEvent(QMouseEvent * event)
{
  // Called when mouse is grabbed
  qQCDebug() << event;
  if (is_interactive())
    m_gesture_area->handle_mouse_move_event(event);
  else
    QQuickItem::mouseMoveEvent(event);
}

void
QcMapItem::mouseReleaseEvent(QMouseEvent * event)
{
  // Called when mouse is grabbed
  qQCDebug() << event;
  if (is_interactive()) {
    m_gesture_area->handle_mouse_release_event(event);
    ungrabMouse();
  } else
    QQuickItem::mouseReleaseEvent(event);
}

void
QcMapItem::mouseUngrabEvent()
{
  // qQCDebug();
  if (is_interactive())
    m_gesture_area->handle_mouse_ungrab_event();
  else
    QQuickItem::mouseUngrabEvent();
}

void
QcMapItem::touchUngrabEvent()
{
  // qQCDebug();
  if (is_interactive())
    m_gesture_area->handle_touch_ungrab_event();
  else
    QQuickItem::touchUngrabEvent();
}

void
QcMapItem::touchEvent(QTouchEvent * event)
{
  qQCDebug() << event;
  if (is_interactive()) {
    m_gesture_area->handle_touch_event(event);
    if (event->type() == QEvent::TouchEnd or
        event->type() == QEvent::TouchCancel) {
      ungrabTouchPoints();
    }
  } else
    // ignore event so sythesized event is generated;
    QQuickItem::touchEvent(event);
}

void
QcMapItem::wheelEvent(QWheelEvent * event)
{
  // qQCDebug();
  on_wheel_event(event);
  event->accept();

  // if (is_interactive())
  //   m_gesture_area->handle_wheel_event(event);
  // else
  //   QQuickItem::wheelEvent(event);
}

bool
QcMapItem::childMouseEventFilter(QQuickItem * item, QEvent * event)
{
  // Return true if the specified event should not be passed onto the specified child item, and false otherwise

  QString class_name(item->metaObject()->className());
  QEvent::Type event_type = event->type();
  // Fixme: can test for QHoverEvent type ???
  bool is_hover =
    event_type == QEvent::HoverEnter ||
    event_type == QEvent::HoverLeave ||
    event_type == QEvent::HoverMove;
  if (!is_hover)
    qQCDebug() << "  Item:" << class_name << "   " << item << "\n  event:" << event;
  // Test if event comes from QQuickMouseArea_QML_80
  if (!class_name.startsWith("QQuickMouseArea")) {
      if (!is_hover)
        qQCDebug() << "  pass to item";
      return false;
  }

  if (!isVisible() or !isEnabled() or !is_interactive())
    return QQuickItem::childMouseEventFilter(item, event);

  switch (event_type) {
  case QEvent::MouseButtonPress:
  case QEvent::MouseMove:
  case QEvent::MouseButtonRelease:
    return send_mouse_event(static_cast<QMouseEvent *>(event));

  case QEvent::TouchBegin:
  case QEvent::TouchUpdate:
  case QEvent::TouchEnd:
  case QEvent::TouchCancel: {
    QTouchEvent * touch_event = static_cast<QTouchEvent *>(event);
    if (touch_event->points().count() >= 2)
      // 1 touch point = handle with MouseEvent (event is always synthesized)
      // let the synthesized mouse event grab the mouse,
      // note there is no mouse grabber at this point since
      // touch event comes first (see Qt::AA_SynthesizeMouseForUnhandledTouchEvents)
      return send_touch_event(touch_event); // Fixme: -Wimplicit-fallthrough
  }

  case QEvent::UngrabMouse: {
    QQuickWindow * _window = window();
    if (!_window and
        (( !_window->mouseGrabberItem() or
          ( _window->mouseGrabberItem() and _window->mouseGrabberItem() != this ))))
      // child lost grab, we could even lost some events
      // if grab already belongs for example in item in diffrent window,
      // clear up states
      mouseUngrabEvent();
    break;
  }

  default:
    break;
  }

  return QQuickItem::childMouseEventFilter(item, event);
}

bool
QcMapItem::send_mouse_event(QMouseEvent * event)
{
  qQCDebug() << event;

  QPointF local_position = mapFromScene(event->scenePosition()); //Qt6 ???
  QQuickWindow * _window = window();
  QQuickItem * grabber = _window ? _window->mouseGrabberItem() : nullptr;
  // Fixme: faster ? / duplicated
  bool is_mouse_area = !grabber or QString(grabber->metaObject()->className()).startsWith(QStringLiteral("QQuickMouseArea"));
  bool steal_event = m_gesture_area->is_active(); // means pan or pinch is active

  // grabber is QQuickMouseArea, steal_event is false first then true
  qQCDebug() << event << "\ngrabber" << grabber << "\nsteal_event" << steal_event << is_mouse_area;

  if (is_mouse_area and (steal_event or contains(local_position)) and (!grabber or !grabber->keepMouseGrab())) {
    /*
      // Fixme: Qt6 cloneMouseEvent
    QScopedPointer<QMouseEvent> mouseEvent(QQuickWindowPrivate::cloneMouseEvent(event, &local_position));
    mouseEvent->setAccepted(false);

    switch (mouseEvent->type()) {
    case QEvent::MouseMove:
      m_gesture_area->handle_mouse_move_event(mouseEvent.data());
      break;
    case QEvent::MouseButtonPress:
      m_gesture_area->handle_mouse_press_event(mouseEvent.data());
      break;
    case QEvent::MouseButtonRelease:
      m_gesture_area->handle_mouse_release_event(mouseEvent.data());
      break;
    default:
      break;
    }
    */

    steal_event = m_gesture_area->is_active(); // recheck value
    // Fixme: duplicated code ???
    grabber = _window ? _window->mouseGrabberItem() : nullptr;
    qQCDebug() << "grabber" << grabber << "\nsteal_event" << steal_event;

    if (grabber and steal_event and !grabber->keepMouseGrab() and grabber != this) {
      qQCDebug() << "grab mouse";
      grabMouse();
    }

    if (steal_event) {
      event->setAccepted(true);
      qQCDebug() << "don't deliver event";
      return true; // do not deliver event
    } else {
      qQCDebug() << "deliver event";
      return false; // deliver event
    }
  } else {
    // ungrab if necessary and deliver event
    if (event->type() == QEvent::MouseButtonRelease
        and (_window and _window->mouseGrabberItem() == this)) {
      qQCDebug() << "ungrab mouse";
      ungrabMouse();
    }
    qQCDebug() << "deliver event";
    return false; // deliver event
  }
}

bool
QcMapItem::send_touch_event(QTouchEvent * event)
{
  const QTouchEvent::TouchPoint & point = event->points().first();
  /* Qt6
  QQuickPointerDevice * touch_device = QQuickPointerDevice::touchDevice(event->device());
  QQuickWindowPrivate * window_private = QQuickWindowPrivate::get(window());
  auto touch_point_grabber_item = [touch_device, window_private](const QTouchEvent::TouchPoint & point) -> QQuickItem * {
    if (QQuickEventPoint * event_pointer = window_private->pointerEventInstance(touch_device)->pointById(point.id()))
      return event_pointer->grabberItem(); // Fixme: fix Qt 5.10
    return nullptr;
  };

  QQuickItem * grabber = touch_point_grabber_item(point);
  */

  QQuickItem * grabber = static_cast<QQuickItem *>(event->target());

  // Fixme: faster ?
  bool is_mouse_area = QString(grabber->metaObject()->className()).startsWith(QStringLiteral("QQuickMouseArea"));

  bool steal_event = m_gesture_area->is_active();
  bool contains_point = contains(mapFromScene(point.scenePosition()));

  if (is_mouse_area and (steal_event or contains_point) and (!grabber or !grabber->keepTouchGrab())) {
    // Qt6: QTouchEvent::QTouchEvent ctor obsolete
    QScopedPointer<QTouchEvent> touch_event(new QTouchEvent(event->type(), event->pointingDevice(), event->modifiers(),
                                                            event->touchPointStates(), event->points()));
    touch_event->setTimestamp(event->timestamp());
    touch_event->setAccepted(false);

    m_gesture_area->handle_touch_event(touch_event.data());

    steal_event = m_gesture_area->is_active(); // recheck value
    // Fixme: duplicated code ???
    //Qt6 grabber = touch_point_grabber_item(point);

    if (grabber and steal_event and !grabber->keepTouchGrab() and grabber != this) {
      QVector<int> ids;
      for (const auto & touch_point : event->points())
        if (!(touch_point.state() & Qt::TouchPointReleased))
          ids.append(touch_point.id());
      grabTouchPoints(ids);
    }

    if (steal_event) {
      // do not deliver
      event->setAccepted(true);
      return true;
    } else
      return false;

  } else {
    // ungrab if necessary and deliver event
    //old// if (event->type() == QEvent::TouchEnd
    //old//     and (_window and _window->itemForTouchPointId.value(point.id()) == this))
    //old//   ungrabTouchPoints();
    return false;
  }
}

void
QcMapItem::on_wheel_event(const QWheelEvent * event)
{
  qQCDebug() << event;

  int zoom_increment = event->angleDelta().y() > 0 ? 1 : -1;
  stable_zoom_by_increment(event->position(), zoom_increment);
}

void
QcMapItem::on_double_clicked(const QMouseEvent * event)
{
  // Fixme: improve arguments
  qQCDebug();

  int zoom_increment = 0;
  int button = event->button();
  if (button == Qt::LeftButton)
    zoom_increment = 1;
  else if (button == Qt::RightButton)
    zoom_increment = -1;
  stable_zoom_by_increment(event->pos(), zoom_increment);
}

void
QcMapItem::on_press_and_hold(const QMouseEvent * event)
{
  // Fixme: improve arguments
  qQCDebug();

  QcVectorDouble position_px(event->pos());
  QcVectorDouble projected_coordinate = to_projected_coordinate(position_px);
  QcWgsCoordinate coordinate = to_coordinate(position_px); // Fixme: from projected_coordinate but nan check
  QcMapEvent map_event = m_event_router.create_map_event(event, projected_coordinate, coordinate);
  m_event_router.handle_mouse_press_and_hold_event(map_event);
  // update();
}

void
QcMapItem::on_press_and_hold_released(const QMouseEvent * event)
{
  // Fixme: improve arguments
  qQCDebug();

  // Fixme: duplicated
  QcVectorDouble position_px(event->pos());
  QcVectorDouble projected_coordinate = to_projected_coordinate(position_px);
  QcWgsCoordinate coordinate = to_coordinate(position_px); // Fixme: from projected_coordinate but nan check
  QcMapEvent map_event = m_event_router.create_map_event(event, projected_coordinate, coordinate);
  m_event_router.handle_mouse_press_and_hold_released_event(map_event);
  // update();
}

/**************************************************************************************************/

void
QcMapItem::set_zoom_level(unsigned int new_zoom_level)
{
  qQCDebug() << new_zoom_level;

  if (new_zoom_level == zoom_level())
    return;

  // Fixme: check range
  // Fixme: int
  //   new_zoom_level < 0 is WRONG
  if (new_zoom_level < 0 or new_zoom_level > 18)
    return;

  m_viewport->set_zoom_level(new_zoom_level);
  // update(); // Fixme: signal
  emit zoom_levelChanged(new_zoom_level);
}

void
QcMapItem::set_center_qt(const QGeoCoordinate & coordinate)
{
  set_center(QcWgsCoordinate(coordinate));
}

void
QcMapItem::set_center(const QcWgsCoordinate & coordinate)
{
  // qQCDebug() << "WGS84 " << coordinate;

  if (coordinate == m_viewport->center())
    return;

  // Fixme: check latitude
  // if (!center.isValid())
  //   return;
  // coordinate.setLatitude(qBound(-m_maximumViewportLatitude, center.latitude(), m_maximumViewportLatitude));

  m_viewport->set_center(coordinate);
  // update(); // Fixme: signal

  emit centerChanged(coordinate);
}

QcWgsCoordinate
QcMapItem::center() const
{
  return m_viewport->center();
}

QGeoCoordinate
QcMapItem::center_qt() const
{
  return center().to_qt();
}

void
QcMapItem::pan(int dx, int dy)
{
  // qQCDebug() << dx << dy;
  m_viewport->pan(dx, dy); // Fixme: unit is m
  update(); // Fixme: signal
}

void
QcMapItem::stable_zoom(QPointF position_px, unsigned int new_zoom_level)
{
  qQCDebug() << position_px << zoom_level() << new_zoom_level;

  if (new_zoom_level == zoom_level())
    return;

  // Fixme: check range
  // Fixme: int
  //  new_zoom_level < 0 is WRONG
  if (new_zoom_level < 0 or new_zoom_level > 18)
    return;

  m_viewport->stable_zoom(QcVectorDouble(position_px), new_zoom_level);
  emit zoom_levelChanged(new_zoom_level);
}

void
QcMapItem::stable_zoom_by_increment(QPointF position_px, int zoom_increment)
{
  qQCDebug() << position_px << zoom_increment;
  int new_zoom_level = zoom_level() + zoom_increment;
  stable_zoom(position_px, new_zoom_level);
}

/**************************************************************************************************/

void
QcMapItem::geometryChange(const QRectF & new_geometry, const QRectF & old_geometry)
{
  // qQCDebug() << old_geometry << "->" << new_geometry;

  // Fixme: qt6
  // m_geometry_changed = true;
  // update(); // useless ???  done in supra ???
  // QQuickItem::geometryChange(new_geometry, old_geometry);

  // Derived classes must call the base class method within their implementation.
  // If the two geometries are the same, it doesn't do anything.
  QQuickItem::geometryChange(new_geometry, old_geometry);

  // Fixme: pass device pixel ratio here ?
  //   This value is dependent on the screen the window is on, and may change when the window is moved.
  //   device_pixel_ratio is unused
  auto device_pixel_ratio = window()->devicePixelRatio();
  QSize viewport_size(new_geometry.width(), new_geometry.height()); // Fixme: QSizeF size()
  m_viewport->set_viewport_size(viewport_size, device_pixel_ratio);
}

QSGNode *
QcMapItem::updatePaintNode(QSGNode * old_node, UpdatePaintNodeData *)
{
  // qQCDebug() << old_node;

  QSGSimpleRectNode * root = static_cast<QSGSimpleRectNode *>(old_node);

  // if (!m_map) {
  //   delete old_node;
  //   return nullptr;
  // }

  // Fixme: qt6
  //   done in QcMapScene::update_scene_graph()
  //   but for root child !
  // Item is empty ?
  // if (rect.isEmpty()) {
  //   delete root;
  //   return nullptr;
  // }

  // Create node
  if (!root)
    // QSGSimpleRectNode is a convenience class for drawing solid filled rectangles
    // QQuickItem::boundingRect() is undocumented
    //   -> QRectF(0, 0, d->width, d->height)
    //   https://doc.qt.io/qt-6/qquickitem.html#updatePaintNode
    root = new QSGSimpleRectNode(boundingRect(), m_color);
  else {
    // Fixme: qt6
    // if (m_geometry_changed) {
    // }
    // m_geometry_changed = false;
    root->setRect(boundingRect());
    // Fixme: here or after new ?
    root->setColor(m_color);
  }

  QSGNode * content = root->childCount() ? root->firstChild() : nullptr;
  // @map_view.h call QcMapScene::update_scene_graph()
  content = m_map_view->update_scene_graph(content, window());
  // append node if any child (content was nullptr)
  if (content and root->childCount() == 0)
    root->appendChildNode(content);

  return root;
}

/**************************************************************************************************/

/*!
  \qmlmethod coordinate QtLocation::Map::to_coordinate(QPointF position, bool clipToViewPort)

  Returns the coordinate which corresponds to the \a position relative to the map item.

  If \a cliptoViewPort is \c true, or not supplied then returns an invalid coordinate if
  \a position is not within the current viewport.
*/

QcVectorDouble
QcMapItem::to_projected_coordinate(const QcVectorDouble & position_px, bool clip_to_viewport) const
{
  return m_viewport->screen_to_projected_coordinate(position_px, clip_to_viewport);
}

QcWgsCoordinate
QcMapItem::to_coordinate(const QcVectorDouble & position_px, bool clip_to_viewport) const
{
  return m_viewport->screen_to_coordinate(position_px, clip_to_viewport);
}

QGeoCoordinate
QcMapItem::to_coordinate_qt(const QVector2D & position_px, bool clip_to_viewport) const
{
  QcVectorDouble _position_px(position_px.x(), position_px.y());
  return to_coordinate(_position_px, clip_to_viewport).to_qt();
}

/*!
    \qmlmethod point QtLocation::Map::from_coordinate(coordinate coordinate, bool clipToViewPort)

    Returns the position relative to the map item which corresponds to the \a coordinate.

    If \a cliptoViewPort is \c true, or not supplied then returns an invalid QPointF if
    \a coordinate is not within the current viewport.
*/
QcVectorDouble
QcMapItem::from_coordinate(const QcWgsCoordinate & coordinate, bool clip_to_viewport) const
{
  return m_viewport->coordinate_to_screen(coordinate, clip_to_viewport);
}

QVector2D
QcMapItem::from_coordinate_qt(const QGeoCoordinate & coordinate, bool clip_to_viewport) const
{
  QcWgsCoordinate _coordinate(coordinate);
  QcVectorDouble position_px = from_coordinate(_coordinate, clip_to_viewport);
  return QVector2D(position_px.x(), position_px.y());
}

/**************************************************************************************************/

QVariantList
QcMapItem::make_plugin_layers(const QString & plugin_name)
{
  QVariantList plugin_layers;
  const QcWmtsPlugin * plugin = m_plugin_manager[plugin_name];
  if (plugin)
    for (const auto * layer : plugin->layers()) {
      QcWmtsPluginLayerData * layer_data = new QcWmtsPluginLayerData(layer);
      connect(layer_data, &QcWmtsPluginLayerData::statusChanged, this, &QcMapItem::layer_status_changed);
      connect(layer_data, &QcWmtsPluginLayerData::opacityChanged, this, &QcMapItem::layer_opacity_changed);
      plugin_layers << QVariant::fromValue(layer_data);
    }
  return plugin_layers;
}

QVariantList
QcMapItem::plugins() const
{
  QVariantList plugins;
  const QcProjection & projection = m_viewport->projection();
  for (auto * plugin : m_plugin_manager.plugins())
    if (plugin->projection() == projection)
      plugins << QVariant::fromValue(QcWmtsPluginData(plugin->name(), plugin->title()));
  return plugins;
}

QVariantList
QcMapItem::plugin_layers(const QString & plugin_name)
{
  if (m_plugin_layers.contains(plugin_name))
    return m_plugin_layers[plugin_name];
  else
    return QVariantList();
}

void
QcMapItem::set_projection(const QcProjection * projection)
{
  m_map_view->set_projection(projection);
  update();
}

void
QcMapItem::layer_status_changed(bool status)
{
  QcWmtsPluginLayerData * layer_data = qobject_cast<QcWmtsPluginLayerData *>(QObject::sender());
  const QcWmtsPluginLayer * plugin_layer = layer_data->plugin_layer();
  if (status)
    m_map_view->add_layer(plugin_layer);
  else
    m_map_view->remove_layer(plugin_layer);
  m_gesture_area->set_zoom_level_interval(m_viewport->zoom_level_interval()); // Fixme: use signal ?
  update();
}

void
QcMapItem::layer_opacity_changed(float opacity)
{
  QcWmtsPluginLayerData * layer_data = qobject_cast<QcWmtsPluginLayerData *>(QObject::sender());
  const QcWmtsPluginLayer * plugin_layer = layer_data->plugin_layer();
  if (layer_data->status()) {
    m_map_view->set_opacity(plugin_layer, opacity);
    update();
  }
}

/**************************************************************************************************/

QString
QcMapItem::projection() const
{
  return m_viewport->projection().title();
}

QStringList
QcMapItem::projections() const
{
  QSet<QString> projections;
  for (auto * plugin : m_plugin_manager.plugins())
    // Fixme: to func
    projections.insert(plugin->projection().title());
  return QStringList(projections.begin(), projections.end());
}

/**************************************************************************************************/

void
QcMapItem::set_bearing(double bearing)
{
  m_viewport->set_bearing(bearing);
}

double
QcMapItem::bearing() const
{
  return m_viewport->bearing();
}

/*
void
QcMapItem::set_gps_horizontal_precision(double horizontal_precision)
{
  m_map_view->set_gps_horizontal_precision(horizontal_precision);
}

double
QcMapItem::gps_horizontal_precision() const
{
  return m_map_view->gps_horizontal_precision();
}
*/

QcLocationCircleData *
QcMapItem::location_circle_data()
{
  return &m_map_view->location_circle_data();
}

QcMapScale
QcMapItem::make_scale(unsigned int max_length_px) const
{
  return m_viewport->make_scale(max_length_px);
}

/**************************************************************************************************/

void
QcMapItem::prefetch_data()
{
  // qQCDebug();
}

/**************************************************************************************************/

// QC_END_NAMESPACE
