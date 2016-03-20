#include "android_activity.h"

#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroid>

#include <QtDebug>

AndroidActivity::AndroidActivity(QObject *parent)
  : QObject(parent),
    m_orientation_lock(false)
{
  connect(this, SIGNAL(orientationLockChanged()), this, SLOT(updateOrientationLock()));
}

void
AndroidActivity::set_orientation_lock(bool orientation_lock)
{
  qInfo() << "set_orientation_lock" << orientation_lock;

  if (m_orientation_lock == orientation_lock)
    return;

  m_orientation_lock = orientation_lock;
  emit orientationLockChanged();
}

bool
AndroidActivity::orientation_lock() const
{
  return m_orientation_lock;
}

void
AndroidActivity::updateOrientationLock()
{
  if (m_orientation_lock)
    QtAndroid::androidActivity().callMethod<void>("lock_orientation", "()V");
  else
    QtAndroid::androidActivity().callMethod<void>("unlock_orientation", "()V");
}

