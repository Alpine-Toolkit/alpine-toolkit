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

import java.lang.reflect.Method;

import android.content.Context;
import android.content.pm.ActivityInfo;
import android.os.Build;
import android.os.PowerManager;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;

/**************************************************************************************************/

public class DeviceUserInterfaceHelper
{
  private static final String LOG_TAG = Constants.LOG.TAG;

  private static AlpineToolkitActivity m_activity;

  /**********************************************/

  public DeviceUserInterfaceHelper(AlpineToolkitActivity activity)
  {
    m_activity = activity;
  }

  /**********************************************/

  public void get_display_metrics()
  {
    DisplayMetrics metrics = new DisplayMetrics();
    m_activity.getWindowManager().getDefaultDisplay().getMetrics(metrics);
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
      Window window = m_activity.getWindow();

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
    m_activity.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LOCKED);
  }

  public void unlock_orientation()
  {
    Log.i(LOG_TAG, "unlock_orientation");
    m_activity.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR);
  }

  public void request_sensor_orientation()
  {
    Log.i(LOG_TAG, "request_sensor_orientation");
    m_activity.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR);
  }

  public void request_portrait_orientation()
  {
    Log.i(LOG_TAG, "request_portrait_orientation");
    m_activity.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
  }

  public void request_landscape_orientation()
  {
    Log.i(LOG_TAG, "request_landscape_orientation");
    m_activity.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
  }

  /**********************************************/

  private PowerManager.WakeLock m_wave_lock = null;

  public void acquire_full_wake_lock()
  {
    // Keep screen bright
    // http://developer.android.com/reference/android/os/PowerManager.html
    PowerManager power_manager = (PowerManager) m_activity.getSystemService(Context.POWER_SERVICE);
    m_wave_lock = power_manager.newWakeLock(PowerManager.FULL_WAKE_LOCK
					    | PowerManager.ACQUIRE_CAUSES_WAKEUP
					    | PowerManager.ON_AFTER_RELEASE,
					    "AlpineToolkitActivity full wake lock");
    m_wave_lock.acquire();
  };

  public void release_full_wake_lock()
  {
    m_wave_lock.release();
    m_wave_lock = null;
  };
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
