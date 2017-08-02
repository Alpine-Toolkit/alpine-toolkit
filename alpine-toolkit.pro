####################################################################################################

TEMPLATE = app
TARGET = alpine-toolkit

####################################################################################################

CONFIG += c++14
CONFIG += debug console qml_debug
CONFIG += qtquickcompiler

QT += core network
QT += qml quick quickcontrols2
QT += sensors
QT += positioning
QT += sql
QT += svg widgets gui # to support SVG
QT += remoteobjects
# QT += charts

####################################################################################################

INCLUDEPATH += $$PWD
INCLUDEPATH += $$OUT_PWD

####################################################################################################
#
# Service Replica
#

# INCLUDEPATH += service

HEADERS += \
  service/definitions.h \
  service/client.h

SOURCES += \
  service/client.cpp

REPC_REPLICA += service/service.rep

####################################################################################################

# DEFINES += WITH_PROJ4
linux:!android {
LIBS += -lproj
}
android {
INCLUDEPATH += $$PWD/third-parties/proj4/proj.4.git/src
LIBS += -L$$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/proj4 -lqtcarto_proj4
}

####################################################################################################
#
# Sources
#

INCLUDEPATH += src src/qtcarto

# Fixme: config.h # symlink to cmake build ...

HEADERS += \
  src/qtcarto/coordinate/mercator.h \
  src/qtcarto/coordinate/projection.h \
  src/qtcarto/coordinate/sexagesimal_angle.h \
  src/qtcarto/coordinate/wgs84.h \
  src/qtcarto/coordinate/debug_tools.h \
  src/qtcarto/data_structure/simd.h \
  src/qtcarto/geo_data_format/gpx.h \
  src/qtcarto/geo_data_format/route.h \
  src/qtcarto/geo_data_format/waypoint.h \
  src/qtcarto/geo_data_format/xml_reader.h \
  src/qtcarto/geo_data_format/wkb.h \
  src/qtcarto/geometry/vector.h \
  src/qtcarto/math/interval.h \
  src/qtcarto/math/qc_math.h

HEADERS += \
  src/application/application.h \
  src/bleaudb/bleau_schema.h \
  src/bleaudb/bleau_schema_manager.h \
  src/bleaudb/bleau_sqlite_database.h \
  src/bleaudb/tmp/bleaudb.h \
  src/camptocamp/camptocamp_api_cache.h \
  src/camptocamp/camptocamp_client.h \
  src/camptocamp/camptocamp_constant.h \
  src/camptocamp/camptocamp_document.h \
  src/camptocamp/camptocamp_login_data.h \
  src/camptocamp/camptocamp_login.h \
  src/camptocamp/camptocamp_media_cache.h \
  src/camptocamp/camptocamp_qml.h \
  src/camptocamp/camptocamp_search_settings.h \
  src/configuration/configuration.h \
  src/document/document_database.h \
  src/document/document.h \
  src/ephemeride/ephemeride.h \
  src/full_text_search/text_document.h \
  src/full_text_search/language.h \
  src/full_text_search/phonetic_encoder.h \
  src/full_text_search/stemmer.h \
  src/full_text_search/token.h \
  src/full_text_search/tokenizer.h \
  src/international_morse_code_engine/international_morse_code_engine.h \
  src/network/network_downloader.h \
  src/network/network_reply.h \
  src/network/network_request.h \
  src/network/network_request_manager.h \
  src/orm/database_connection.h \
  src/orm/database.h \
  src/orm/database_query.h \
  src/orm/database_query_old.h \
  src/orm/database_row.h \
  src/orm/database_row_list.h \
  src/orm/database_schema.h \
  src/orm/database_table.h \
  src/orm/json_adaptator.h \
  src/orm/network_database.h \
  src/orm/schema.h \
  src/orm/schema_manager.h \
  src/orm/sql_flavour.h \
  src/orm/sqlite_database.h \
  src/orm/sql_query_model.h \
  src/orm/sql_record_wrapper.h \
  src/orm/type_conversion.h \
  src/refuge/refuge_schema.h \
  src/refuge/refuge_schema_manager.h \
  src/refuge/refuge_sqlite_database.h \
  src/rrd/rrd.h \
  src/satellite_model/satellite_model.h \
  src/sensors/qml_barimeter_altimeter_sensor.h \
  src/sensors/qmlsensor.h \
  src/sensors/qmlsensorrange.h \
  src/settings/settings_database.h \
  src/settings/settings_tree.h \
  src/tools/debug_data.h \
  src/tools/logger.h \
  src/tools/platform.h

SOURCES += \
  src/qtcarto/coordinate/mercator.cpp \
  src/qtcarto/coordinate/projection.cpp \
  src/qtcarto/coordinate/sexagesimal_angle.cpp \
  src/qtcarto/coordinate/wgs84.cpp \
  src/qtcarto/coordinate/debug_tools.cpp \
  src/qtcarto/data_structure/simd.cpp \
  src/qtcarto/geo_data_format/gpx.cpp \
  src/qtcarto/geo_data_format/route.cpp \
  src/qtcarto/geo_data_format/waypoint.cpp \
  src/qtcarto/geo_data_format/xml_reader.cpp \
  src/qtcarto/geo_data_format/wkb.cpp \
  src/qtcarto/geometry/vector.cpp \
  src/qtcarto/math/interval.cpp \
  src/qtcarto/math/qc_math.cpp

