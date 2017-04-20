/***************************************************************************************************
 **
 ** $QTCARTO_BEGIN_LICENSE:GPL3$
 **
 ** Copyright (C) 2017 Fabrice Salvaire
 ** Contact: http://www.fabrice-salvaire.fr
 **
 ** This file is part of the QtCarto library.
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
 ** $QTCARTO_END_LICENSE$
 **
 ***************************************************************************************************/

/**************************************************************************************************/

package org.alpine_toolkit;

import java.util.Map;
import java.util.Vector;

import android.content.pm.PackageManager;

// https://developer.android.com/topic/libraries/support-library/index.html
// https://developer.android.com/topic/libraries/support-library/packages.html
// Android Studio: use Build > Edit Libraries & Dependencies to update build.gradle
// https://developer.android.com/studio/build/dependencies.html
import android.support.v4.app.ActivityCompat; // API 23
import android.support.v4.content.ContextCompat ; // API 23
import android.util.Log;

/**************************************************************************************************/

public class PermissionHelper
{
  private static final String LOG_TAG = Constants.LOG.TAG;

  private static AlpineToolkitActivity m_activity;

  /**********************************************/

  public PermissionHelper(AlpineToolkitActivity activity)
  {
    m_activity = activity;
  }

  /**********************************************/

  public enum PermissionStatus
  {
    Granted,
    Refused, // unused
    NeedExplain,
    NeedGrant,
  }

  private Map<String, Integer> m_permission_request_map;
  private Vector<String> m_permission_requests;

  private
  int get_permission_id(String permission)
  {
    if (m_permission_request_map.containsKey(permission))
      return m_permission_request_map.get(permission);
    else {
      int id = m_permission_requests.size();
      m_permission_request_map.put(permission, id);
      m_permission_requests.add(permission);
      return id;
    }
  }

  public
  int check_permission(String permission) // Manifest.permission.READ_CONTACTS
  {
    if (ContextCompat.checkSelfPermission(m_activity, permission) == PackageManager.PERMISSION_GRANTED) {
      Log.i(LOG_TAG, "Permission: " + permission + " is granted");
      return PermissionStatus.Granted.ordinal();
    } else
      // Should we show an explanation ?
      if (ActivityCompat.shouldShowRequestPermissionRationale(m_activity, permission)) {
        // Show an explanation to the user *asynchronously* -- don't
        // block this thread waiting for the user's response! After
        // the user sees the explanation, try again to request the
        // permission.
        Log.i(LOG_TAG, "Permission: " + permission + " need explain");
        return PermissionStatus.NeedExplain.ordinal();
      } else {
        // No explanation needed, we can request the permission.
        int permission_id = get_permission_id(permission);
        // id is an app-defined int constant. The callback method gets
        // the result of the request.
        ActivityCompat.requestPermissions(m_activity, new String[]{permission}, permission_id);
        Log.i(LOG_TAG, "Permission: " + permission + " need granted");
        return PermissionStatus.NeedGrant.ordinal();
      }
  }

  // @Override
  public void onRequestPermissionsResult(int permission_id, String permissions[], int[] grant_results) {
    // Fixme: id vs string ???, multi-permissions ?
    // If request is cancelled, the result arrays are empty.
    String permission = permissions[0];
    if (grant_results.length > 0 && grant_results[0] == PackageManager.PERMISSION_GRANTED) {
      // permission was granted.
      Log.i(LOG_TAG, "Permission: " + permission + " granted");
    } else {
      // permission denied
      Log.i(LOG_TAG, "Permission: " + permission + " denied");
    }
    // Call c++
  }
}
