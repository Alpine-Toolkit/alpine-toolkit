package org.alpha_ursae_minoris;

import java.lang.reflect.Method;

import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.graphics.Color;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.PowerManager;
import android.provider.Settings;
import android.telephony.TelephonyManager;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;

public class AumActivity extends org.qtproject.qt5.android.bindings.QtActivity
{
  private static AumActivity m_instance;

  public AumActivity()
  {
    m_instance = this;
  }

  private PowerManager.WakeLock m_wave_lock = null;

  @Override
  public void onCreate(Bundle savedInstanceState)
  {
    Log.i("AumActivity", ">>>>>>>>>> AumActivity.onCreate <<<<<<<<<<");

    // Fixme: hardcoded
    set_status_bar_background_color(Color.parseColor("#3949ab"));

    super.onCreate(savedInstanceState);

    // get_display_metrics();
    // get_device_id();
  }

  public void get_display_metrics() {
    DisplayMetrics metrics = new DisplayMetrics();
    getWindowManager().getDefaultDisplay().getMetrics(metrics);
    // I/AumActivity(19529): height width px: 1920 1080
    // I/AumActivity(19529): x y DPI: 422.03 424.069
    // I/AumActivity(19529): density DPI: 480       // screen density DENSITY_XXHIGH
    // I/AumActivity(19529): density: 3.0           // logical density of the display
    // I/AumActivity(19529): scaled density: 3.0    // A scaling factor for fonts displayed on the display
    // 423 dpi / 160 dpi = 2.64
    // 480 / 160 = 3
    Log.i("AumActivity", "height width px: " + metrics.heightPixels + " " + metrics.widthPixels);
    Log.i("AumActivity", "x y DPI: " + metrics.xdpi + " " + metrics.ydpi);
    Log.i("AumActivity", "density: " + metrics.density);
    Log.i("AumActivity", "density DPI: " + metrics.densityDpi);
    Log.i("AumActivity", "scaled density: " + metrics.scaledDensity);
  }