#document/document_manager.cpp
SOURCES += \
  src/application/application.cpp \
  src/application/test.cpp \
  src/bleaudb/bleau_schema.cpp \
  src/bleaudb/bleau_schema_manager.cpp \
  src/bleaudb/bleau_sqlite_database.cpp \
  src/camptocamp/camptocamp_api_cache.cpp \
  src/camptocamp/camptocamp_client.cpp \
  src/camptocamp/camptocamp_document.cpp \
  src/camptocamp/camptocamp_login.cpp \
  src/camptocamp/camptocamp_login_data.cpp \
  src/camptocamp/camptocamp_media_cache.cpp \
  src/camptocamp/camptocamp_qml.cpp \
  src/camptocamp/camptocamp_search_settings.cpp \
  src/configuration/configuration.cpp \
  src/document/document.cpp \
  src/document/document_database.cpp \
  src/ephemeride/ephemeride.cpp \
  src/full_text_search/phonetic_encoder.cpp \
  src/full_text_search/stemmer.cpp \
  src/full_text_search/text_document.cpp \
  src/full_text_search/token.cpp \
  src/full_text_search/tokenizer.cpp \
  src/international_morse_code_engine/international_morse_code_engine.cpp \
  src/main.cpp \
  src/network/network_downloader.cpp \
  src/network/network_reply.cpp \
  src/network/network_request.cpp \
  src/network/network_request_manager.cpp \
  src/orm/database.cpp \
  src/orm/database_connection.cpp \
  src/orm/database_query.cpp \
  src/orm/database_schema.cpp \
  src/orm/database_table.cpp \
  src/orm/json_adaptator.cpp \
  src/orm/network_database.cpp \
  src/orm/schema.cpp \
  src/orm/schema_manager.cpp \
  src/orm/sql_query_model.cpp \
  src/orm/sqlite_database.cpp \
  src/orm/type_conversion.cpp \
  src/refuge/refuge_schema.cpp \
  src/refuge/refuge_schema_custom_code.cpp \
  src/refuge/refuge_schema_manager.cpp \
  src/refuge/refuge_sqlite_database.cpp \
  src/rrd/rrd.cpp \
  src/satellite_model/satellite_model.cpp \
  src/sensors/qml_barimeter_altimeter_sensor.cpp \
  src/sensors/qmlsensor.cpp \
  src/sensors/qmlsensorrange.cpp \
  src/settings/settings_database.cpp \
  src/settings/settings_tree.cpp \
  src/tools/debug_data.cpp \
  src/tools/logger.cpp \
  src/tools/platform.cpp

####################################################################################################
#
# Android
#

android {
message("Android arch is $$ANDROID_TARGET_ARCH") # x86 armeabi-v7a

DEFINES += ANDROID

QT += androidextras

HEADERS += \
  src/android_activity/android_activity.h

SOURCES += \
  src/android_activity/android_activity.cpp

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

####################################################################################################
#
# Dependencies
#

INCLUDEPATH += $$PWD/third-parties/include # local/cmark/include

linux:!android {
LIBS += -L$$PWD/third-parties/local/cmark/lib -lcmark
LIBS += -L$$PWD/build-cmake/third-parties/snowball -lsnowball
}

android {
ANDROID_EXTRA_PLUGINS += $$OUT_PWD/plugins

LIBS += -L$$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/cmark -lcmark
LIBS += -L$$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/snowball -lsnowball
# LIBS += -lcrypto -lssl

ANDROID_EXTRA_LIBS += $$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/cmark/libcmark.so
ANDROID_EXTRA_LIBS += $$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/snowball/libsnowball.so
ANDROID_EXTRA_LIBS += $$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/sqlite/libsqlite.so
contains(ANDROID_TARGET_ARCH, armeabi-v7a) {
    #! ANDROID_EXTRA_LIBS += $$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/geos/libgeos.so
    ANDROID_EXTRA_LIBS += $$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/proj4/libqtcarto_proj4.so
    #! ANDROID_EXTRA_LIBS += $$PWD/build-cmake-android-$$ANDROID_TARGET_ARCH/third-parties/spatialite/libspatialite.so
}

# $$PWD/../third-parties/openssl-1.0.2h/libcrypto.so \
# $$PWD/../third-parties/openssl-1.0.2h/libssl.so
# $$PWD/build-cmake-android/third-parties/libiconv/libiconv.so \
}

####################################################################################################
#
# Resources
#

RESOURCES += ressources/alpine-toolkit.qrc

####################################################################################################
#
# Translations
#

lupdate_only{
SOURCES += \
  pages/*.qml
}

TRANSLATIONS = ressources/translations/alpine-toolkit.fr_FR.ts
# \ alpine-toolkit-en.ts

####################################################################################################
#
# Dist
#

# Fixme: Complete
DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/src/org/alpine_toolkit/AlpineToolkitActivity.java \
    android/src/org/alpine_toolkit/AlpineToolkitService.java
