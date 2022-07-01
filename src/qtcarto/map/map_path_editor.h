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

#ifndef __QC_MAP_PATH_EDITOR_H__
#define __QC_MAP_PATH_EDITOR_H__

/**************************************************************************************************/

#include "geometry/path.h"
#include "map/decorated_path.h"
#include "map/map_event_router.h"
#include "map/map_view.h"
#include "map/path_property.h"

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

class QcMapPathEditor : public QcMapEventClient
{
  Q_OBJECT
  Q_PROPERTY(QcPathProperty * path_property READ path_property_ptr CONSTANT)

public:
  QcMapPathEditor(QcMapView * map_view);
  ~QcMapPathEditor();

  // void handle_mouse_press_event(const QcMapEvent & event) override;
  void handle_mouse_move_event(const QcMapEvent & event) override;
  // void handle_mouse_release_event(const QcMapEvent & event) override;
  // void handle_mouse_wheel_event(const QcMapEvent & event) override;

  void handle_mouse_press_and_hold_event(const QcMapEvent & event) override;
  void handle_mouse_press_and_hold_released_event(const QcMapEvent & event) override;

  // void handle_clicked_event(const QcMapEvent & event) override;
  // void handle_double_clicked_event(const QcMapEvent & event) override;

  Q_INVOKABLE void clear();
  Q_INVOKABLE void set_closed(bool value);
  Q_INVOKABLE void set_vertex_edition_mode(bool value);

  QcDecoratedPathDouble path() const { return m_path; }
  void set_path(const QcPathDouble & path) { m_path = path ;}

  QcPathProperty path_property() const { return m_path_property; }

signals:
  void path_changed();

private:
  void update_path();
  QcPathProperty * path_property_ptr() { return &m_path_property; } // const

private:
  QcDecoratedPathDouble m_path;
  QcPathProperty m_path_property;
  QcMapView * m_map_view;
  bool m_vertex_edition_mode = false;
  int m_selected_vertex_index = -1;
};

/**************************************************************************************************/

// QC_END_NAMESPACE

// Q_DECLARE_METATYPE(QcMapPathEditor)

/**************************************************************************************************/

#endif /* __QC_MAP_PATH_EDITOR_H__ */
