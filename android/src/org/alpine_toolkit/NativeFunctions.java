/**************************************************************************************************/

package org.alpine_toolkit;

/**************************************************************************************************/

public class NativeFunctions {
  // Define the native function
  // these functions are called by the BroadcastReceiver object
  // when it receives a new notification
  public static native void stop_service();
}
