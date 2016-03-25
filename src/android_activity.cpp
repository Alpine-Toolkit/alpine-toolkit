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
    m_full_wave_lock(false)
{
  connect(this, SIGNAL(orientation_lockChanged()), this, SLOT(update_orientation_lock()));
  connect(this, SIGNAL(orientationChanged()), this, SLOT(update_orientation()));
  connect(this, SIGNAL(full_wave_lockChanged()), this, SLOT(update_full_wave_lock()));
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

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
