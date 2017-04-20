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

import android.content.pm.PackageManager;
import android.hardware.Camera;
import android.util.Log;
import java.lang.Character;

/**************************************************************************************************/

// class LampSignalRunnable implements Runnable {
//   @Override
//   public void run() {
//     android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_BACKGROUND);
//   }
// }

/**************************************************************************************************/

public class CameraHelper
{
  private static final String LOG_TAG = Constants.LOG.TAG;

  private static AlpineToolkitActivity m_activity;

  private Camera m_camera = null; // deprecated aPI
  private Camera.Parameters m_camera_parameters = null;
  private boolean m_torch_enabled = false;

  /**********************************************/

  public CameraHelper(AlpineToolkitActivity activity)
  {
    m_activity = activity;
  }

  /**********************************************/

  private boolean has_flash()
  {
    PackageManager package_manager = m_activity.getPackageManager();
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

  public void release_camera()
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
