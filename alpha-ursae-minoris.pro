TEMPLATE = app
TARGET = alpha-ursae-minoris

CONFIG += c++14
CONFIG += debug console qml_debug

QT += qml quick sensors positioning

INCLUDEPATH += src

HEADERS += \
  src/ephemeride/ephemeride.h \
  src/sensors/qmlsensorrange.h \
  src/sensors/qmlsensor.h \
  src/sensors/qml_barimeter_altimeter_sensor.h \
  src/satellite_model.h \
  src/refuge/refuge.h

SOURCES += \
  main.cpp \
  src/ephemeride/ephemeride.cpp \
  src/sensors/qmlsensorrange.cpp \
  src/sensors/qmlsensor.cpp \
  src/sensors/qml_barimeter_altimeter_sensor.cpp \
  src/satellite_model.cpp \
  src/refuge/refuge.cpp

lupdate_only{
SOURCES += \
  main.qml \
  pages/*.qml
}

OTHER_FILES += \
  main.qml \
  pages/*.qml \
  android/AndroidManifest.xml

RESOURCES += alpha-ursae-minoris.qrc

TRANSLATIONS = translations/alpha-ursae-minoris.fr_FR.ts
# \ alpha-ursae-minoris-en.ts

android {
DEFINES += ANDROID

QT += androidextras

HEADERS += \
  src/android_activity.h

SOURCES += \
  src/android_activity.cpp

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