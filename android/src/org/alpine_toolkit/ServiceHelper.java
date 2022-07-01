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

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;

/**************************************************************************************************/

public class ServiceHelper
{
  private static final String LOG_TAG = Constants.LOG.TAG;

  private static AlpineToolkitActivity m_activity;

  /**********************************************/

  public ServiceHelper(AlpineToolkitActivity activity)
  {
    m_activity = activity;
  }

  /**********************************************/

  public boolean is_service_running()
  {
    String service_name = AlpineToolkitService.class.getName();
    // String service_name = "org.alpine_toolkit.AlpineToolkitService";
    // ActivityManager activity_manager = m_activity.getSystemService(ActivityManager); // require API 23
    ActivityManager activity_manager = (ActivityManager) m_activity.getSystemService(Context.ACTIVITY_SERVICE);
    for (ActivityManager.RunningServiceInfo running_service : activity_manager.getRunningServices(Integer.MAX_VALUE)) {
      String running_service_name = running_service.service.getClassName();
      // Log.i(LOG_TAG, running_service_name);
      if (running_service_name.equals(service_name))
        return true;
    }
    return false;
  }
}
