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

import android.annotation.TargetApi;
import android.content.Context;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCharacteristics; // added in API level 21
import android.hardware.camera2.CameraManager;
import android.os.Build;

/**************************************************************************************************/

// camera2 API
//   https://medium.com/google-developers/detecting-camera-features-with-camera2-61675bb7d1bf

/*
@TargetApi(Build.VERSION_CODES.LOLLIPOP)
public class CameraManagerLollipop extends BaseCameraManager
{
  see https://github.com/Abhi347/NoobCameraFlash/blob/master/noobcameraflash/src/main/java/com/noob/noobcameraflash/Utilities/CameraUtilLollipop.java
  seems very complicated ...
}
*/

/**************************************************************************************************/

@TargetApi(Build.VERSION_CODES.M)
public class CameraManagerMarshmallow extends CameraManagerBase
{
  private CameraManager m_camera_manager = null;
  private Boolean m_has_flash = false;
  private String m_camera_id = null;

  /**********************************************/

  public CameraManagerMarshmallow(AlpineToolkitActivity activity)
  {
    super(activity);

    try {
      // Note: System services not available to Activities before onCreate()
      m_camera_manager = (CameraManager) m_activity.getSystemService(Context.CAMERA_SERVICE);
      String[] camera_ids = m_camera_manager.getCameraIdList();
      for (String camera_id : camera_ids) {
        CameraCharacteristics camera_characteristics = m_camera_manager.getCameraCharacteristics(camera_id);
        if (camera_characteristics.get(CameraCharacteristics.FLASH_INFO_AVAILABLE)) {
          m_camera_id = camera_id;
          m_has_flash = true;
        }
      }
    } catch (CameraAccessException e) {
    }
  }

  public void set_torch_mode(boolean enabled)
  {
    try {
      m_camera_manager.setTorchMode(m_camera_id, enabled); // added in API level 23
    } catch (CameraAccessException e) {
    }
  }

  public boolean has_flash()
  {
    return m_has_flash;
  }

  public void _open_camera()
  {
  }

  public void _release_camera()
  {
  }

  public void _set_torch_mode_fast(boolean enabled)
  {
    set_torch_mode(enabled);
  }
}
