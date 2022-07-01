/***************************************************************************************************
**
 * This file is part of the Alpine Toolkit software.
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 * SPDX-License-Identifier: GPL-3.0-only
**
***************************************************************************************************/

/**************************************************************************************************/

package org.alpine_toolkit;

import org.alpine_toolkit.Camera.CameraManagerBase;
import org.alpine_toolkit.Camera.CameraManagerIcs;
import org.alpine_toolkit.Camera.CameraManagerMarshmallow;
import org.alpine_toolkit.Permission.PermissionManager;

import android.graphics.Color;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.text.TextUtils;
import android.util.Log;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;

import android.support.v4.content.ContextCompat;

/**************************************************************************************************/

/*
class LampSignalRunnable implements Runnable {
  @Override
  public void run() {
    android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_BACKGROUND);
  }
}
*/

/**************************************************************************************************/

public class AlpineToolkitActivity extends QtActivity
{
  private static final String LOG_TAG = "AlpineToolkitActivity";

  private static AlpineToolkitActivity m_instance;

  private CameraManagerBase m_camera_manager = null;
  private DeviceUserInterfaceHelper m_device_ui_helper = null;
  private PermissionManager m_permission_manager = null;
  private PhoneHelper m_phone_helper = null;
  private ServiceHelper m_service_helper = null;
  private SdCardHelper m_sdcard_helper = null;

  /**********************************************/

  public AlpineToolkitActivity()
  {
    m_instance = this;
  }

  /**********************************************/

