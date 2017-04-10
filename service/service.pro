####################################################################################################

TEMPLATE = lib
TARGET = service

####################################################################################################

CONFIG += c++14
CONFIG += debug console

QT += core
QT += remoteobjects
QT += sensors
# QT += positioning
# QT += sql

####################################################################################################
#
# Sources
#

# INCLUDEPATH +=

# Place before sources
REPC_SOURCE += service.rep

HEADERS += \
  definitions.h \
  service.h

SOURCES += \
  main.cpp \
  service.cpp
