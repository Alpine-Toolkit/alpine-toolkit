# -*- mode: qmake -*-

####################################################################################################

HEADERS += \
  src/application/application.h \
  src/satellite_model/satellite_model.h \
  src/sensors/qml_barimeter_altimeter_sensor.h \
  src/sensors/qmlsensor.h \
  src/sensors/qmlsensorrange.h \
  src/application/alpine_toolkit.h

SOURCES += \
  src/main.cpp \
  src/application/application.cpp \
  src/application/test.cpp \
  src/satellite_model/satellite_model.cpp \
  src/sensors/qml_barimeter_altimeter_sensor.cpp \
  src/sensors/qmlsensor.cpp \
  src/sensors/qmlsensorrange.cpp
