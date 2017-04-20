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

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.BatteryManager;
import android.util.Log;

/**************************************************************************************************/

public class BatteryReceiver extends BroadcastReceiver
{
  private static final String LOG_TAG = Constants.LOG.TAG;

  @Override
  public void onReceive(Context context, Intent battery_status)
  {
    // Are we charging / charged?
    int status = battery_status.getIntExtra(BatteryManager.EXTRA_STATUS, -1);
    boolean is_charging = status == BatteryManager.BATTERY_STATUS_CHARGING || status == BatteryManager.BATTERY_STATUS_FULL;

    // How are we charging?
    int charge_plug = battery_status.getIntExtra(BatteryManager.EXTRA_PLUGGED, -1);
    boolean usb_charge = charge_plug == BatteryManager.BATTERY_PLUGGED_USB;
    boolean ac_charge = charge_plug == BatteryManager.BATTERY_PLUGGED_AC;

    int level = battery_status.getIntExtra(BatteryManager.EXTRA_LEVEL, -1);
    int scale = battery_status.getIntExtra(BatteryManager.EXTRA_SCALE, -1);
    float percent = level / (float) scale;

    String message = String.format("Battery receiver: %1$s %2$s %3$f ", is_charging, charge_plug, percent);
    Log.i(LOG_TAG, message);

    // call c++
  }
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
