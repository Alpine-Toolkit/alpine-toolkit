Source Map
==========

* :file:`alpine-toolkit-all.pro`
  Alpine Toolkit Top Qmake
* :file:`alpine-toolkit.pro`
  Alpine Toolkit Qmake
* :file:`android/`
  Android sources

  * :file:`assets/`
  * :file:`res/`
    icons and logo
  * :file:`src/org/alpine_toolkit/`

    * :file:`AlpineToolkitActivity.java`
      Alpine Toolkit Activity
    * :file:`AlpineToolkitService.java`
      Alpine Toolkit Service
    * :file:`AssetHelper.java`
      Tool to copy asset on filesystem
    * :file:`BatteryReceiver.java`
      Battery Event Receiver
    * :file:`Camera/`
      Camera Tools
    * :file:`Constants.java`
    * :file:`DeviceUserInterfaceHelper.java`
      User Interface Tools
    * :file:`FileHelper.java`
      Tools to delete directory and copy file
    * :file:`NativeFunctions.java`
      *purpose ???*
    * :file:`Permission/`
      Permission Tools *used ?*
    * :file:`PhoneHelper.java`
      Phone Tools
    * :file:`SdCardHelper.java`
      Storage Tools
    * :file:`ServiceHelper.java`
      Service Tools

* :file:`annexes/`
  Additional contents like fuel-gauge PDF
* :file:`build-scripts/`
* :file:`cmake/`
  CMake add-ons
* :file:`CMakeLists.txt`
  Alpine Toolkit Top Cmakelists
* :file:`code-generator/`
  Code generator

  * :file:`camptocamp/`
  * :file:`CodeGenerator/`
  * :file:`code-generator-templates/`
  * :file:`Schemas/`

  Scripts

  * :file:`generate`
  * :file:`generate-all`
  * :file:`generate-cpp-class`

* :file:`common.pri`
  Common definitions for QMake
* :file:`compile_commands.json`
  -> :file:`build-cmake/compile_commands.json`
* :file:`config.h`
  -> :file:`build-cmake/config.h`
* :file:`config.h.in`
  Template for :file:`config.h`
* :file:`dev-scripts/`
* :file:`doc/`
  Alpine Toolkit Documentation
* :file:`imports/`
  Additional Qt Plugins

  * :file:`QtCarto/`

* :file:`map-providers/`
  WMTS map providers data
* :file:`map-tools/`
  Tools to cache WMTS tiles
* :file:`mapviewer/`
  Mapviewer standalone application (will be deprecated)
* :file:`ressources/`
  Ressources like icons, qml, js files
* :file:`service/`
  Android service sources
* :file:`sqlite/`
  SQlite Qt plugin (with **at** prefix) patched for :code:`sqlite3_enable_load_extension`
* :file:`src/`
  Alpine Toolkit sources

  * :file:`application/`
  * :file:`bleaudb/`
    BleauDB API
  * :file:`camptocamp/`
    C2C API
  * :file:`checksum/`
    Tool to compute checksum
  * :file:`configuration/`
  * :file:`document/`
  * :file:`ephemeride/`
    Tool to compute ephemeride
  * :file:`full_text_search/`
    Full Text Search Engine
  * :file:`international_morse_code_engine/`
    Tool to encode/decode Morse code
  * :file:`logging/`
    Logging tool
  * :file:`main.cpp`
    Alpine Toolkit main
  * :file:`network/`
    Tool for network request
  * :file:`orm/`
    ORM engine
  * :file:`platform_abstraction/`
    Platform abstraction for Android, Linux
  * :file:`qtcarto/`
    Map engine
  * :file:`refuge/`
    Refuge database
  * :file:`rrd/`
    RRD database engine
  * :file:`satellite_model/`
    GPS Satellite Model
  * :file:`sensors/`
    Qt add-ons for Barometer/Altimeter Sensor
  * :file:`settings/`
    Settings Database
  * :file:`third_party_license/`
    Third Party License Database
  * :file:`tools/`

* :file:`third-parties/`
  Third parties sources

  * :file:`build-openssl-android.sh`
    Script to build OpenSSL for Android
  * :file:`cmake/`
    CMake add-ons
  * :file:`CMakelists.txt`
    Third-parties CMakelists
  * :file:`cmark/`
    Markdown library
  * :file:`geos/`
    Spatialite dependency (for Android)
  * :file:`libiconv/`
    Spatialite dependency (for Android)
  * :file:`libspatialindex/`
    R-Tree library
  * :file:`openssl/`
    OpenSSL Library (for Android)
  * :file:`proj4/`
    Projection library (for Android)
  * :file:`spatialite/`
    Spatialite is a SQLite GIS extension (for Android)
  * :file:`snowball/`
    Snowball is a string processing library (for Android)
  * :file:`sqlite/`
    SQLite source (for Android)

* :file:`unit-tests/`
  Unit tests