  public void set_status_bar_background_color(int color) {
    if (Build.VERSION.SDK_INT >= 21) {
      Window window = getWindow();

      // original code, works on Lollipop SDKs
      // window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
      // window.clearFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
      // window.setStatusBarColor(getResources().getColor(YOUR_COLOR));

      try {
	// Flag indicating that this Window is responsible for drawing the background for the system bars.
	// to work on old SDKs
	// int FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS = 0x80000000;
	window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
	window.clearFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);

	Class<?> cls = window.getClass();
	Method method = cls.getDeclaredMethod("setStatusBarColor", new Class<?>[] { Integer.TYPE });
	method.invoke(window, color);
      } catch (Exception e) {
	// upgrade your SDK and ADT
      }
    }
  }

  // SCREEN_ORIENTATION_BEHIND
  // SCREEN_ORIENTATION_FULL_SENSOR
  // SCREEN_ORIENTATION_FULL_USER
  // SCREEN_ORIENTATION_LANDSCAPE
  // SCREEN_ORIENTATION_LOCKED
  // SCREEN_ORIENTATION_NOSENSOR
  // SCREEN_ORIENTATION_PORTRAIT
  // SCREEN_ORIENTATION_REVERSE_LANDSCAPE
  // SCREEN_ORIENTATION_REVERSE_PORTRAIT
  // SCREEN_ORIENTATION_SENSOR
  // SCREEN_ORIENTATION_SENSOR_LANDSCAPE
  // SCREEN_ORIENTATION_SENSOR_PORTRAIT
  // SCREEN_ORIENTATION_UNSPECIFIED
  // SCREEN_ORIENTATION_USER
  // SCREEN_ORIENTATION_USER_LANDSCAPE
  // SCREEN_ORIENTATION_USER_PORTRAIT

  public void lock_orientation()
  {
    Log.i("AumActivity", "lock_orientation");
    this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LOCKED);
  }

  public void unlock_orientation() {
    Log.i("AumActivity", "unlock_orientation");
    this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR);
  }

  public void request_sensor_orientation() {
    Log.i("AumActivity", "request_sensor_orientation");
    this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR);
  }

  public void request_portrait_orientation() {
    Log.i("AumActivity", "request_portrait_orientation");
    this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
  }

  public void request_landscape_orientation() {
    Log.i("AumActivity", "request_landscape_orientation");
    this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
  }

  public void get_device_id() {
    // cf. http://developer.samsung.com/technical-doc/view.do?v=T000000103

    // I/AumActivity(11407): IMEI: 353414073315588
    // I/AumActivity(11407): IMSI: 208015304147532
    // I/AumActivity(11407): Serial No: a9e91f81
    // I/AumActivity(11407): Andoid ID: 48a43365dba7923e

    String imei_string = null;
    String imsi_string = null;
    String serial_number = null;
    String android_id = null;

    // Android devices should have telephony services
    // require READ_PHONE_STATE permission
    TelephonyManager telephonyManager = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE);

    // Mac Address
    // Wifi must be turned on

    /*
     * getDeviceId() function Returns the unique device ID.
     * for example, the IMEI for GSM and the MEID or ESN for CDMA phones.
     */
    imei_string = telephonyManager.getDeviceId();
    if (imei_string != null)
      Log.i("AumActivity", "IMEI: " + imei_string);

    /*
     * getSubscriberId() function Returns the unique subscriber ID.
     * for example, the IMSI for a GSM phone.
     */
    imsi_string = telephonyManager.getSubscriberId();
    if (imsi_string != null)
    Log.i("AumActivity", "IMSI: " + imsi_string);

    /*
     * Returns the serial number as unique number
     * Works for Android 2.3 and above
     */
    // Serial Number is not available with all android devices
    // serial_number = System.getProperty("ro.serialno");
    try {
      Class<?> c = Class.forName("android.os.SystemProperties"); // API is hidden
      Method get = c.getMethod("get", String.class, String.class);
      serial_number = (String) (get.invoke(c, "ro.serialno", "unknown"));
    }
    catch (Exception ignored) {
    }
    if (serial_number != null)
      Log.i("AumActivity", "Serial No: " + serial_number);

    /*
     * Returns the unique DeviceID
     * Works for Android 2.2 and above
     */
    // The value may change if a factory reset is performed on the device.
    // Also, there has been at least one widely-observed bug in a popular handset from a major manufacturer, where every instance has the same ANDROID_ID.
    android_id = Settings.Secure.getString(getContentResolver(), Settings.Secure.ANDROID_ID);
    if (android_id != null)
      Log.i("AumActivity", "Andoid ID: " + android_id);
  }

  public void issue_call(String phone_number) {
    // Note: this Intent cannot be used to call emergency numbers.
    // Applications can dial emergency numbers using ACTION_DIAL, however.
    Log.i("AumActivity", "Issue call: " + phone_number);
    Intent call_intent = new Intent(Intent.ACTION_CALL);
    call_intent.setData(Uri.parse("tel:" + phone_number));
    startActivity(call_intent);
  }

  public void issue_dial(String phone_number) {
    Log.i("AumActivity", "Issue dial: " + phone_number);
    Intent call_intent = new Intent(Intent.ACTION_DIAL);
    call_intent.setData(Uri.parse("tel:" + phone_number));
    startActivity(call_intent);
  }

  public void acquire_full_wake_lock() {
    // Keep screen bright
    // http://developer.android.com/reference/android/os/PowerManager.html
    PowerManager power_manager = (PowerManager) getSystemService(Context.POWER_SERVICE);
    m_wave_lock = power_manager.newWakeLock(PowerManager.FULL_WAKE_LOCK
					    | PowerManager.ACQUIRE_CAUSES_WAKEUP
					    | PowerManager.ON_AFTER_RELEASE,
					    "AumActivity full wake lock");
    m_wave_lock.acquire();
  };

  public void release_full_wake_lock() {
    m_wave_lock.release();
    m_wave_lock = null;
  };

  /* Checks if external storage is available for read and write */
  public boolean isExternalStorageWritable() {
    String state = Environment.getExternalStorageState();
    if (Environment.MEDIA_MOUNTED.equals(state)) {
      return true;
    }
    return false;
  }

  /* Checks if external storage is available to at least read */
  public boolean isExternalStorageReadable() {
    String state = Environment.getExternalStorageState();
    if (Environment.MEDIA_MOUNTED.equals(state) ||
        Environment.MEDIA_MOUNTED_READ_ONLY.equals(state)) {
      return true;
    }
    return false;
  }
}
