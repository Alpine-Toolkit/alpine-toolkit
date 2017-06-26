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

import android.app.Notification;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.IBinder;
import android.util.Log;

// import android.support.v4.app.NotificationCompat;

import org.qtproject.qt5.android.bindings.QtService;

/**************************************************************************************************/

/*
 * https://developer.android.com/guide/components/services.html
 */

public class AlpineToolkitService extends QtService
{
  private static final String LOG_TAG = "AlpineToolkitService";
  private static final String STOP_ACTION = "action.stop";

  final int NOTIFICATION_ID = 1; // The identifier for this notification, must not be 0.

  private static BatteryReceiver m_battery_receiver = null; // Fixme: static ???

  public static void start_service(Context ctx)
  {
    Log.i(LOG_TAG, "start_service");
    ctx.startService(new Intent(ctx, AlpineToolkitService.class));
  }

  public static void stop_service(Context ctx)
  {
    Log.i(LOG_TAG, "stop_service");
    ctx.stopService(new Intent(ctx, AlpineToolkitService.class));
  }

  @Override
  public void onCreate()
  {
    Log.i(LOG_TAG, "onCreate");
    super.onCreate();

    if (m_battery_receiver == null) { // Fixme: ???
      m_battery_receiver = new BatteryReceiver();
      IntentFilter intent_filter = new IntentFilter();
      intent_filter.addAction(Intent.ACTION_BATTERY_CHANGED);
      intent_filter.addAction(Intent.ACTION_POWER_CONNECTED);
      intent_filter.addAction(Intent.ACTION_POWER_DISCONNECTED);
      intent_filter.addAction(Intent.ACTION_BATTERY_LOW);
      intent_filter.addAction(Intent.ACTION_BATTERY_OKAY);
      registerReceiver(m_battery_receiver, intent_filter);
    }
  }

  @Override
  public int onStartCommand(Intent intent, int flags, int start_id)
  {
    String action = intent.getAction();
    Log.i(LOG_TAG, "onStartCommand " + action);
    if (action != null) {
      if (action.equals(STOP_ACTION))
        stop_foreground_service();
    } else // null
      start_foreground_service();
    return super.onStartCommand(intent, flags, start_id);
  }

  @Override
  public void onDestroy()
  {
    Log.i(LOG_TAG, "onDestroy");
    super.onDestroy();

    if (m_battery_receiver != null) {
      unregisterReceiver(m_battery_receiver);
      m_battery_receiver = null;
    }
  }

  @Override
  public IBinder onBind(Intent intent)
  {
    Log.i(LOG_TAG, "onBind");
    return super.onBind(intent);
    // Used only in case of bound services.
    // return null;
  }

  private void start_foreground_service()
  {
    Log.i(LOG_TAG, "start_foreground_service");
    // cf. https://developer.android.com/guide/components/services.html#Foreground
    // Make this service run in the foreground, supplying the ongoing notification to be shown to the user while in this state.
    startForeground(NOTIFICATION_ID, build_notification());
  }

  private void stop_foreground_service()
  {
    Log.i(LOG_TAG, "stop_foreground_service");
    stopForeground(true);
    NativeFunctions.stop_service();
    // stopSelf();
  }

  private Notification build_notification()
  {
    Intent notification_intent = new Intent(this, AlpineToolkitActivity.class);
    // notification_intent.setAction(Constants.ACTION.MAIN);
    // notification_intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
    PendingIntent pending_intent = PendingIntent.getActivity(this, 0, notification_intent, 0);

    Intent stop_intent = new Intent(this, AlpineToolkitService.class);
    stop_intent.setAction(STOP_ACTION);
    PendingIntent pending_stop_intent = PendingIntent.getService(this, 0, stop_intent, 0);

    int icon_id = getResources().getIdentifier("icon", "drawable", getPackageName());
    int icon_transparent_id = getResources().getIdentifier("icon_transparent", "drawable", getPackageName());
    Bitmap icon = BitmapFactory.decodeResource(getResources(), icon_id);

    // return new NotificationCompat.Builder(this)
    return new Notification.Builder(this)
      .setPriority(Notification.PRIORITY_MAX)
      .setContentTitle("Alpine Toolkit Service")
      .setTicker("Alpine Toolkit Service is started") // Set the text that is displayed in the status bar when the notification first arrives.
      .setContentText("Hello!")
      .setSmallIcon(icon_transparent_id)
      .setLargeIcon(Bitmap.createScaledBitmap(icon, 128, 128, false))
      .setContentIntent(pending_intent) // Supply a PendingIntent to send when the notification is clicked.
      .setOngoing(true) //  Ongoing notifications cannot be dismissed by the user
      .addAction(android.R.drawable.ic_media_pause, "Stop", pending_stop_intent) // ic_media_stop
      .build();
  }
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
