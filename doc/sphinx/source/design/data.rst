Application Data
================

Data stored in the Qt Ressource file
------------------------------------

These files are:

* :file:`data/bleau.json`
  BleauDB data
* :file:`data/refuges.json`
  Refuge data
* :file:`data/stop-words.json`
  Stop Words data for FTS engine
* :file:`data/third_party_licenses.json`
  Third party licenses

Android Path
------------

* **Internal Storage Directory** :code:`getDataDir()` :file:`/data/user/0/org.alpine_toolkit/`
  `link <https://developer.android.com/reference/android/content/Context.html#getDataDir()>`_
* **Internal Directory** :code:`getFilesDir()` :file:`/data/user/0/org.alpine_toolkit/files`
  `link <https://developer.android.com/reference/android/content/Context.html#getFilesDir()>`_
* **Cache Directory** :code:`getCacheDir()`:file:`/data/user/0/org.alpine_toolkit/cache`
  `link <https://developer.android.com/reference/android/content/Context.html#getCacheDir()>`_

* **External Storage Directory** :code:`Environment.getExternalStorageDirectory()` :file:`/storage/emulated/0`
* **External Cache Directory**  :code:`getExternalCacheDir()` :file:`/storage/emulated/0/Android/data/org.alpine_toolkit/cache`
  `link <https://developer.android.com/reference/android/content/Context.html#getExternalCacheDir()>`_

* **External Files Directories** *code:`ContextCompat.getExternalFilesDirs()`
  `link <https://developer.android.com/reference/android/content/Context.html#getExternalFilesDirs(java.lang.String)>`_

  * :file:`/storage/emulated/0/Android/data/org.alpine_toolkit/files`
  * :file:`/storage/18F1-3803/Android/data/org.alpine_toolkit/files`


Android Assets
--------------

Some files are required by third parties when dynamic libraries are loaded at startup.  It means
theses files must be made available in the Android device file system before theses libraries are
loaded during the Qt thread initialisation.  The solution is to copy theses files from the Asset to
the file system in the private directory :file:`/data/user/0/org.alpine_toolkit/files/assets` when
the Java application is created first.  See code in
:file:`android/src/org/alpine_toolkit/AssetHelper.java`.

Theses files are listed in the file :file:`android/res/values/startup.xml`:

* :file:`android/assets/proj4_data/epsg`
  Proj4 EPSG data file

Data created by the application
-------------------------------

Theses files are created in the application user directory, on Linux
:file:`$HOME/.local/share/alpine-toolkit`.

:file:`debug_data.json`
      Debug information

:file:`c2c-cache.sqlite`
      Camptocamp cache database

:file:`media`
      Camptocamp file cache

:file:`wmts_token/geoportail-license.json`
      Geoportail token

:file:`wmts_cache`
      WMTS cache directory

Initialisation Sequence
-----------------------

QaConfig::init() is called in Application() ctor : create directory

QcMapItem is created when map page is loaded, then it creates QcWmtsPluginManager
