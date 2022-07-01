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

import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.AssetManager;
import android.content.res.Resources;
import android.util.Log;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

/**************************************************************************************************/

public class AssetHelper
{
  private static final String LOG_TAG = Constants.LOG.TAG;

  private static final String ASSET_VERSION = "asset_version";

  private AlpineToolkitActivity m_activity;
  private AssetManager m_asset_manager;

  /**********************************************/

  public AssetHelper(AlpineToolkitActivity activity)
  {
    m_activity = activity;
    m_asset_manager = m_activity.getAssets();
  }

  public void copy_assets(String asset_path, boolean force)
  {
    Resources resources = m_activity.getResources();
    int asset_version = resources.getInteger(R.integer.asset_version);

    SharedPreferences preferences = m_activity.getPreferences(Context.MODE_PRIVATE);
    int saved_asset_version = preferences.getInt(ASSET_VERSION, 0);
    Log.i(LOG_TAG, "Asset Version: " + asset_version + " Saved: " + saved_asset_version);

    if (saved_asset_version != asset_version || force) {
      FileHelper.delete_directory(new File(asset_path));

      // Files are listed in res/startup.xml
      String[] assets_to_move = resources.getStringArray(R.array.assets_to_move);
      boolean rc = true;
      for (String from_path : assets_to_move) {
        String to_path = asset_path + '/' + from_path;
        rc &= _copy_asset(from_path, to_path);
      }
      if (rc) {
        SharedPreferences.Editor editor = preferences.edit();
        editor.putInt(ASSET_VERSION, asset_version);
        editor.apply();
      } else {
        Log.i(LOG_TAG, "Failed to copy assets");
      }
    }
  }

  private boolean _copy_asset(String from_path, String to_path)
  {
    Log.i(LOG_TAG, "Copy asset " + from_path + " -> " + to_path);
    try {
      new File(to_path).getParentFile().mkdirs();
      InputStream input = m_asset_manager.open(from_path); // throw IOException
      OutputStream output = new FileOutputStream(to_path);
      FileHelper.copy_file(input, output);
      input.close();
      output.flush();
      output.close();
      return true;
    } catch(Exception e) {
      Log.i(LOG_TAG, "Failed to Copy asset " + from_path + " -> " + to_path);
      e.printStackTrace();
      return false;
    }
  }

  /*
  private boolean copy_asset_folder(String from_path, String to_path)
  {
    try {
      String[] files = m_asset_manager.list(from_path);
      new File(to_path).mkdirs(); // Fixme: rc
      boolean rc = true;
      for (String file : files)
        // if file is directory ???
        rc &= copy_asset(from_path + "/" + file, to_path + "/" + file);
      return rc;
    } catch (Exception e) {
      e.printStackTrace();
      return false;
    }
  }
  */
}
