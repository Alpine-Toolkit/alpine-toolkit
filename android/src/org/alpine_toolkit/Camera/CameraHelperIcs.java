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

package org.alpine_toolkit.Camera;

import org.alpine_toolkit.AlpineToolkitActivity;

import android.content.pm.PackageManager;
import android.hardware.Camera;
import android.util.Log;

/**************************************************************************************************/

@SuppressWarnings("deprecation")
public class CameraHelperIcs extends CameraHelperBase
{
  private Camera m_camera = null;
  private Camera.Parameters m_camera_parameters = null;
  private Boolean m_has_flash = false;

  /**********************************************/

  public CameraHelperIcs(AlpineToolkitActivity activity)
  {
    super(activity);

    PackageManager package_manager = m_activity.getPackageManager();
    m_has_flash = package_manager.hasSystemFeature(PackageManager.FEATURE_CAMERA_FLASH);
    // Log.i(LOG_TAG, "has_flash: " + m_has_flash);
  }

  /**********************************************/

  public boolean has_flash()
  {
    return m_has_flash;
  }

  public void _open_camera()
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

  public void _release_camera()
  {
    if (m_camera != null) {
      Log.i(LOG_TAG, "release_camera");
      m_camera.stopPreview();
      m_camera.release();
      m_camera = null;
    }
  }

  public void _set_torch_mode_fast(boolean enabled)
  {
    // Log.i(LOG_TAG, "_set_torch_mode: " + enabled);

    if (m_has_flash == false || m_torch_enabled == enabled || m_camera == null)
      return;

    String flash_mode = enabled ? Camera.Parameters.FLASH_MODE_TORCH : Camera.Parameters.FLASH_MODE_OFF;
    m_camera_parameters.setFlashMode(flash_mode);
    m_camera.setParameters(m_camera_parameters);

    if (enabled)
      m_camera.startPreview();
    else
      m_camera.stopPreview();

    m_torch_enabled = enabled;
  }

  // Set torch mode : open / release camera
  public void set_torch_mode(boolean enabled)
  {
    Log.i(LOG_TAG, "set_torch_mode: " + enabled);

    if (m_has_flash == false || m_torch_enabled == enabled)
      return;

    if (enabled) {
      _open_camera();
      _enable_torch();
    } else {
      _disable_torch();
      _release_camera();
    }
  }
}
