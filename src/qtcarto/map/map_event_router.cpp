/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2016 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

#include "map_event_router.h"
#include "qtcarto.h"

#include<QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

/**************************************************************************************************/

QcMapEvent::QcMapEvent()
  : m_button(),
    m_buttons(),
    m_modifiers(),
    m_projected_coordinate(),
    m_coordinate()
{}

QcMapEvent::QcMapEvent(int button, int buttons, int modifiers,
                       const QcVectorDouble & projected_coordinate,
                       const QcWgsCoordinate & coordinate)
  : m_button(button),
    m_buttons(buttons),
    m_modifiers(modifiers),
    m_projected_coordinate(projected_coordinate),
    m_coordinate(coordinate)
{}

QcMapEvent::QcMapEvent(const QcMapEvent & other)
  : m_button(other.m_button),
    m_buttons(other.m_buttons),
    m_modifiers(other.m_modifiers),
    m_projected_coordinate(other.m_projected_coordinate),
    m_coordinate(other.m_coordinate)
{}

QcMapEvent::~QcMapEvent()
{}

QcMapEvent &
QcMapEvent::operator=(const QcMapEvent & other)
{
  if (this != &other) {
    m_button = other.m_button;
    m_buttons = other.m_buttons;
    m_modifiers = other.m_modifiers;
    m_projected_coordinate = other.m_projected_coordinate;
    m_coordinate = other.m_coordinate;
  }

  return *this;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug
operator<<(QDebug debug, const QcMapEvent & map_event)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "QcMapEvent(";
    debug << map_event.button();
    debug << ',';
    debug << map_event.buttons();
    debug << ',';
    debug << map_event.modifiers();
    debug << ',';
    debug << map_event.projected_coordinate();
    debug << ')';
    debug << map_event.coordinate();
    debug << ')';

    return debug;
}
#endif

/**************************************************************************************************/

QcMapEventClient::QcMapEventClient(const QString & name)
  : QObject(),
    m_name(name)
{}

QcMapEventClient::~QcMapEventClient()
{}

/**************************************************************************************************/

QcMapEventRouter::QcMapEventRouter()
  : QObject()
{
}

QcMapEventRouter::~QcMapEventRouter()
{
}

QcMapEvent
QcMapEventRouter::create_map_event(const QMouseEvent * event,
                                   const QcVectorDouble & projected_coordinate,
                                   const QcWgsCoordinate & coordinate)
{
  return QcMapEvent(event->button(), event->buttons(), event->modifiers(),
                    projected_coordinate, coordinate);
}

void
QcMapEventRouter::handle_mouse_press_event(const QcMapEvent & event)
{
  if (!m_current_client)
    m_current_client->handle_mouse_press_event(event);
}

void
QcMapEventRouter::handle_mouse_move_event(const QcMapEvent & event)
{
  if (!m_current_client)
    m_current_client->handle_mouse_move_event(event);
}

void
QcMapEventRouter::handle_mouse_release_event(const QcMapEvent & event)
{
  if (!m_current_client)
    m_current_client->handle_mouse_release_event(event);
}

void
QcMapEventRouter::handle_mouse_wheel_event(const QcMapEvent & event)
{
  if (!m_current_client)
    m_current_client->handle_mouse_wheel_event(event);
}

void
QcMapEventRouter::handle_mouse_press_and_hold_event(const QcMapEvent & event)
{
  qQCInfo() << event;
  if (!m_current_client.isNull())
    m_current_client->handle_mouse_press_and_hold_event(event);
}

void
QcMapEventRouter::handle_mouse_press_and_hold_released_event(const QcMapEvent & event)
{
  qQCInfo() << event;
  if (!m_current_client.isNull())
    m_current_client->handle_mouse_press_and_hold_released_event(event);
}

void
QcMapEventRouter::handle_clicked_event(const QcMapEvent & event)
{
  if (!m_current_client)
    m_current_client->handle_clicked_event(event);
}

void
QcMapEventRouter::handle_double_clicked_event(const QcMapEvent & event)
{
  if (!m_current_client)
    m_current_client->handle_double_clicked_event(event);
}

void
QcMapEventRouter::register_client(ClientSharedPointer client)
{
  m_clients.insert(client->name(), client);
}

void
QcMapEventRouter::unregister_client(const QString & name)
{
  // Fixme: in stack
  m_clients.remove(name);
}

void
QcMapEventRouter::push_client(const QString & name)
{
  if (m_clients.contains(name)) {
    qQCInfo() << "push" << name;
    m_current_client = m_clients.value(name);
    // m_current_client.data()
    // m_client_stack.insert());
  }
  // Fixme: else
}

void
QcMapEventRouter::pop_client()
{
  if (m_client_stack.size()) {
    m_client_stack.removeLast();
    // qQCInfo() << "pop" << name;
    if (m_client_stack.size())
      m_current_client = m_client_stack.last();
    else
      m_current_client = ClientSharedPointer(nullptr);
  }
}

/**************************************************************************************************/

// QC_END_NAMESPACE
