TEMPLATE = app
TARGET = qtcarto

CONFIG += c++14
CONFIG += debug console qml_debug

QT += qml quick sensors

HEADERS += \
  sensors/qmlsensorrange.h \
  sensors/qmlsensor.h \
  sensors/qml_barimeter_altimeter_sensor.h

SOURCES += main.cpp \
  sensors/qmlsensorrange.cpp \
  sensors/qmlsensor.cpp \
  sensors/qml_barimeter_altimeter_sensor.cpp

RESOURCES += sensors.qrc

OTHER_FILES += \
  main.qml

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

