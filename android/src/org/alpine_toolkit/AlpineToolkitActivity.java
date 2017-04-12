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

import java.lang.Character;
import java.lang.reflect.Method;

import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.hardware.Camera;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.PowerManager;
import android.provider.Settings;
import android.telephony.TelephonyManager;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;

import org.qtproject.qt5.android.bindings.QtActivity;

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

  private PowerManager.WakeLock m_wave_lock = null;

  private Camera m_camera = null;
  private Camera.Parameters m_camera_parameters = null;
  private boolean m_torch_enabled = false;

  /**********************************************/

  public AlpineToolkitActivity()
  {
    m_instance = this;
  }

  /**********************************************/

  @Override
  public void onCreate(Bundle savedInstanceState)
  {
    Log.i(LOG_TAG, ">>>>>>>>>> AlpineToolkitActivity.onCreate <<<<<<<<<<");

    // Fixme: hardcoded
    set_status_bar_background_color(Color.parseColor("#3949ab"));

    super.onCreate(savedInstanceState);

    // get_display_metrics();
    // get_device_id();
    // set_torch_mode(true);
  }

  @Override
  protected void onDestroy() {
    release_camera();
    super.onDestroy();
  }

  /**********************************************/

  public void get_display_metrics()
  {
    DisplayMetrics metrics = new DisplayMetrics();
    getWindowManager().getDefaultDisplay().getMetrics(metrics);
    // I/AlpineToolkitActivity(19529): height width px: 1920 1080
    // I/AlpineToolkitActivity(19529): x y DPI: 422.03 424.069
    // I/AlpineToolkitActivity(19529): density DPI: 480       // screen density DENSITY_XXHIGH
    // I/AlpineToolkitActivity(19529): density: 3.0           // logical density of the display
    // I/AlpineToolkitActivity(19529): scaled density: 3.0    // A scaling factor for fonts displayed on the display
    // 423 dpi / 160 dpi = 2.64
    // 480 / 160 = 3
    Log.i(LOG_TAG, "height width px: " + metrics.heightPixels + " " + metrics.widthPixels);
    Log.i(LOG_TAG, "x y DPI: " + metrics.xdpi + " " + metrics.ydpi);
    Log.i(LOG_TAG, "density: " + metrics.density);
    Log.i(LOG_TAG, "density DPI: " + metrics.densityDpi);
    Log.i(LOG_TAG, "scaled density: " + metrics.scaledDensity);
  }

  /**********************************************/

  public void set_status_bar_background_color(int color)
  {
    if (Build.VERSION.SDK_INT >= 21) {
      Window window = getWindow();

      // original code, works on Lollipop SDKs
      // window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
      // window.clearFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
      // window.setStatusBarColor(getResources().getColor(YOUR_COLOR));

      try {
	// Flag indicating that this Window is responsible for drawing the background for the system bars.
	// to work on old SDKs
	// int FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS = 0x80000000;
	window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
	window.clearFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);

	Class<?> cls = window.getClass();
	Method method = cls.getDeclaredMethod("setStatusBarColor", new Class<?>[] { Integer.TYPE });
	method.invoke(window, color);
      } catch (Exception e) {
	// upgrade your SDK and ADT
      }
    }
  }

  /**********************************************/

  // SCREEN_ORIENTATION_BEHIND
  // SCREEN_ORIENTATION_FULL_SENSOR
  // SCREEN_ORIENTATION_FULL_USER
  // SCREEN_ORIENTATION_LANDSCAPE
  // SCREEN_ORIENTATION_LOCKED
  // SCREEN_ORIENTATION_NOSENSOR
  // SCREEN_ORIENTATION_PORTRAIT
  // SCREEN_ORIENTATION_REVERSE_LANDSCAPE
  // SCREEN_ORIENTATION_REVERSE_PORTRAIT
  // SCREEN_ORIENTATION_SENSOR
  // SCREEN_ORIENTATION_SENSOR_LANDSCAPE
  // SCREEN_ORIENTATION_SENSOR_PORTRAIT
  // SCREEN_ORIENTATION_UNSPECIFIED
  // SCREEN_ORIENTATION_USER
  // SCREEN_ORIENTATION_USER_LANDSCAPE
  // SCREEN_ORIENTATION_USER_PORTRAIT

  public void lock_orientation()
  {
    Log.i(LOG_TAG, "lock_orientation");
    this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LOCKED);
  }

  public void unlock_orientation()
  {
    Log.i(LOG_TAG, "unlock_orientation");
    this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR);
  }

  public void request_sensor_orientation()
  {
    Log.i(LOG_TAG, "request_sensor_orientation");
    this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR);
  }

  public void request_portrait_orientation()
  {
    Log.i(LOG_TAG, "request_portrait_orientation");
    this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
  }

  public void request_landscape_orientation()
  {
    Log.i(LOG_TAG, "request_landscape_orientation");
    this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
  }

  /**********************************************/

  public void get_device_id()
  {
    // cf. http://developer.samsung.com/technical-doc/view.do?v=T000000103

    // I/AlpineToolkitActivity(11407): IMEI: 3534140...
    // I/AlpineToolkitActivity(11407): IMSI: 2080153...
    // I/AlpineToolkitActivity(11407): Serial No: a9e...
    // I/AlpineToolkitActivity(11407): Andoid ID: 48a433...

    String imei_string = null;
    String imsi_string = null;
    String serial_number = null;
    String android_id = null;

    // Android devices should have telephony services
    // require READ_PHONE_STATE permission
    TelephonyManager telephonyManager = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE);

    // Mac Address
    // Wifi must be turned on

    /*
     * getDeviceId() function Returns the unique device ID.
     * for example, the IMEI for GSM and the MEID or ESN for CDMA phones.
     */
    imei_string = telephonyManager.getDeviceId();
    if (imei_string != null)
      Log.i(LOG_TAG, "IMEI: " + imei_string);

    /*
     * getSubscriberId() function Returns the unique subscriber ID.
     * for example, the IMSI for a GSM phone.
     */
    imsi_string = telephonyManager.getSubscriberId();
    if (imsi_string != null)
    Log.i(LOG_TAG, "IMSI: " + imsi_string);

    /*
     * Returns the serial number as unique number
     * Works for Android 2.3 and above
     */
    // Serial Number is not available with all android devices
    // serial_number = System.getProperty("ro.serialno");
    try {
      Class<?> c = Class.forName("android.os.SystemProperties"); // API is hidden
      Method get = c.getMethod("get", String.class, String.class);
      serial_number = (String) (get.invoke(c, "ro.serialno", "unknown"));
    }
    catch (Exception ignored) {
    }
    if (serial_number != null)
      Log.i(LOG_TAG, "Serial No: " + serial_number);

    /*
     * Returns the unique DeviceID
     * Works for Android 2.2 and above
     */
    // The value may change if a factory reset is performed on the device.
    // Also, there has been at least one widely-observed bug in a popular handset from a major manufacturer, where every instance has the same ANDROID_ID.
    android_id = Settings.Secure.getString(getContentResolver(), Settings.Secure.ANDROID_ID);
    if (android_id != null)
      Log.i(LOG_TAG, "Andoid ID: " + android_id);
  }

  /**********************************************/

  public void issue_call(String phone_number)
  {
    // Note: this Intent cannot be used to call emergency numbers.
    // Applications can dial emergency numbers using ACTION_DIAL, however.
    Log.i(LOG_TAG, "Issue call: " + phone_number);
    Intent call_intent = new Intent(Intent.ACTION_CALL);
    call_intent.setData(Uri.parse("tel:" + phone_number));
    startActivity(call_intent); // CALL_PHONE Permission
  }

  public void issue_dial(String phone_number)
  {
    Log.i(LOG_TAG, "Issue dial: " + phone_number);
    Intent call_intent = new Intent(Intent.ACTION_DIAL);
    call_intent.setData(Uri.parse("tel:" + phone_number));
    startActivity(call_intent);
  }

  /**********************************************/

  public void acquire_full_wake_lock()
  {
    // Keep screen bright
    // http://developer.android.com/reference/android/os/PowerManager.html
    PowerManager power_manager = (PowerManager) getSystemService(Context.POWER_SERVICE);
    m_wave_lock = power_manager.newWakeLock(PowerManager.FULL_WAKE_LOCK
					    | PowerManager.ACQUIRE_CAUSES_WAKEUP
					    | PowerManager.ON_AFTER_RELEASE,
					    "AlpineToolkitActivity full wake lock");
    m_wave_lock.acquire();
  };

  public void release_full_wake_lock() {
    m_wave_lock.release();
    m_wave_lock = null;
  };

  /**********************************************/

  /* Checks if external storage is available for read and write */
  public boolean isExternalStorageWritable()
  {
    String state = Environment.getExternalStorageState();
    if (Environment.MEDIA_MOUNTED.equals(state)) {
      return true;
    }
    return false;
  }

  /* Checks if external storage is available to at least read */
  public boolean isExternalStorageReadable()
  {
    String state = Environment.getExternalStorageState();
    if (Environment.MEDIA_MOUNTED.equals(state) ||
        Environment.MEDIA_MOUNTED_READ_ONLY.equals(state)) {
      return true;
    }
    return false;
  }

  /**********************************************/

  private boolean has_flash()
  {
    PackageManager package_manager = getPackageManager();
    boolean has_flash = package_manager.hasSystemFeature(PackageManager.FEATURE_CAMERA_FLASH);
    // Log.i(LOG_TAG, "has_flash: " + has_flash);
    return has_flash;
  }

  private void open_camera()
  {
    if (m_camera == null) {
      try {
	Log.i(LOG_TAG, "open_camera");
	// Open back-facing camera on a device with more than one camera
	m_camera = Camera.open();
	m_camera_parameters = m_camera.getParameters();
      } catch (Exception e) {
	// Camera is not available (in use or does not exist)
	// Fixme:
      }
    }
  }

  private void release_camera()
  {
    if (m_camera != null) {
      Log.i(LOG_TAG, "release_camera");
      m_camera.stopPreview();
      m_camera.release();
      m_camera = null;
    }
  }

  private void _set_torch_mode(boolean enabled)
  {
    if (m_torch_enabled != enabled) {
      // Log.i(LOG_TAG, "_set_torch_mode: " + enabled);
      if (m_camera != null) {
	String flash_mode = enabled ? Camera.Parameters.FLASH_MODE_TORCH : Camera.Parameters.FLASH_MODE_OFF;
	m_camera_parameters.setFlashMode(flash_mode);
	m_camera.setParameters(m_camera_parameters);
	if (enabled)
	  m_camera.startPreview();
	else
	  m_camera.stopPreview();
	m_torch_enabled = enabled;
      }
    }

    // CameraManager manager = (CameraManager) getSystemService(Context.CAMERA_SERVICE);
    // try {
    //   for (String camera_id : manager.getCameraIdList()) {
    // 	Log.i(LOG_TAG, "camera_id: " + camera_id);
    // 	// CameraCharacteristics camera_characteristics = manager.getCameraCharacteristics (camera_id);
    // 	// if (! camera_characteristics.get("FLASH_STATE_UNAVAILABLE"))
    // 	// 	manager.setTorchMode(camera_id, enabled);
    //   }
    // } catch (Exception e) { // CameraAccessException
    // }
  }

  private void _enable_torch()
  {
    _set_torch_mode(true);
  }

  private void _disable_torch()
  {
    _set_torch_mode(false);
  }

  public void set_torch_mode(boolean enabled)
  {
    Log.i(LOG_TAG, "set_torch_mode: " + enabled);
    if (m_torch_enabled != enabled) {
      if (enabled) {
	if (has_flash()) {
	  open_camera();
	  _enable_torch();
	}
      } else {
	_disable_torch();
	release_camera();
      }
    }
  }

  /*
  public void perform_lamp_signal(final String encoded_message, final int rate_ms) {
    Log.i(LOG_TAG, "perform_lamp_signal: " + encoded_message + " " + rate_ms);
    if (has_flash()) {
      // Fixme: camera vs thread ???
      // Fixme: stop thread
      new Thread(new Runnable() {
	  @Override
	  public void run() {
	    Log.i(LOG_TAG, "perform_lamp_signal run");
	    open_camera();
	    for (char bit : encoded_message.toCharArray()) {
	      // Log.i(LOG_TAG, "perform_lamp_signal bit: " + bit);
	      if (bit == '1')
		_enable_torch();
	      else
		_disable_torch();
	      try {
		Thread.sleep(rate_ms); // 1/4 s = 250 ms
	      } catch (InterruptedException exception) {
		// Fixme: disable torch ???
		exception.printStackTrace();
	      }
	    }
	    release_camera();
	  }
	}).start();
    }
  }
  */

  public void perform_lamp_signal(final String encoded_message, final int rate_ms)
  {
    Log.i(LOG_TAG, "perform_lamp_signal: " + encoded_message + " " + rate_ms);
    if (has_flash()) {
      // Fixme: camera vs thread ???
      // Fixme: stop thread
      new Thread(new Runnable() {
	  @Override
	  public void run() {
	    // Log.i(LOG_TAG, "perform_lamp_signal run");
	    open_camera();
            _disable_torch(); // else don't turn on first time
	    boolean is_on = true;
	    for (char run : encoded_message.toCharArray()) {
	      int multiple = Character.digit(run, 10); // (int)c - (int)'0'
	      // Log.i(LOG_TAG, "perform_lamp_signal run: " + multiple + " " + is_on);
	      if (is_on)
		_enable_torch();
	      else
		_disable_torch();
	      is_on = !is_on;
	      try {
		Thread.sleep(rate_ms * multiple);
	      } catch (InterruptedException exception) {
		// Fixme: disable torch ???
		exception.printStackTrace();
	      }
	    }
	    release_camera();
	  }
	}).start();
    }
  }
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
