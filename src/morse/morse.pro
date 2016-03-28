####################################################################################################

TARGET = test_morse
TEMPLATE = app

CONFIG += c++14
CONFIG += debug

QT += core testlib

SOURCES += \
  international-morse-code.cpp \
  test_morse.cpp

HEADERS += \
  international-morse-code.h \
  international-morse-code-table.cpp

####################################################################################################
#
# End
#
####################################################################################################
