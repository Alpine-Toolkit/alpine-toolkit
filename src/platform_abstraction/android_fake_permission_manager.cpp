/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
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
