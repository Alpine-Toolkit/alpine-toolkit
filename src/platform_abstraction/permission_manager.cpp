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

#include "permission_manager.h"
#include "alpine_toolkit.h"

/**************************************************************************************************/

PermissionManager::PermissionManager()
  : m_callbacks()
{}

PermissionManager::~PermissionManager()
{}

/**************************************************************************************************/

bool
PermissionManager::require_write_permission(const QString & path) const
{
  return false;
}

/**************************************************************************************************/

QString
PermissionManager::permission_explanation(const QString & permission) const
{
  const char * explanation;

  // Fixme: better place ?
  if (permission == QLatin1String("WRITE_EXTERNAL_STORAGE"))
    explanation =
      "<p>The permission to read and write the external storage is required "
      "in order to write permanent data and access an external sdcard on your device.<p> "
      "<p>The application will create a top directory named <strong>alpine-toolkit</strong> "
      "at the root of the primary external storage, where it will store all the data. "
      "<strong>This directory will remain if you uninstall the application.</strong></p> "
      "<p>If you need more space on your device, you can later move this directory to an external sdcard.</p>";

  return tr(explanation);
}

/**************************************************************************************************/

void
PermissionManager::check_permission(const QString & permission, const PermissionCallback & callback)
{
  if (is_permission_granted(permission))
    callback(permission, true);
  else {
    register_callback(permission, callback);

    if (need_explain(permission))
      // signal to ui
      emit open_explain_permission(permission, permission_explanation(permission));
    else
      request_permission(permission);
  }
}

/**************************************************************************************************/

void
PermissionManager::register_callback(const QString & permission, const PermissionCallback & callback)
{
  if (not m_callbacks.contains(permission))
    m_callbacks[permission] = PermissionCallbackList();

  PermissionCallbackList & callbacks = m_callbacks[permission];

  // Fixme: we cannot implement reliably operator== for std::function<void(const QString&, bool)>
  if (callbacks.size())
    qATWarning() << "Callback is already registered for permission" << permission;
  // if (not callbacks.contains(callback))
  callbacks << callback;
  // else
  //    qATWarning() << "Callback is already registered for permission" << permission;
}

void
PermissionManager::call_callback(const QString & permission, bool granted)
{
  if (m_callbacks.contains(permission)) {
    for (const auto & callback : m_callbacks[permission])
      callback(permission, granted);
    m_callbacks[permission].clear();
  } else
    qATWarning() << "Any callback for permission" << permission;
}

/**************************************************************************************************/

void
PermissionManager::on_accepted_explain_permission(const QString & permission)
{
  qATInfo() << "Permission accepted" << permission;
  request_permission(permission);
}

void
PermissionManager::on_rejected_explain_permission(const QString & permission)
{
  qATInfo() << "Permission rejected" << permission;
  call_callback(permission, false);
}
