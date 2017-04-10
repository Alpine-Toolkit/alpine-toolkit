/**************************************************************************************************/

package org.alpine_toolkit;

import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Environment;
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

  final int SERVICE_ID = 1; // The identifier for this notification, must not be 0.

  public static void start_service(Context ctx) {
    Log.i(LOG_TAG, "start_service");
    ctx.startService(new Intent(ctx, AlpineToolkitService.class));
  }

  public static void stop_service(Context ctx) {
    Log.i(LOG_TAG, "stop_service");
    ctx.stopService(new Intent(ctx, AlpineToolkitService.class));
  }

  @Override
  public void onCreate() {
    Log.i(LOG_TAG, "onCreate");
    super.onCreate();
  }

  @Override
  public int onStartCommand(Intent intent, int flags, int start_id) {
    String action = intent.getAction();
    Log.i(LOG_TAG, "onStartCommand " + action);
    return super.onStartCommand(intent, flags, start_id);
  }

  @Override
  public void onDestroy() {
    Log.i(LOG_TAG, "onDestroy");
    super.onDestroy();
  }

  @Override
  public IBinder onBind(Intent intent) {
    Log.i(LOG_TAG, "onBind");
    return super.onBind(intent);
    // Used only in case of bound services.
    // return null;
  }

  private void start_foreground_service() {
    Log.i(LOG_TAG, "start_foreground_service");
    // cf. https://developer.android.com/guide/components/services.html#Foreground
    // Make this service run in the foreground, supplying the ongoing notification to be shown to the user while in this state.
    // startForeground(NOTIFICATION_ID, build_notification());
  }

  private void stop_foreground_service() {
    Log.i(LOG_TAG, "stop_foreground_service");
    stopForeground(true);
    // stopSelf();
  }

  // private Notification build_notification() {
  //   Intent notification_intent = new Intent(this, AlpineToolkitActivity.class);
  //   // notification_intent.setAction(Constants.ACTION.MAIN);
  //   // notification_intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
  //   PendingIntent pending_intent = PendingIntent.getActivity(this, 0, notification_intent, 0);

  //   Intent stop_intent = new Intent(this, MyService.class);
  //   stop_intent.setAction(Constants.ACTION.STOP);
  //   PendingIntent pending_stop_intent = PendingIntent.getService(this, 0, stop_intent, 0);

  //   Bitmap icon = BitmapFactory.decodeResource(getResources(), R.mipmap.ic_launcher); // R.drawable.xxx

  //   return new NotificationCompat.Builder(this)
  //     .setPriority(Notification.PRIORITY_MAX)
  //     .setContentTitle("Foreground Service")
  //     .setTicker("Foreground Service") // Set the text that is displayed in the status bar when the notification first arrives.
  //     .setContentText("Hello!")
  //     .setSmallIcon(R.mipmap.ic_launcher)
  //     .setLargeIcon(Bitmap.createScaledBitmap(icon, 128, 128, false))
  //     .setContentIntent(pending_intent) // Supply a PendingIntent to send when the notification is clicked.
  //     .setOngoing(true)
  //     .addAction(android.R.drawable.ic_media_pause, "Stop", pending_stop_intent)
  //     .build();
  // }
}

/***************************************************************************************************
 *
 * End
 *
 **************************************************************************************************/
