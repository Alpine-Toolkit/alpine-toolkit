/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
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
** $ALPINE_TOOLKIT_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

package org.alpine_toolkit;

import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;

import android.support.v4.content.ContextCompat;

/**************************************************************************************************/

// class LampSignalRunnable implements Runnable {
//   @Override
//   public void run() {
//     android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_BACKGROUND);
//   }
// }

/**************************************************************************************************/

public class AlpineToolkitActivity extends QtActivity
{
  private static final String LOG_TAG = "AlpineToolkitActivity";

  private static AlpineToolkitActivity m_instance;

  private CameraHelper m_camera_helper = null;
  private DeviceUserInterfaceHelper m_device_ui_helper = null;
  private PermissionHelper m_permission_helper = null;
  private PhoneHelper m_phone_helper = null;
  private ServiceHelper m_service_helper = null;

  /**********************************************/

  public AlpineToolkitActivity()
  {
    m_instance = this;

    m_camera_helper = new CameraHelper(this);
    m_device_ui_helper = new DeviceUserInterfaceHelper(this);
    m_permission_helper = new PermissionHelper(this);
    m_phone_helper = new PhoneHelper(this);
    m_service_helper = new ServiceHelper(this);
  }

  /**********************************************/

  @Override
  public void onCreate(Bundle savedInstanceState)
  {
    Log.i(LOG_TAG, ">>>>>>>>>> AlpineToolkitActivity.onCreate <<<<<<<<<<");

    // Fixme: hardcoded
    set_status_bar_background_color(Color.parseColor("#3949ab"));

    super.onCreate(savedInstanceState);

    Log.i(LOG_TAG, "Is service running? " + m_service_helper.is_service_running());

    // Debug
    try {
      Process process = Runtime.getRuntime().exec("mount");
      process.waitFor();
      BufferedReader buffered_reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
      StringBuilder output = new StringBuilder();
      String line;
      while ((line = buffered_reader.readLine()) != null)
        output.append(line + "\n");
      Log.i(LOG_TAG, "Mount: " + output);
    }
    // } catch (Exception e) {
    catch (java.io.IOException e)
    {}
    catch (java.lang.InterruptedException e)
    {}

    // Get external SDCard path
    Log.i(LOG_TAG, "External SDCard: " + Environment.getExternalStorageDirectory()); // /storage/emulated/0
    // File[] paths = getExternalMediaDirs(); // API 21
    File[] external_files_dirs = ContextCompat.getExternalFilesDirs(this, null);
    for (File path : external_files_dirs)
      Log.i(LOG_TAG, "external files dir: " + path);

    // Check permissions
    String[] permissions = {
            "android.permission.BODY_SENSORS",
            "android.permission.CAMERA",
            "android.permission.FLASHLIGHT",
            "android.permission.READ_EXTERNAL_STORAGE",
            "android.permission.READ_PHONE_STATE",
            "android.permission.WRITE_EXTERNAL_STORAGE",
    };
    if (Build.VERSION.SDK_INT >= 21) { // Build.VERSION_CODES.LOLLIPOP
      for (String permission : permissions) {
        int rc = m_permission_helper.check_permission(permission);
        // if (rc == PermissionHelper.PermissionStatus.Granted.ordinal())
      }
    }

    // get_display_metrics();
    // get_device_id();
    // set_torch_mode(true);
  }

  @Override
  protected void onDestroy()
  {
    m_camera_helper.release_camera();
    super.onDestroy();
  }

  /**********************************************/

  @Override
  public void onRequestPermissionsResult(int permission_id, String permissions[], int[] grant_results)
  {
    m_permission_helper.onRequestPermissionsResult(permission_id, permissions, grant_results);
  }

  /**********************************************
   *
   * Device UI API
   *
   */

  public void get_display_metrics()
  {
    m_device_ui_helper.get_display_metrics();
  }

  // private
  public void set_status_bar_background_color(int color)
  {
    m_device_ui_helper.set_status_bar_background_color(color);
  }

  // used
  public void lock_orientation()
  {
    m_device_ui_helper.lock_orientation();
  }

  // used
  public void unlock_orientation()
  {
    m_device_ui_helper.unlock_orientation();
  }

  // used
  public void request_sensor_orientation()
  {
    m_device_ui_helper.request_sensor_orientation();
  }

  // used
  public void request_portrait_orientation()
  {
    m_device_ui_helper.request_portrait_orientation();
  }

  // used
  public void request_landscape_orientation()
  {
    m_device_ui_helper.request_landscape_orientation();
  }

  /**********************************************/

  // used
  public void acquire_full_wake_lock()
  {
    m_device_ui_helper.acquire_full_wake_lock();
  }

  // used
  public void release_full_wake_lock()
  {
    m_device_ui_helper.release_full_wake_lock();
  }

  /**********************************************
   *
   * Phone API
   *
   */

  public void get_device_id()
  {
     m_phone_helper.get_device_id();
  }

  // used
  public void issue_call(String phone_number)
  {
    m_phone_helper.issue_call(phone_number);
  }

  // used
  public void issue_dial(String phone_number)
  {
    m_phone_helper.issue_dial(phone_number);
  }

  /**********************************************
   *
   * Camera API
   *
   */

  // used
  public void set_torch_mode(boolean enabled)
  {
    m_camera_helper.set_torch_mode(enabled);
  }

  // used
  public void perform_lamp_signal(final String encoded_message, final int rate_ms)
  {
    m_camera_helper.perform_lamp_signal(encoded_message, rate_ms);
  }

  /**********************************************
   *
   * SD Card API
   *
   */
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
