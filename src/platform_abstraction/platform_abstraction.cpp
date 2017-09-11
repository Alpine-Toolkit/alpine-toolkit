/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire.
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the QtCarto library.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "platform_abstraction.h"

#include <QtDebug>

/**************************************************************************************************/

PlatformAbstraction::PlatformAbstraction(QObject * parent)
  : QObject(parent),
    m_orientation_lock(false),
    m_orientation(Unspecified),
    m_full_wave_lock(false),
    m_torch_enabled(false)
{
}

PlatformAbstraction::~PlatformAbstraction()
{}

/**************************************************************************************************/

QStringList
PlatformAbstraction::need_explain() const
{
  qInfo() << "need_explain";

  return QStringList();
}

void
PlatformAbstraction::ask_permission(const QString & permission) const
{
  qInfo() << "ask_permission" << permission;
}

bool
PlatformAbstraction::is_permission_granted(const QString & permission) const
{
  qInfo() << "is_permission_granted" << permission;

  return true;
}

bool
PlatformAbstraction::is_permission_denied(const QString & permission) const
{
  qInfo() << "is_permission_denied" << permission;

  return false;
}

/**************************************************************************************************/

void
PlatformAbstraction::set_orientation_lock(bool orientation_lock)
{
  qInfo() << "set_orientation_lock" << orientation_lock;

  if (m_orientation_lock != orientation_lock) {
     m_orientation_lock = orientation_lock;
     emit orientation_lockChanged();
  }
}

bool
PlatformAbstraction::orientation_lock() const
{
  return m_orientation_lock;
}

/*
void
PlatformAbstraction::update_orientation_lock()
{
  if (m_orientation_lock)
    ;
  else
    ;
}
*/

/**************************************************************************************************/

void
PlatformAbstraction::set_orientation(PlatformAbstraction::ScreenOrientation orientation)
{
  qInfo() << "set_orientation" << orientation;

  if (m_orientation != orientation) {
    m_orientation = orientation;
    emit orientationChanged();
  }
}

PlatformAbstraction::ScreenOrientation
PlatformAbstraction::orientation() const
{
  return m_orientation;
}

/*
void
PlatformAbstraction::update_orientation()
{
  switch (m_orientation) {
  case Portrait:
    ;
  case Landscape:
    ;
  case Sensor:
  default:
    ;
  }
}
*/

/**************************************************************************************************/

void
PlatformAbstraction::set_full_wave_lock(bool full_wave_lock)
{
  qInfo() << "set_full_wave_lock" << full_wave_lock;

  if (m_full_wave_lock != full_wave_lock) {
    m_full_wave_lock = full_wave_lock;
    emit full_wave_lockChanged();
  }
}

bool
PlatformAbstraction::full_wave_lock() const
{
  return m_full_wave_lock;
}

/*
void
PlatformAbstraction::update_full_wave_lock()
{
  if (m_full_wave_lock)
    ;
  else
    ;
}
*/

/**************************************************************************************************/

void
PlatformAbstraction::set_torch(bool enabled)
{
  qInfo() << "set_torch" << enabled;

  if (m_torch_enabled != enabled) {
    m_torch_enabled = enabled;
    emit torchChanged();
  }
}

bool
PlatformAbstraction::torch() const
{
  return m_torch_enabled;
}

/*
void
PlatformAbstraction::update_torch()
{
}
*/

/**************************************************************************************************/

void
PlatformAbstraction::issue_call(const QString & phone_number) const
{
  qInfo() << "issue_call" << phone_number;
}

void
PlatformAbstraction::issue_dial(const QString & phone_number) const
{
  qInfo() << "issue_dial" << phone_number;
}

/**************************************************************************************************/

void
PlatformAbstraction::perform_lamp_signal(const QString & message, int rate_ms) const
{
  qInfo() << "perform_lamp_signal" << message << rate_ms;
}

void
PlatformAbstraction::stop_lamp_signal() const
{
  qInfo() << "stop_lamp_signal";
}

void
PlatformAbstraction::start_lamp_dimmer(int period, int duty_cycle) const
{
  qInfo() << "start_lamp_dimmer" << period << duty_cycle;
}

void
PlatformAbstraction::stop_lamp_dimmer() const
{
  qInfo() << "stop_lamp_dimmer";
}
