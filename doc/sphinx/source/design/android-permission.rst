Android Permission
==================

Reference Documentation
-----------------------

* `Android Developers Permissions overview <https://developer.android.com/guide/topics/permissions/overview>`_
* `QtAndroid <https://doc.qt.io/qt-5/qtandroid.html>`_

Alpine Toolkit Permissions
--------------------------

Permissions are listed in

* :file:`android/AndroidManifest.xml`
* :file:`android/src/org/alpine_toolkit/Constants.java`

These permissions are automatically granted:

* **ACCESS_NETWORK_STATE**
* **FLASHLIGHT**
* **INTERNET**

These permissions need grant:

* **ACCESS_FINE_LOCATION**
* **CAMERA**
* **READ_EXTERNAL_STORAGE**
* **WRITE_EXTERNAL_STORAGE**
  required by :code:`Application::setup_user_directory`

Implementation
--------------

Relevant source files are

* :file:`android/src/org/alpine_toolkit/`

  * :file:`AlpineToolkitActivity.java`
  * :file:`android/src/org/alpine_toolkit/Permission/`

* :file:`src/platform_abstraction/permission_manager.cpp`
* :file:`src/platform_abstraction/android_permission_manager.cpp`

* :file:`resource/js/android_permission.js`

Permission Workflow
-------------------

*Fixme: AT versus Qt implementation ???*

1. At Activity startup, permissions are checked

  * if they are granted,
  * if they need an explanation,
  * if they need to be granted.

1. :code:`PermissionManager` API
