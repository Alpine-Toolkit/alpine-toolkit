####################################################################################################

TARGET = test_international_morse_code_engine
TEMPLATE = app

CONFIG += c++14
CONFIG += debug

QT += core testlib

SOURCES += \
  international_morse_code_engine.cpp \
  test_international_morse_code_engine.cpp

HEADERS += \
  international_morse_code_engine.h \
  international_morse_code_engine_table.cpp

####################################################################################################
#
# End
#
####################################################################################################
