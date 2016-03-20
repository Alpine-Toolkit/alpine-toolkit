package org.alpha_ursae_minoris;

import android.content.pm.ActivityInfo;
import android.util.Log;

public class AumActivity extends org.qtproject.qt5.android.bindings.QtActivity
{
  private static AumActivity m_instance;

  public AumActivity()
  {
    m_instance = this;
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
}
