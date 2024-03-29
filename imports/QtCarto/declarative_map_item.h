// -*- mode: c++ -*-

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

#ifndef DECLARATIVE_MAP_ITEM_H
#define DECLARATIVE_MAP_ITEM_H

/**************************************************************************************************/

#include "map_gesture_area.h"
#include "plugin_data.h"

#include "map/map_event_router.h"
#include "map/map_path_editor.h"
#include "map/map_view.h"
#include "map/viewport.h"
#include "wmts/wmts_plugin_manager.h"

#include <QColor>
#include <QGeoCoordinate>
#include <QHash>
#include <QQuickItem>
#include <QTouchEvent>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcMapItem : public QQuickItem
{
  Q_OBJECT
  Q_INTERFACES(QQmlParserStatus)
  Q_PROPERTY(QColor color READ color WRITE set_color NOTIFY colorChanged)
  Q_PROPERTY(QcMapGestureArea * gesture READ gesture CONSTANT)
  Q_PROPERTY(unsigned int zoom_level READ zoom_level WRITE set_zoom_level NOTIFY zoom_levelChanged)
  Q_PROPERTY(QcWgsCoordinate center READ center WRITE set_center NOTIFY centerChanged)
  Q_PROPERTY(double bearing READ bearing WRITE set_bearing NOTIFY bearingChanged)
  Q_PROPERTY(QcLocationCircleData * location_circle_data READ location_circle_data CONSTANT)
  Q_PROPERTY(QVariantList plugins READ plugins CONSTANT)
  Q_PROPERTY(QString projection READ projection CONSTANT)
  Q_PROPERTY(QStringList projections READ projections CONSTANT)
  Q_PROPERTY(QcMapEventRouter * event_router READ event_router CONSTANT)
  Q_PROPERTY(QcMapPathEditor * path_editor READ path_editor CONSTANT)

public:
  Q_INVOKABLE static QcWgsCoordinate cast_QGeoCoordinate(const QGeoCoordinate & coordinate) {
    return QcWgsCoordinate(coordinate);
  }

  Q_INVOKABLE static QcVectorDouble cast_QVector2D(const QVector2D & vector) {
    return QcVectorDouble(vector.x(), vector.y());
  }

  Q_INVOKABLE static QcVectorDouble cast_QPointF(const QPointF & vector) {
    return QcVectorDouble(vector.x(), vector.y());
  }

public:
  QcMapItem(QQuickItem *parent = 0);
  ~QcMapItem();

  QcMapGestureArea * gesture() { return m_gesture_area; }

  void set_color(const QColor & color);
  QColor color() const { return m_color; }

  void set_zoom_level(unsigned int zoom_level);
  unsigned int zoom_level() const { return m_viewport->zoom_level(); }

  void set_center(const QcWgsCoordinate & center);
  QcWgsCoordinate center() const;

  Q_INVOKABLE QGeoCoordinate center_qt() const;
  Q_INVOKABLE void set_center_qt(const QGeoCoordinate & center);

  void set_bearing(double bearing);
  double bearing() const;

  QcLocationCircleData * location_circle_data();
  QcMapPathEditor * path_editor() { return m_path_editor; }

  Q_INVOKABLE QcMapScale make_scale(unsigned int max_length_px) const;

  // Fixme: QVector2D use float ...
  Q_INVOKABLE QcVectorDouble to_projected_coordinate(const QcVectorDouble & position_px, bool clip_to_viewport = true) const;
  Q_INVOKABLE QcWgsCoordinate to_coordinate(const QcVectorDouble & position, bool clip_to_viewport = true) const;
  Q_INVOKABLE QcWgsCoordinate to_coordinate(const QPointF & position, bool clip_to_viewport = true) const {
    return to_coordinate(QcVectorDouble(position), clip_to_viewport);
  }
  Q_INVOKABLE QcVectorDouble from_coordinate(const QcWgsCoordinate & coordinate, bool clip_to_viewport = true) const;
  Q_INVOKABLE QGeoCoordinate to_coordinate_qt(const QVector2D & position, bool clip_to_viewport = true) const;
  Q_INVOKABLE QVector2D from_coordinate_qt(const QGeoCoordinate & coordinate, bool clip_to_viewport = true) const;

  Q_INVOKABLE void pan(int dx, int dy);
  Q_INVOKABLE void stable_zoom(QPointF position_px, unsigned int zoom_level);
  Q_INVOKABLE void stable_zoom_by_increment(QPointF position_px, int zoom_increment);

  Q_INVOKABLE void prefetch_data(); // optional hint for prefetch

  QVariantList plugins() const;
  Q_INVOKABLE QVariantList plugin_layers(const QString & plugin_name);

  QString projection() const;
  QStringList projections() const;
  void set_projection(const QcProjection * projection);

  QcMapEventRouter * event_router() { return &m_event_router; }

  bool childMouseEventFilter(QQuickItem * item, QEvent * event) Q_DECL_OVERRIDE ;

  // called from map gesture area
  void on_wheel_event(const QWheelEvent * event);
  void on_press_and_hold(const QMouseEvent * event);
  void on_press_and_hold_released(const QMouseEvent * event);
  void on_double_clicked(const QMouseEvent * event);

signals:
  void colorChanged(const QColor & color);
  void zoom_levelChanged(int zoom_level);
  void centerChanged(const QcWgsCoordinate & coordinate);
  void bearingChanged(double bearing);
  void gps_horizontal_precisionChanged(double horizontal_precision);

protected:
  void mouseMoveEvent(QMouseEvent * event) Q_DECL_OVERRIDE ;
  void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE ;
  void mouseReleaseEvent(QMouseEvent * event) Q_DECL_OVERRIDE ;
  void mouseUngrabEvent() Q_DECL_OVERRIDE ;
  void touchEvent(QTouchEvent * event) Q_DECL_OVERRIDE ;
  void touchUngrabEvent() Q_DECL_OVERRIDE;
  void wheelEvent(QWheelEvent * event) Q_DECL_OVERRIDE ;

  /* bool sendMouseEvent(QMouseEvent *event); */
  /* bool sendTouchEvent(QTouchEvent *event); */

  void componentComplete() Q_DECL_OVERRIDE ;
  void geometryChanged(const QRectF & new_geometry, const QRectF & old_geometry) Q_DECL_OVERRIDE ;
  QSGNode * updatePaintNode(QSGNode * old_node, UpdatePaintNodeData *) Q_DECL_OVERRIDE ;

private slots:
  void layer_status_changed(bool status);
  void layer_opacity_changed(float opacity);

private:
  bool is_interactive();
  bool send_touch_event(QTouchEvent * event);
  bool send_mouse_event(QMouseEvent * event);
  QVariantList make_plugin_layers(const QString & plugin);

private:
  QColor m_color;
  QcMapGestureArea * m_gesture_area;
  QcWmtsPluginManager & m_plugin_manager;
  QcMapPathEditor * m_path_editor;
  QcMapEventRouter m_event_router;
  QcMapView * m_map_view;
  QcViewport * m_viewport; // ???
  QHash<QString, QVariantList> m_plugin_layers;
};

// QC_END_NAMESPACE

/**************************************************************************************************/

#endif // DECLARATIVE_MAP_ITEM_H
