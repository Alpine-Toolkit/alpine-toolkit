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

/**************************************************************************************************/

public interface CameraManagerInterface
{
  boolean has_flash(); // always inverted
  void set_torch_mode(boolean enabled);

  void _set_torch_mode_fast(boolean enabled);
  void _open_camera();
  void _release_camera(); // Fixme: called in Activity
}
