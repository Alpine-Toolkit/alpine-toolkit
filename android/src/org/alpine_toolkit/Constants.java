/***************************************************************************************************
**
** $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
**
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
**
** This file is part of the Alpine Toolkit software.
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
