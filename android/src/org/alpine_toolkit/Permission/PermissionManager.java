/***************************************************************************************************
 **
 ** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 **
 ** Copyright (C) 2017 Fabrice Salvaire
 ** Contact: http://www.fabrice-salvaire.fr
 **
 ** This file is part of the Alpine Toolkit software.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 ** $ALPINE_TOOLKIT_END_LICENSE$
 **
 ***************************************************************************************************/

/*
 * Note: Android doesn't provide signal when permission change
 *
 */

/**************************************************************************************************/

package org.alpine_toolkit.Permission;

import org.alpine_toolkit.AlpineToolkitActivity;
import org.alpine_toolkit.Constants;
import org.alpine_toolkit.NativeFunctions;

import android.content.pm.PackageManager;
import android.os.Build;
import android.util.Log;

import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

// https://developer.android.com/topic/libraries/support-library/index.html
// https://developer.android.com/topic/libraries/support-library/packages.html
// Android Studio: use Build > Edit Libraries & Dependencies to update build.gradle
// https://developer.android.com/studio/build/dependencies.html
import android.support.v4.app.ActivityCompat; // API 23
import android.support.v4.content.ContextCompat ; // API 23

/**************************************************************************************************/

public class PermissionManager
{
  private static final String LOG_TAG = Constants.LOG.TAG;

  private AlpineToolkitActivity m_activity;

  private Map<String, PermissionStatus> m_permissions;

  /**********************************************/

  public PermissionManager(AlpineToolkitActivity activity)
  {
    m_activity = activity;
    m_permissions = new HashMap<String, PermissionStatus>();
  }

  /**********************************************/

  /* Check permission status and register it
   *
   */
  public PermissionStatus check_permission(String permission)
  {
    PermissionStatus permission_status = m_permissions.get(permission);
    if (permission_status != null) {
      permission_status = new PermissionStatus(permission);
      m_permissions.put(permission_status.permission(), permission_status);
    }

    if (ContextCompat.checkSelfPermission(m_activity, permission) == PackageManager.PERMISSION_GRANTED) {
      Log.i(LOG_TAG, "Permission: " + permission + " is granted");
      permission_status.set_granted();
    } else {
      // Should we show an explanation ?
      if (ActivityCompat.shouldShowRequestPermissionRationale(m_activity, permission)) {
        // Show an explanation to the user *asynchronously* -- don't
        // block this thread waiting for the user's response! After
        // the user sees the explanation, try again to request the
        // permission.
        Log.i(LOG_TAG, "Permission: " + permission + " need explain");
        if (permission_status.is_explained())
          permission_status.set_need_grant();
        else
          permission_status.set_need_explain();
      } else {
        // No explanation needed, we can request the permission.
        // id is an app-defined int constant. The callback method gets
        // the result of the request.
        Log.i(LOG_TAG, "Permission: " + permission + " need grant");
        permission_status.set_need_grant();
      }
    }

    return permission_status;
  }

  /* To check permission status at startup
   *
   */
  public void check_permissions(String[] permissions)
  {
    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) // API 21
      for (String permission : permissions)
        check_permission(permission);
  }

  /**********************************************/

  public void set_as_explained(String permission)
  {
    PermissionStatus permission_status = m_permissions.get(permission);
    if (permission_status != null && permission_status.is_need_explain())
      permission_status.set_as_explained();
  }

  /**********************************************/

  public String[] need_explain()
  {
    ArrayList<String> permissions = new ArrayList<String>();
    for (PermissionStatus permission_status : m_permissions.values()) {
      if (permission_status.is_need_explain())
        permissions.add(permission_status.permission());
    }
    return permissions.toArray(new String[0]);
  }

  public String[] need_grant()
  {
    ArrayList<String> permissions = new ArrayList<String>();
    for (PermissionStatus permission_status : m_permissions.values()) {
      if (permission_status.is_need_grant())
        permissions.add(permission_status.permission());
    }
    return permissions.toArray(new String[0]);
  }

  /**********************************************/

  public Boolean is_permission_granted(final String permission)
  {
    // Always recheck permission status
    PermissionStatus permission_status = check_permission(permission);
    return permission_status.is_granted();
  }

  public Boolean is_permission_denied(final String permission)
  {
    // Always recheck permission status
    PermissionStatus permission_status = check_permission(permission);
    return permission_status.is_denied();
  }

  /**********************************************/

  /* Request to grant a permission
   *
   */
  public void request_permission(String permission)
  {
    // Always recheck permission status
    PermissionStatus permission_status = check_permission(permission);
    if (permission_status.is_need_grant())
      ActivityCompat.requestPermissions(m_activity, new String[]{permission}, permission_status.id());
  }

  /*
   * Permission slot: call native functions
   *
   */
  // @Override
  public void onRequestPermissionsResult(int permission_id, String permissions[], int[] grant_results) {
    // If request is cancelled, the result arrays are empty.
    for (int i = 0; i < permissions.length; ++i) {
      String permission = permissions[i];
      int grant_result = grant_results[i];
      PermissionStatus permission_status = m_permissions.get(permission);
      if (permission_status != null) {
        if (grant_result == PackageManager.PERMISSION_GRANTED) {
          // permission was granted.
          Log.i(LOG_TAG, "Permission: " + permission + " granted");
          permission_status.set_granted();
          NativeFunctions.on_permission_granted(permission);
        } else {
          // permission denied
          Log.i(LOG_TAG, "Permission: " + permission + " denied");
          permission_status.set_denied();
          NativeFunctions.on_permission_denied(permission);
        }
      } else {
        Log.e(LOG_TAG, "permission error: " + permission);
      }
    }
  }
}
