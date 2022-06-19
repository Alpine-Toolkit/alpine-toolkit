/***************************************************************************************************
 *
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

/**************************************************************************************************/

#include "android_fake_permission_manager.h"
#include "alpine_toolkit.h"

/**************************************************************************************************/

AndroidFakePermissionManager::AndroidFakePermissionManager()
  : PermissionManager(),
    m_permission_status()
{
  m_permission_status[QLatin1String("WRITE_EXTERNAL_STORAGE")] = false;
}

AndroidFakePermissionManager::~AndroidFakePermissionManager()
{}

/**************************************************************************************************/

bool
AndroidFakePermissionManager::require_write_permission(const QString & path) const
{
  bool rc = true;
  qATInfo() << "require_write_permission" << path << rc;
  return rc;
}

/**************************************************************************************************/

bool
AndroidFakePermissionManager::need_explain(const QString & permission)
{
  bool rc = permission == QLatin1String("WRITE_EXTERNAL_STORAGE");
  qATInfo() << "need_explain" << permission << rc;
  return rc;
}

/**************************************************************************************************/

bool
AndroidFakePermissionManager::is_permission_granted(const QString & permission) const
{
  bool rc = m_permission_status[permission];
  qATInfo() << "is_permission_granted" << permission << rc;
  return rc;
}

/**************************************************************************************************/

void
AndroidFakePermissionManager::request_permission(const QString & permission)
{
  qATInfo() << "ask_permission" << permission;

  // Could be false
  m_permission_status[permission] = true;
  call_callback(permission, true);
}
