/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire.
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine Toolkit software.
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
#include "alpine_toolkit.h"

#include "android_permission_manager.h"

#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
#include <QtAndroid>
#include <QtDebug>

/**************************************************************************************************/

AndroidPlatform::AndroidPlatform(QObject * parent)
  : PlatformAbstraction(parent)
{
  m_permission_manager = new AndroidPermissionManager();
}

AndroidPlatform::~AndroidPlatform()
{}

/**************************************************************************************************/

QStringList
AndroidPlatform::external_storages() const
{
  QAndroidJniObject array = QtAndroid::androidActivity().callObjectMethod("get_external_storages", "()[Ljava/lang/String;");

  QAndroidJniEnvironment jni_env;
  int length = jni_env->GetArrayLength(array.object<jarray>());
  QStringList paths;
  for (int i = 0; i < length; i++) {
    QAndroidJniObject element = jni_env->GetObjectArrayElement(array.object<jobjectArray>(), i);
    paths << element.toString();
  }

  return paths;
}

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
AndroidPlatform::issue_call(const QString & phone_number) const
{
  qATInfo() << "issue_call" << phone_number;
  QAndroidJniObject j_phone_number = QAndroidJniObject::fromString(phone_number);
  // void issue_call(String phone_number)
  QtAndroid::androidActivity().callMethod<void>("issue_call", "(Ljava/lang/String;)V", j_phone_number.object<jstring>());
}

void
AndroidPlatform::issue_dial(const QString & phone_number) const
{
  qATInfo() << "issue_dial" << phone_number;
  QAndroidJniObject j_phone_number = QAndroidJniObject::fromString(phone_number);
  // void issue_dial(String phone_number)
  QtAndroid::androidActivity().callMethod<void>("issue_dial", "(Ljava/lang/String;)V", j_phone_number.object<jstring>());
}

/**************************************************************************************************/

void
AndroidPlatform::perform_lamp_signal(const QString & message, int rate_ms) const
{
  qATInfo() << "perform_lamp_signal" << message << rate_ms;
  QAndroidJniObject j_message = QAndroidJniObject::fromString(message);
  QtAndroid::androidActivity().callMethod<void>("perform_lamp_signal", "(Ljava/lang/String;I)V", j_message.object<jstring>(), rate_ms);
}

void
AndroidPlatform::stop_lamp_signal() const
{
  QtAndroid::androidActivity().callMethod<void>("stop_lamp_signal", "()V");
}

void
AndroidPlatform::start_lamp_dimmer(int period, int duty_cycle) const
{
  qATInfo() << "start_lamp_dimmer" << period << duty_cycle;
  QtAndroid::androidActivity().callMethod<void>("start_lamp_dimmer", "(I;I)V", period, duty_cycle);
}

void
AndroidPlatform::stop_lamp_dimmer() const
{
  QtAndroid::androidActivity().callMethod<void>("stop_lamp_dimmer", "()V");
}
