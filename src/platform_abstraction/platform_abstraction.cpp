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
    m_torch_enabled(false),
    m_morse_code_engine(nullptr)
{
}

PlatformAbstraction::~PlatformAbstraction()
{
  if (m_morse_code_engine)
    delete m_morse_code_engine;
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
PlatformAbstraction::issue_call(const QString & phone_number)
{
  qInfo() << "issue_call" << phone_number;
}

void
PlatformAbstraction::issue_dial(const QString & phone_number)
{
  qInfo() << "issue_dial" << phone_number;
}

/**************************************************************************************************/

void
PlatformAbstraction::load_morse_code_engine()
{
  if (!m_morse_code_engine)
    m_morse_code_engine = new InternationalMorseCodeEngine();
}

void
PlatformAbstraction::perform_lamp_signal(const QString & message, int rate_ms)
{
  load_morse_code_engine();
  QString encoded_message = m_morse_code_engine->encode(message, true, true);
  qInfo() << "perform_lamp_signal" << message << encoded_message;
  impl_perform_lamp_signal(encoded_message, rate_ms);
}

QString
PlatformAbstraction::encode_morse(const QString & message)
{
  load_morse_code_engine();
  return m_morse_code_engine->encode(message);
}

QString
PlatformAbstraction::decode_morse(const QString & encoded_message)
{
  load_morse_code_engine();
  return m_morse_code_engine->decode(encoded_message);
}
