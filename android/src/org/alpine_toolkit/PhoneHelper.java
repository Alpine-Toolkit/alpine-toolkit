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

import java.lang.reflect.Method;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.provider.Settings;
import android.telephony.TelephonyManager;
import android.util.Log;

/**************************************************************************************************/

public class PhoneHelper
{
  private static final String LOG_TAG = Constants.LOG.TAG;

  private static AlpineToolkitActivity m_activity;

  /**********************************************/

  public PhoneHelper(AlpineToolkitActivity activity)
  {
    m_activity = activity;
  }

  /**********************************************/

  // public void get_device_id()
  // {
  //   // cf. http://developer.samsung.com/technical-doc/view.do?v=T000000103
  //
  //   // I/AlpineToolkitActivity(11407): IMEI: 3534140...
  //   // I/AlpineToolkitActivity(11407): IMSI: 2080153...
  //   // I/AlpineToolkitActivity(11407): Serial No: a9e...
  //   // I/AlpineToolkitActivity(11407): Andoid ID: 48a433...
  //
  //   String imei_string = null;
  //   String imsi_string = null;
  //   String serial_number = null;
  //   String android_id = null;
  //
  //   // Android devices should have telephony services
  //   // require READ_PHONE_STATE permission
  //   TelephonyManager telephonyManager = (TelephonyManager) m_activity.getSystemService(Context.TELEPHONY_SERVICE);
  //
  //   // Mac Address
  //   // Wifi must be turned on
  //
  //   /*
  //    * getDeviceId() function Returns the unique device ID.
  //    * for example, the IMEI for GSM and the MEID or ESN for CDMA phones.
  //    */
  //   imei_string = telephonyManager.getDeviceId(); // not recommended !
  //   if (imei_string != null)
  //     Log.i(LOG_TAG, "IMEI: " + imei_string);
  //
  //   /*
  //    * getSubscriberId() function Returns the unique subscriber ID.
  //    * for example, the IMSI for a GSM phone.
  //    */
  //   imsi_string = telephonyManager.getSubscriberId(); // not recommended !
  //   if (imsi_string != null)
  //   Log.i(LOG_TAG, "IMSI: " + imsi_string);
  //
  //   /*
  //    * Returns the serial number as unique number
  //    * Works for Android 2.3 and above
  //    */
  //   // Serial Number is not available with all android devices
  //   // serial_number = System.getProperty("ro.serialno");
  //   try {
  //     Class<?> c = Class.forName("android.os.SystemProperties"); // API is hidden
  //     Method get = c.getMethod("get", String.class, String.class);
  //     serial_number = (String) (get.invoke(c, "ro.serialno", "unknown")); // not recommended !
  //   }
  //   catch (Exception ignored) {
  //   }
  //   if (serial_number != null)
  //     Log.i(LOG_TAG, "Serial No: " + serial_number);
  //
  //   /*
  //    * Returns the unique DeviceID
  //    * Works for Android 2.2 and above
  //    */
  //   // The value may change if a factory reset is performed on the device.
  //   // Also, there has been at least one widely-observed bug in a popular handset from a major manufacturer, where every instance has the same ANDROID_ID.
  //   android_id = Settings.Secure.getString(m_activity.getContentResolver(), Settings.Secure.ANDROID_ID); // not recommended !
  //   if (android_id != null)
  //     Log.i(LOG_TAG, "Andoid ID: " + android_id);
  // }

  /**********************************************/

  public void issue_call(String phone_number)
  {
    // Note: this Intent cannot be used to call emergency numbers.
    // Applications can dial emergency numbers using ACTION_DIAL, however.
    Log.i(LOG_TAG, "Issue call: " + phone_number);
    Intent call_intent = new Intent(Intent.ACTION_CALL);
    call_intent.setData(Uri.parse("tel:" + phone_number));
    m_activity.startActivity(call_intent); // require CALL_PHONE Permission
  }

  public void issue_dial(String phone_number)
  {
    Log.i(LOG_TAG, "Issue dial: " + phone_number);
    Intent call_intent = new Intent(Intent.ACTION_DIAL);
    call_intent.setData(Uri.parse("tel:" + phone_number));
    m_activity.startActivity(call_intent);
  }
}