  private void _init()
  {
    m_device_ui_helper = new DeviceUserInterfaceHelper(this);
    m_permission_manager = new PermissionManager(this);
    m_phone_helper = new PhoneHelper(this);
    m_service_helper = new ServiceHelper(this);

    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
      _init_marshmallow();
    } else if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
      _init_lollipop();
    } else {
      _init_ics();
    }
  }

  private void _init_ics()
  {
    Log.i(LOG_TAG, "Init for ICS");
    m_camera_manager = new CameraManagerIcs(this);
  }

  private void _init_lollipop()
  {
    Log.i(LOG_TAG, "Init for Lollipop");
    m_camera_manager = new CameraManagerIcs(this);
  }

  private void _init_marshmallow()
  {
    Log.i(LOG_TAG, "Init for Marshmallow");
    m_camera_manager = new CameraManagerMarshmallow(this); // must be called in onCreate
  }

  /**********************************************/

  private void _copy_assets()
  {
    // Copy some assets in a readable place
    // proj4_data/epsg file is required when qtcarto library is loaded
    // Files are copied to /data/user/0/org.alpine_toolkit/files/assets/

    AssetHelper asset_helper = new AssetHelper(this);
    String asset_path = getFilesDir() + "/assets" ;
    asset_helper.copy_assets(asset_path, false);
  }

  /**********************************************/

  @Override
  public void onCreate(Bundle savedInstanceState)
  {
    Log.i(LOG_TAG, ">>>>>>>>>> AlpineToolkitActivity.onCreate <<<<<<<<<<");

    _init();
    _copy_assets();

    // Fixme: hardcoded
    set_status_bar_background_color(Color.parseColor(Constants.UI.BACKGROUND_COLOR));

    super.onCreate(savedInstanceState);

    m_permission_manager.check_permissions(Constants.PERMISSIONS);

    Log.i(LOG_TAG, "Is service running? " + m_service_helper.is_service_running());
    // _log_directories();
    // _debug_log();
  }

  @Override
  protected void onDestroy()
  {
    m_camera_manager._release_camera();
    super.onDestroy();
  }

  /**********************************************/

  private void _log_directories()
  {
    // Returns the absolute path to the directory on the filesystem where files created with openFileOutput(String, int) are stored.
    Log.i(LOG_TAG, "Internal Directory: " + getFilesDir());
    // Returns the absolute path to the application specific cache directory on the filesystem.
    Log.i(LOG_TAG, "Cache Directory: " + getCacheDir());

    // I AlpineToolkitActivity: Internal Directory: /data/user/0/org.alpine_toolkit/files
    // I AlpineToolkitActivity: Cache Directory:    /data/user/0/org.alpine_toolkit/cache

    // Get external path
    Log.i(LOG_TAG, "External Storage Directory: " + Environment.getExternalStorageDirectory()); // /storage/emulated/0
    // Returns absolute path to application-specific directory on the primary shared/external storage device where the application can place cache files it owns. 
    Log.i(LOG_TAG, "External Cache Directory: " + getExternalCacheDir()); // ...Dirs()

    // File[] paths = getExternalMediaDirs(); // API 21
    // cf. SdCardHelper.get_external_storages()
    File[] external_files_dirs = ContextCompat.getExternalFilesDirs(this, null);
    for (File path : external_files_dirs)
      Log.i(LOG_TAG, "External Files Directories: " + path);

    // I AlpineToolkitActivity: External Storage Directory: /storage/emulated/0
    // I AlpineToolkitActivity: External Cache Directory:   /storage/emulated/0/Android/data/org.alpine_toolkit/cache
    // I AlpineToolkitActivity: External Files Directories: /storage/emulated/0/Android/data/org.alpine_toolkit/files
    // I AlpineToolkitActivity: External Files Directories: /storage/18F1-3803/Android/data/org.alpine_toolkit/files
  }

  /**********************************************/

  private void _debug_log()
  {
    /*
    try {
      Process process = Runtime.getRuntime().exec("mount");
      process.waitFor();
      BufferedReader buffered_reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
      StringBuilder output = new StringBuilder();
      String line;
      while ((line = buffered_reader.readLine()) != null)
        output.append(line).append("\n");
      Log.i(LOG_TAG, "Mount: " + output);
    }
    // } catch (Exception e) {
    catch (java.io.IOException e)
    {}
    catch (java.lang.InterruptedException e)
    {}
    */

    // get_display_metrics();
    // get_device_id();
    // set_torch_mode(true);
  }

  /**********************************************/

  @Override
  public void onRequestPermissionsResult(int permission_id, String permissions[], int[] grant_results)
  {
    m_permission_manager.onRequestPermissionsResult(permission_id, permissions, grant_results);
  }

  /**********************************************
   *
   * Permission API
   *
   */

  public String need_explain()
  {
    return TextUtils.join(",", m_permission_manager.need_explain());
  }

  public String need_grant()
  {
    return TextUtils.join(",", m_permission_manager.need_grant());
  }

  public Boolean is_permission_granted(final String permission)
  {
    return m_permission_manager.is_permission_granted(permission);
  }

  public Boolean is_permission_denied(final String permission)
  {
    return m_permission_manager.is_permission_denied(permission);
  }

  public void set_as_explained(String permission)
  {
    m_permission_manager.set_as_explained(permission);
  }

  public void request_permission(String permission)
  {
    m_permission_manager.request_permission(permission);
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

  // public void get_device_id()
  // {
  //    m_phone_helper.get_device_id();
  // }

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
    m_camera_manager.set_torch_mode(enabled);
  }

  // used
  public void perform_lamp_signal(final String encoded_message, final int rate_ms)
  {
    m_camera_manager.perform_lamp_signal(encoded_message, rate_ms);
  }

  public void stop_lamp_signal()
  {
    m_camera_manager.stop_lamp_signal();
  }

  public void start_lamp_dimmer(final int period, final int duty_cycle)
  {
    m_camera_manager.start_lamp_dimmer(period, duty_cycle);
  }

  public void stop_lamp_dimmer()
  {
    m_camera_manager.stop_lamp_dimmer();
  }

  /**********************************************
   *
   * SD Card API
   *
   */

  public String[] get_external_storages()
  {
    File[] files = m_sdcard_helper.get_external_storage();
    String[] paths = new String[files.length];
    for (int i = 0; i < paths.length; i++)
      paths[i] = files[i].getPath();
    return paths;
  }

  public boolean is_external_storage_writable()
  {
     return m_sdcard_helper.is_external_storage_writable();
  }

  public boolean is_external_storage_readable()
  {
    return m_sdcard_helper.is_external_storage_readable();
  }
}
