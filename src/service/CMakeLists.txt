####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

# add_library(alpine_toolkit_service SHARED)
add_executable(alpine-toolkit-service)

target_sources(alpine-toolkit-service
  PRIVATE
    main.cpp
    service.cpp
    service_application.cpp
    ${CMAKE_SOURCE_DIR}/src/base/logging/logger.cpp
)

qt_add_repc_sources(alpine-toolkit-service service.rep)

target_include_directories(alpine-toolkit-service
  PRIVATE
    ${CMAKE_SOURCE_DIR}/src # alpine_toolkit.h
    ${CMAKE_BINARY_DIR} # config.h
    ${CMAKE_CURRENT_BINARY_DIR} # rep_service_source.h
)

target_link_libraries(alpine-toolkit-service
  PRIVATE
    Qt6::Core
    Qt6::Core5Compat
    Qt6::RemoteObjects

    # androidextras
    # LIBS += -L$$OUT_PWD/../src -lalpine_toolkit_common_armeabi-v7a
)
