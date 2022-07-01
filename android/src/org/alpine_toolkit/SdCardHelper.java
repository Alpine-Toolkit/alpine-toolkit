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

import android.os.Environment;

import android.support.v4.content.ContextCompat;

import java.io.File;

/**************************************************************************************************/

public class SdCardHelper
{
  private static final String LOG_TAG = Constants.LOG.TAG;

  private static AlpineToolkitActivity m_activity;

  /**********************************************/

  public SdCardHelper(AlpineToolkitActivity activity)
  {
    m_activity = activity;
  }

  /**********************************************/

  static public File[] get_external_storage()
  {
    return ContextCompat.getExternalFilesDirs(m_activity, null);
  }

  /* Checks if external storage is available for read and write */
  static public boolean is_external_storage_writable()
  {
    String state = Environment.getExternalStorageState();
      return Environment.MEDIA_MOUNTED.equals(state);
  }

  /* Checks if external storage is available to at least read */
  static public boolean is_external_storage_readable()
  {
    String state = Environment.getExternalStorageState();
      return Environment.MEDIA_MOUNTED.equals(state) ||
              Environment.MEDIA_MOUNTED_READ_ONLY.equals(state);
  }
}
