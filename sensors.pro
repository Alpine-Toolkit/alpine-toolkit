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

