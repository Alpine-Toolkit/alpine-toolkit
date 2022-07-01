/***************************************************************************************************
**
 * This file is part of the Alpine Toolkit software.
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 * SPDX-License-Identifier: GPL-3.0-only
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
public class CameraManagerIcs extends CameraManagerBase
{
  private Camera m_camera = null;
  private Camera.Parameters m_camera_parameters = null;
  private Boolean m_has_flash = false;

  /**********************************************/

  public CameraManagerIcs(AlpineToolkitActivity activity)
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

    if (!m_has_flash || m_torch_enabled == enabled || m_camera == null)
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

    if (!m_has_flash || m_torch_enabled == enabled)
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
