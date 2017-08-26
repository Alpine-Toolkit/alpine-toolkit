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

package org.alpine_toolkit.Camera;

import org.alpine_toolkit.AlpineToolkitActivity;
import org.alpine_toolkit.Constants;

import android.util.Log;
import java.lang.Character;

/**************************************************************************************************/

// THI05-J. Do not use Thread.stop() to terminate threads
// https://www.securecoding.cert.org/confluence/display/java/THI05-J.+Do+not+use+Thread.stop%28%29+to+terminate+threads

/**************************************************************************************************/

/*
class LampSignalRunnable implements Runnable {
  @Override
  public void run() {
    android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_BACKGROUND);
  }
}
*/

/**************************************************************************************************/

/**************************************************************************************************/

public abstract class CameraManagerBase implements CameraManagerInterface
{
  protected static final String LOG_TAG = Constants.LOG.TAG;
  protected static AlpineToolkitActivity m_activity;
  protected boolean m_torch_enabled = false;

  private Thread m_lamp_signal_thread = null;
  private Thread m_dimmer_thread = null;

  /**********************************************/

  public CameraManagerBase(AlpineToolkitActivity activity)
  {
    m_activity = activity;
  }

  /**********************************************/

  public void _enable_torch()
  {
    _set_torch_mode_fast(true);
  }

  public void _disable_torch()
  {
    _set_torch_mode_fast(false);
  }

  /**********************************************/

  private final class LampSignalRunnable implements Runnable
  {
    private String m_encoded_message;
    private int m_rate_ms;

    public LampSignalRunnable(String encoded_message, int rate_ms)
    {
      m_encoded_message = encoded_message;
      m_rate_ms = rate_ms;
    }

    @Override
    public synchronized void run() {
      // Log.i(LOG_TAG, "perform_lamp_signal run");

      _open_camera();
      _disable_torch(); // else don't turn on first time

      // for (char bit : encoded_message.toCharArray()) {
      //   // Log.i(LOG_TAG, "perform_lamp_signal bit: " + bit);
      //   if (bit == '1')
      //     _enable_torch();
      //   else
      //     _disable_torch();
      //   try {
      //     Thread.sleep(rate_ms); // 1/4 s = 250 ms
      //   } catch (InterruptedException exception) {
      //     // Fixme: disable torch ???
      //     exception.printStackTrace();
      //   }
      // }

      boolean is_on = true;
      for (char run : m_encoded_message.toCharArray()) {
        int multiple = Character.digit(run, 10); // (int)c - (int)'0'
        // Log.i(LOG_TAG, "perform_lamp_signal run: " + multiple + " " + is_on);
        if (is_on)
          _enable_torch();
        else
          _disable_torch();
        is_on = !is_on;
        try {
          Thread.sleep(m_rate_ms * multiple);
        } catch (InterruptedException e) {
          // Fixme: when ???
          break;
        }
      }

      _release_camera();
      m_lamp_signal_thread = null;
    }
  }

  public void perform_lamp_signal(final String encoded_message, final int rate_ms)
  {
    Log.i(LOG_TAG, "perform_lamp_signal: " + encoded_message + " " + rate_ms);

    if (! has_flash())
      return;

    m_lamp_signal_thread = new Thread(new LampSignalRunnable(encoded_message, rate_ms));
    m_lamp_signal_thread.start();
  }

  public void stop_lamp_signal()
  {
    if (m_lamp_signal_thread != null) {
      m_lamp_signal_thread.interrupt();
      m_lamp_signal_thread = null;
    }
  }

  /**********************************************/

  private final class DimmerRunnable implements Runnable
  {
    int m_period; // ms
    int m_duty_cycle; // %
    int m_on_time;
    int m_off_time;

    DimmerRunnable(final int periods, final int duty_cycle)
    {
      m_period = periods;
      m_duty_cycle = duty_cycle;

      m_on_time = m_period * m_duty_cycle / 100;
      m_off_time = m_period - m_on_time;
    }

    @Override
    public synchronized void run() {
      _open_camera();
      _disable_torch(); // else don't turn on first time

      boolean is_on = true;
      while (!Thread.interrupted()) {
        if (is_on)
          _enable_torch();
        else
          _disable_torch();
        try {
          Thread.sleep(is_on ? m_on_time : m_off_time);
        } catch (InterruptedException e) {
          // Fixme: when ???
        }
        is_on = !is_on;
      }

      _release_camera();
    }
  }

  public void start_lamp_dimmer(final int period, final int duty_cycle)
  {
    Log.i(LOG_TAG, "start_lamp_dimmer: " + period + " " + duty_cycle);

    if (! has_flash())
      return;

    stop_lamp_dimmer();

    m_dimmer_thread = new Thread(new DimmerRunnable(period, duty_cycle));
    m_dimmer_thread.start();
  }

  public void stop_lamp_dimmer()
  {
    if (m_dimmer_thread != null) {
      m_dimmer_thread.interrupt();
      m_dimmer_thread = null;
    }
  }
}
