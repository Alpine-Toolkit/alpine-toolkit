Application Data
================

Data stored in the Qt Ressource file
------------------------------------

These files are:

:file:`data/bleau.json`

:file:`data/refuges.json`

:file:`data/stop-words.json`

:file:`data/third_party_licenses.json`
      Third party licenses

Android Assets
--------------

Some files are required by third parties when dynamic libraries are loaded at startup.  It means
theses files must be made available in the Android device file system before theses libraries are
loaded during the Qt thread initialisation.  The solution is to copy theses files from the Asset to
the file system in the private directory :file:`/data/user/0/org.alpine_toolkit/files/assets` when
the Java application is created first.

Theses files are listed in the file :file:`android/res/values/startup.xml`:

:file:`android/assets/proj4_data/epsg`
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
