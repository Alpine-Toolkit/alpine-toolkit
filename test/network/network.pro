####################################################################################################

TARGET = test_network
TEMPLATE = app

CONFIG += c++14
CONFIG += debug

QT += core testlib network

SOURCES += \
  network_reply.cpp \
  network_fetcher.cpp \
  network_ressource_request.cpp \
  network_downloader.cpp \
  test_network.cpp

HEADERS += \
  network_reply.h \
  network_fetcher.h \
  network_ressource_request.h \
  network_downloader.h

####################################################################################################
#
# End
#
####################################################################################################
