/***************************************************************************************************
 *
 * $QTCARTO_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2016 Fabrice Salvaire.
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
 * $QTCARTO_END_LICENSE$
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "android_activity.h"

#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroid>
#include <QtDebug>

/**************************************************************************************************/

AndroidActivity::AndroidActivity(QObject *parent)
  : QObject(parent),
    m_orientation_lock(false),
    m_orientation(Unspecified),
    m_full_wave_lock(false),
    m_torch_enabled(false),
    m_morse_code_engine(nullptr)
{
  connect(this, SIGNAL(orientation_lockChanged()), this, SLOT(update_orientation_lock()));
  connect(this, SIGNAL(orientationChanged()), this, SLOT(update_orientation()));
  connect(this, SIGNAL(full_wave_lockChanged()), this, SLOT(update_full_wave_lock()));
  connect(this, SIGNAL(torchChanged()), this, SLOT(update_torch()));
}

AndroidActivity::~AndroidActivity()
{
  if (m_morse_code_engine)
    delete m_morse_code_engine;
}

/**************************************************************************************************/

void
AndroidActivity::set_orientation_lock(bool orientation_lock)
{
  qInfo() << "set_orientation_lock" << orientation_lock;

  if (m_orientation_lock == orientation_lock)
    return;

  m_orientation_lock = orientation_lock;
  emit orientation_lockChanged();
}

bool
AndroidActivity::orientation_lock() const
{
  return m_orientation_lock;
}

void
AndroidActivity::update_orientation_lock()
{
  if (m_orientation_lock)
    QtAndroid::androidActivity().callMethod<void>("lock_orientation", "()V");
  else
    QtAndroid::androidActivity().callMethod<void>("unlock_orientation", "()V");
}

/**************************************************************************************************/

void
AndroidActivity::set_orientation(AndroidActivity::ScreenOrientation orientation)
{
  qInfo() << "set_orientation" << orientation;

  if (m_orientation == orientation)
    return;

  m_orientation = orientation;
  emit orientationChanged();
}

AndroidActivity::ScreenOrientation
AndroidActivity::orientation() const
{
  return m_orientation;
}

void
AndroidActivity::update_orientation()
{
  switch (m_orientation) {
  case Portrait:
    QtAndroid::androidActivity().callMethod<void>("request_portrait_orientation", "()V");
  case Landscape:
    QtAndroid::androidActivity().callMethod<void>("request_landscape_orientation", "()V");
  case Sensor:
  default:
    QtAndroid::androidActivity().callMethod<void>("request_sensor_orientation", "()V");
  }
}

/**************************************************************************************************/

void
AndroidActivity::set_full_wave_lock(bool full_wave_lock)
{
  qInfo() << "set_full_wave_lock" << full_wave_lock;

  if (m_full_wave_lock == full_wave_lock)
    return;

  m_full_wave_lock = full_wave_lock;
  emit full_wave_lockChanged();
}

bool
AndroidActivity::full_wave_lock() const
{
  return m_full_wave_lock;
}

void
AndroidActivity::update_full_wave_lock()
{
  if (m_full_wave_lock)
    QtAndroid::androidActivity().callMethod<void>("acquire_lock_full_wave", "()V");
  else
    QtAndroid::androidActivity().callMethod<void>("release_full_wave", "()V");
}

/**************************************************************************************************/

void
AndroidActivity::set_torch(bool enabled)
{
  qInfo() << "set_torch" << enabled;

  if (m_torch_enabled == enabled)
    return;

  m_torch_enabled = enabled;
  emit torchChanged();
}

bool
AndroidActivity::torch() const
{
  return m_torch_enabled;
}

void
AndroidActivity::update_torch()
{
  QtAndroid::androidActivity().callMethod<void>("set_torch_mode", "(Z)V", m_torch_enabled);
}

/**************************************************************************************************/

void
AndroidActivity::issue_call(const QString & phone_number)
{
  qInfo() << "issue_call" << phone_number;
  QAndroidJniObject j_phone_number = QAndroidJniObject::fromString(phone_number);
  // void issue_call(String phone_number)
  QtAndroid::androidActivity().callMethod<void>("issue_call", "(Ljava/lang/String;)V", j_phone_number.object<jstring>());
}

void
AndroidActivity::issue_dial(const QString & phone_number)
{
  qInfo() << "issue_dial" << phone_number;
  QAndroidJniObject j_phone_number = QAndroidJniObject::fromString(phone_number);
  // void issue_dial(String phone_number)
  QtAndroid::androidActivity().callMethod<void>("issue_dial", "(Ljava/lang/String;)V", j_phone_number.object<jstring>());
}

/**************************************************************************************************/

void
AndroidActivity::load_morse_code_engine()
{
  if (!m_morse_code_engine)
    m_morse_code_engine = new InternationalMorseCodeEngine();
}

void
AndroidActivity::perform_lamp_signal(const QString & message, int rate_ms = 250)
{
  load_morse_code_engine();
  QString encoded_message = m_morse_code_engine->encode(message, true);
  qInfo() << "perform_lamp_signal" << message << encoded_message;
  QAndroidJniObject j_encoded_message = QAndroidJniObject::fromString(encoded_message);
  QtAndroid::androidActivity().callMethod<void>("perform_lamp_signal", "(Ljava/lang/String;I)V", j_encoded_message.object<jstring>(), rate_ms);
}

QString
AndroidActivity::decode_morse(const QString & encoded_message)
{
  load_morse_code_engine();
  return m_morse_code_engine->decode(encoded_message);
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
