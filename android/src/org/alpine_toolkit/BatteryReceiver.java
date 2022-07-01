/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
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
    int percent = (int) (100 * level / (float) scale);

    String message = String.format("Battery receiver: %1$s %2$s %3$d ", is_charging, charge_plug, percent);
    Log.i(LOG_TAG, message);

    // call c++
  }
}
