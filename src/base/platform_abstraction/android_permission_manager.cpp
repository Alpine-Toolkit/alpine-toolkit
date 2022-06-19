/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "android_permission_manager.h"
#include "alpine_toolkit.h"

#include <QAndroidJniEnvironment>
#include <QAndroidJniObject>

// Fixme: remove AT implementation
#define USE_QT_PERMISSION_IMPLEMENTATION

/**************************************************************************************************/

AndroidPermissionManager::AndroidPermissionManager()
  : PermissionManager(),
    m_need_explain_cache()
{}

AndroidPermissionManager::~AndroidPermissionManager()
{}

/**************************************************************************************************/

QString
AndroidPermissionManager::to_android_permission(const QString & permission) const
{
  return QLatin1String("android.permission.") + permission;
}

QString
AndroidPermissionManager::from_android_permission(const QString & permission) const
{
  QLatin1String prefix("android.permission.");
  if (permission.startsWith(prefix))
    return permission.mid(prefix.size());
  else {
    qATWarning() << "Invalid permission" << permission;
    return QString();
  }
}


/**************************************************************************************************/

bool
AndroidPermissionManager::require_write_permission(const QString & path) const
{
  qATInfo() << "require_write_permission" << path;

  // Fixme:
  return true;
}

/**************************************************************************************************/

/*
#ifndef USE_QT_PERMISSION_IMPLEMENTATION
QStringList
AndroidPermissionManager::need_explain() const
{
  qATInfo() << "need_explain";

  QAndroidJniObject j_string = QtAndroid::androidActivity().callObjectMethod("need_explain", "()Ljava/lang/String");
  QString permissions = j_string.toString();

  return permissions.split(QChar(','));
}

QStringList
AndroidPermissionManager::need_grant() const
{
  // Fixme: duplicated code

  qATInfo() << "need_grant";

  QAndroidJniObject j_string = QtAndroid::androidActivity().callObjectMethod("need_grant", "()Ljava/lang/String");
  QString permissions = j_string.toString();

  return permissions.split(QChar(','));
}
#endif
*/

/**************************************************************************************************/

bool
AndroidPermissionManager::need_explain(const QString & permission)
{
  qATInfo() << "need_explain" << permission;

  if (m_need_explain_cache.contains(permission))
    return m_need_explain_cache[permission];
  else {
    bool rc;
#ifdef USE_QT_PERMISSION_IMPLEMENTATION
    rc = QtAndroid::shouldShowRequestPermissionRationale(from_android_permission(permission));
#else
    // Fixme: optimise ?
    rc = need_explain().contains(permission); // Fixme: name clash
#endif
    m_need_explain_cache[permission] = rc;
    return rc;
  }
}

/**************************************************************************************************/

bool
AndroidPermissionManager::is_permission_granted(const QString & permission) const
{
  qATInfo() << "is_permission_granted" << permission;

#ifdef USE_QT_PERMISSION_IMPLEMENTATION
  return QtAndroid::checkPermission(to_android_permission(permission)) == QtAndroid::PermissionResult::Granted;
#else
  QAndroidJniObject j_string = QAndroidJniObject::fromString(permission);
  jboolean rc = QtAndroid::androidActivity().callMethod<jboolean>("is_permission_granted", "(Ljava/lang/String)V", j_string.object<jstring>());
  return rc;
#endif
}

bool
AndroidPermissionManager::is_permission_denied(const QString & permission) const
{
  qATInfo() << "is_permission_denied" << permission;

#ifdef USE_QT_PERMISSION_IMPLEMENTATION
  return QtAndroid::checkPermission(to_android_permission(permission)) == QtAndroid::PermissionResult::Denied;
#else
  QAndroidJniObject j_string = QAndroidJniObject::fromString(permission);
  jboolean rc = QtAndroid::androidActivity().callMethod<jboolean>("is_permission_denied", "(Ljava/lang/String)V", j_string.object<jstring>());
  return rc;
#endif
}

/**************************************************************************************************/

void
AndroidPermissionManager::request_permission(const QString & permission)
{
  qATInfo() << "ask_permission" << permission;

#ifdef USE_QT_PERMISSION_IMPLEMENTATION
  QStringList permissions;
  permissions << to_android_permission(permission);
  QtAndroid::PermissionResultCallback callback = [this](const QtAndroid::PermissionResultMap & map) {
    this->permission_callback(map);
  };
  QtAndroid::requestPermissions(permissions, callback);
#else
  QAndroidJniObject j_string = QAndroidJniObject::fromString(permission);
  QtAndroid::androidActivity().callMethod<void>("ask_permission", "(Ljava/lang/String)V", j_string.object<jstring>());
#endif
}

/**************************************************************************************************/

void
AndroidPermissionManager::permission_callback(const QtAndroid::PermissionResultMap & map)
{
  qATInfo() << "Permission callback"; // << map;

  for (const auto & android_permission : map.keys()) {
    QString permission = from_android_permission(android_permission);
    bool granted = map[permission] == QtAndroid::PermissionResult::Granted;
    call_callback(permission, granted);
  }
}

/*
void
AndroidPermissionManager::on_permission_granted(const QString & permission)
{
  qATInfo() << "Permission granted" << permission;
  call_callback(permission, true);
}

void
AndroidPermissionManager::on_permission_denied(const QString & permission)
{
  qATInfo() << "Permission denied" << permission;
  call_callback(permission, false);
}
*/
