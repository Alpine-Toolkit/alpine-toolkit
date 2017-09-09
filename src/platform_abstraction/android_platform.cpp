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

#include "android_platform.h"

#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroid>
#include <QtDebug>

/**************************************************************************************************/

AndroidPlatform::AndroidPlatform(QObject * parent)
  : PlatformAbstraction(parent)
{
  connect(this, SIGNAL(orientation_lockChanged()), this, SLOT(update_orientation_lock()));
  connect(this, SIGNAL(orientationChanged()), this, SLOT(update_orientation()));
  connect(this, SIGNAL(full_wave_lockChanged()), this, SLOT(update_full_wave_lock()));
  connect(this, SIGNAL(torchChanged()), this, SLOT(update_torch()));
}

AndroidPlatform::~AndroidPlatform()
{}

/**************************************************************************************************/

void
AndroidPlatform::update_orientation_lock()
{
  if (m_orientation_lock)
    QtAndroid::androidActivity().callMethod<void>("lock_orientation", "()V");
  else
    QtAndroid::androidActivity().callMethod<void>("unlock_orientation", "()V");
}

/**************************************************************************************************/

void
AndroidPlatform::update_orientation()
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
AndroidPlatform::update_full_wave_lock()
{
  if (m_full_wave_lock)
    QtAndroid::androidActivity().callMethod<void>("acquire_lock_full_wave", "()V");
  else
    QtAndroid::androidActivity().callMethod<void>("release_full_wave", "()V");
}

/**************************************************************************************************/

void
AndroidPlatform::update_torch()
{
  QtAndroid::androidActivity().callMethod<void>("set_torch_mode", "(Z)V", m_torch_enabled);
}

/**************************************************************************************************/

void
AndroidPlatform::issue_call(const QString & phone_number)
{
  qInfo() << "issue_call" << phone_number;
  QAndroidJniObject j_phone_number = QAndroidJniObject::fromString(phone_number);
  // void issue_call(String phone_number)
  QtAndroid::androidActivity().callMethod<void>("issue_call", "(Ljava/lang/String;)V", j_phone_number.object<jstring>());
}

void
AndroidPlatform::issue_dial(const QString & phone_number)
{
  qInfo() << "issue_dial" << phone_number;
  QAndroidJniObject j_phone_number = QAndroidJniObject::fromString(phone_number);
  // void issue_dial(String phone_number)
  QtAndroid::androidActivity().callMethod<void>("issue_dial", "(Ljava/lang/String;)V", j_phone_number.object<jstring>());
}

/**************************************************************************************************/

void
AndroidPlatform::perform_lamp_signal(const QString & message, int rate_ms)
{
  QAndroidJniObject j_message = QAndroidJniObject::fromString(message);
  QtAndroid::androidActivity().callMethod<void>("perform_lamp_signal", "(Ljava/lang/String;I)V", j_message.object<jstring>(), rate_ms);
}
