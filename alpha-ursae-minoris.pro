TEMPLATE = app
TARGET = alpha-ursae-minoris

CONFIG += c++14
CONFIG += debug console qml_debug

QT += qml quick sensors positioning

HEADERS += \
  sensors/qmlsensorrange.h \
  sensors/qmlsensor.h \
  sensors/qml_barimeter_altimeter_sensor.h \
  satellite_model.h

SOURCES += \
  main.cpp \
  sensors/qmlsensorrange.cpp \
  sensors/qmlsensor.cpp \
  sensors/qml_barimeter_altimeter_sensor.cpp \
  satellite_model.cpp

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
  android_activity.h

SOURCES += \
  android_activity.cpp

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