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
