/***************************************************************************************************
**
** $QTCARTO_BEGIN_LICENSE:GPL3$
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
** $QTCARTO_END_LICENSE$
**
***************************************************************************************************/

/**************************************************************************************************/

package org.alpine_toolkit;

import android.app.ActivityManager; // API 23 !!!
import android.content.Context;
import android.util.Log;

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

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
