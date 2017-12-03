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

#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>
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

QStringList
AndroidPlatform::need_explain() const
{
  qATInfo() << "need_explain";

  QAndroidJniObject j_string = QtAndroid::androidActivity().callObjectMethod("need_explain", "()Ljava/lang/String");
  QString permissions = j_string.toString();

  return permissions.split(QChar(','));
}

QStringList
AndroidPlatform::need_grant() const
{
  // Fixme: duplicated code

  qATInfo() << "need_grant";

  QAndroidJniObject j_string = QtAndroid::androidActivity().callObjectMethod("need_grant", "()Ljava/lang/String");
  QString permissions = j_string.toString();

  return permissions.split(QChar(','));
}

void
AndroidPlatform::ask_permission(const QString & permission) const
{
  qATInfo() << "ask_permission" << permission;

  QAndroidJniObject j_string = QAndroidJniObject::fromString(permission);
  QtAndroid::androidActivity().callMethod<void>("ask_permission", "(Ljava/lang/String)V", j_string.object<jstring>());
}

bool
AndroidPlatform::is_permission_granted(const QString & permission) const
{
  qATInfo() << "is_permission_granted" << permission;

  QAndroidJniObject j_string = QAndroidJniObject::fromString(permission);
  jboolean rc = QtAndroid::androidActivity().callMethod<jboolean>("is_permission_granted", "(Ljava/lang/String)V", j_string.object<jstring>());

  return rc;
}

bool
AndroidPlatform::is_permission_denied(const QString & permission) const
{
  qATInfo() << "is_permission_denied" << permission;

  QAndroidJniObject j_string = QAndroidJniObject::fromString(permission);
  jboolean rc = QtAndroid::androidActivity().callMethod<jboolean>("is_permission_denied", "(Ljava/lang/String)V", j_string.object<jstring>());

  return rc;
}

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
  QtAndroid::androidActivity().callMethod<void>("perform_lamp_signal", "(I;I)V", period, duty_cycle);
}

void
AndroidPlatform::stop_lamp_dimmer() const
{
  QtAndroid::androidActivity().callMethod<void>("stop_lamp_dimmer", "()V");
}
