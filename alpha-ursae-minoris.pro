####################################################################################################

TEMPLATE = app
TARGET = alpha-ursae-minoris

####################################################################################################

CONFIG += c++14
CONFIG += debug console qml_debug

QT += qml quick
QT += sensors
QT += positioning
QT += svg widgets gui # to support SVG

INCLUDEPATH += src

HEADERS += \
  src/ephemeride/ephemeride.h \
  src/refuge/refuge.h \
  src/satellite_model/satellite_model.h \
  src/sensors/qml_barimeter_altimeter_sensor.h \
  src/sensors/qmlsensor.h \
  src/sensors/qmlsensorrange.h \
  src/international_morse_code_engine/international_morse_code_engine.h \
  src/international_morse_code_engine/international_morse_code_engine_table.cpp

SOURCES += \
  src/ephemeride/ephemeride.cpp \
  src/main.cpp \
  src/refuge/refuge.cpp \
  src/satellite_model/satellite_model.cpp \
  src/sensors/qml_barimeter_altimeter_sensor.cpp \
  src/sensors/qmlsensor.cpp \
  src/sensors/qmlsensorrange.cpp \
  src/international_morse_code_engine/international_morse_code_engine.cpp

lupdate_only{
SOURCES += \
  pages/*.qml
}

# OTHER_FILES += \
#   pages/*.qml

RESOURCES += alpha-ursae-minoris.qrc

TRANSLATIONS = translations/alpha-ursae-minoris.fr_FR.ts
# \ alpha-ursae-minoris-en.ts

####################################################################################################
#
# Android
#

android {
DEFINES += ANDROID

QT += androidextras

HEADERS += \
  src/android_activity/android_activity.h

SOURCES += \
  src/android_activity/android_activity.cpp

# OTHER_FILES += \
#   android/AndroidManifest.xml

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

####################################################################################################
#
# End
#
####################################################################################################
