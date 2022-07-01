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

/**************************************************************************************************/

public class Constants {

  public interface LOG {
    String TAG = "AlpineToolkitActivity";
  }

  public interface UI {
    String BACKGROUND_COLOR = "#3949ab";
  }

  public static final String[] PERMISSIONS = {
    "android.permission.ACCESS_FINE_LOCATION", // need grant
    "android.permission.ACCESS_NETWORK_STATE", // is granted
    "android.permission.CAMERA", // need grant
    "android.permission.FLASHLIGHT", // is granted
    "android.permission.INTERNET", // is granted
    "android.permission.READ_EXTERNAL_STORAGE", // need grant
    "android.permission.WRITE_EXTERNAL_STORAGE", // need grant
    // "android.permission.BODY_SENSORS",
    // "android.permission.READ_PHONE_STATE",
  };
}
