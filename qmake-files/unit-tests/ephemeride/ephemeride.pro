####################################################################################################

TARGET = test_ephemeride
TEMPLATE = app

CONFIG += c++14
CONFIG += debug

QT += core testlib positioning

SOURCES += \
  ephemeride.cpp \
  test_ephemeride.cpp

HEADERS += \
  ephemeride.h