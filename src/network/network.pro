####################################################################################################

TARGET = test_network
TEMPLATE = app

CONFIG += c++14
CONFIG += debug

QT += core testlib network

SOURCES += \
  network_reply.cpp \
  network_fetcher.cpp \
  test_network.cpp

HEADERS += \
  network_reply.h \
  network_fetcher.h

####################################################################################################
#
# End
#
####################################################################################################
