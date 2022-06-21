####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

# Instruct CMake to run moc automatically when needed.
#  https://cmake.org/cmake/help/latest/prop_tgt/AUTOMOC.html
#  https://doc.qt.io/qt-6/qt-wrap-cpp.html
set(CMAKE_AUTOMOC ON)

# Instruct CMake to run rcc automatically when needed.
# set(CMAKE_AUTORCC ON) # https://public.kitware.com/Bug/view.php?id=15074

if(CMAKE_BUILD_TYPE MATCHES "DEBUG")
  add_compile_definitions(QT_QML_DEBUG)
endif()

# https://doc.qt.io/qt-6/portingguide.html
# Disable use of C++ API deprecated in Qt 5.15
#! add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x050F00)

####################################################################################################

add_library(alpine-toolkit-common SHARED)

target_sources(alpine-toolkit-common
  PRIVATE
    base/logging/handler.cpp
    base/logging/logger.cpp

    configuration/configuration.cpp

    # $<$<PLATFORM_ID:LINUX>:configuration/linux_configuration.cpp>
    # $<$<PLATFORM_ID:ANDROID>:configuration/android_configuration.cpp>

    utils/debug_data/debug_data.cpp
    utils/platform/platform.cpp
)

if(LINUX)
  target_sources(alpine-toolkit-common
    PRIVATE
      configuration/linux_configuration.cpp
  )
endif(LINUX)

if(ANDROID)
  target_sources(alpine-toolkit-common
    PRIVATE
      configuration/android_configuration.cpp
  )
endif(LINUX)

target_include_directories(alpine-toolkit-common
  PRIVATE
    ${CMAKE_BINARY_DIR} # for config.h
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    base
)

target_link_libraries(alpine-toolkit-common
  PRIVATE
    Qt6::Core
    Qt6::Core5Compat
    Qt6::Network # for ???
    Qt6::Widgets # for platform.cpp
)

####################################################################################################

add_subdirectory(service)

# QtCarto Library
add_subdirectory(qtcarto)

# add_subdirectory(qml)

####################################################################################################

# Alpine Toolkit Library
add_library(alpine-toolkit SHARED)

target_sources(alpine-toolkit
  PRIVATE
    base/network/network_downloader.cpp
    base/network/network_reply.cpp
    base/network/network_request.cpp
    base/network/network_request_manager.cpp

    base/orm/database.cpp
    base/orm/database_connection.cpp
    base/orm/database_query.cpp
    base/orm/database_schema.cpp
    base/orm/database_table.cpp
    base/orm/json_adaptator.cpp
    base/orm/network_database.cpp
    base/orm/schema.cpp
    base/orm/schema_manager.cpp
    base/orm/sql_query_model.cpp
    base/orm/sqlite_database.cpp
    base/orm/type_conversion.cpp
    base/platform_abstraction/android_fake_permission_manager.cpp
    base/platform_abstraction/android_fake_platform.cpp
    base/platform_abstraction/linux_platform.cpp
    base/platform_abstraction/permission_manager.cpp
    base/platform_abstraction/platform_abstraction.cpp

    data_sources/bleaudb/bleau_schema.cpp
    data_sources/bleaudb/bleau_schema_manager.cpp
    data_sources/bleaudb/bleau_sqlite_database.cpp
    data_sources/camptocamp/camptocamp_api_cache.cpp
    data_sources/camptocamp/camptocamp_client.cpp
    data_sources/camptocamp/camptocamp_document.cpp
    data_sources/camptocamp/camptocamp_login.cpp
    data_sources/camptocamp/camptocamp_login_data.cpp
    data_sources/camptocamp/camptocamp_media_cache.cpp
    data_sources/camptocamp/camptocamp_qml.cpp
    data_sources/camptocamp/camptocamp_schema.cpp
    data_sources/camptocamp/camptocamp_search_settings.cpp
    data_sources/document/document.cpp
    data_sources/document/document_database.cpp
    #data_sources/document/document_manager.cpp
    data_sources/refuge/refuge_schema.cpp
    data_sources/refuge/refuge_schema_custom_code.cpp
    data_sources/refuge/refuge_schema_manager.cpp
    data_sources/refuge/refuge_sqlite_database.cpp
    data_sources/settings/settings_database.cpp
    data_sources/settings/settings_tree.cpp
    data_sources/third_party_license/third_party_license_schema.cpp
    data_sources/third_party_license/third_party_license_schema_manager.cpp
    data_sources/third_party_license/third_party_license_sqlite_database.cpp

    utils/checksum/checksum.cpp
    utils/ephemeride/ephemeride.cpp
    utils/full_text_search/phonetic_encoder.cpp
    utils/full_text_search/stemmer.cpp
    utils/full_text_search/text_document.cpp
    utils/full_text_search/token.cpp
    utils/full_text_search/tokenizer.cpp
    utils/international_morse_code_engine/international_morse_code_engine.cpp
    utils/rrd/rrd.cpp
)

target_include_directories(alpine-toolkit
  PRIVATE
  PUBLIC
    ${CMAKE_BINARY_DIR} # config.h
    ${CMAKE_SOURCE_DIR}/src # alpine_toolkit.h
    base # network/network_request.h
    data_sources
    utils
)

target_link_libraries(alpine-toolkit
  # cmark
  PRIVATE
    Qt6::Core
    Qt6::Network
    Qt6::Qml
    Qt6::Gui

  PUBLIC
    Qt6::Core5Compat
    Qt6::Positioning
    Qt6::Quick
    Qt6::Sql

    snowball

    qtcarto # link alpine-toolkit-common
)

####################################################################################################
#
# Application
#

add_executable(alpine-toolkit-app)
set_target_properties(alpine-toolkit-app
  PROPERTIES
    OUTPUT_NAME alpine-toolkit
)

target_sources(alpine-toolkit-app
  PRIVATE
    main.cpp

    application/application.cpp
    application/test.cpp

    qml/satellite_model/satellite_model.cpp
    qml/sensors/qml_barimeter_altimeter_sensor.cpp
    qml/sensors/qmlsensor.cpp
    qml/sensors/qmlsensorrange.cpp

    service/client.cpp
)

qt_add_repc_replicas(alpine-toolkit-app service/service.rep)

target_include_directories(alpine-toolkit-app
  PRIVATE
    ${CMAKE_BINARY_DIR} # config.h
    ${CMAKE_CURRENT_BINARY_DIR} # rep_service_replica.h
    qml
)

add_subdirectory(resources)

target_link_libraries(alpine-toolkit-app
  PRIVATE
  Qt6::Widgets # QApplication
    Qt6::Qml
    Qt6::Sensors
    Qt6::RemoteObjects

    alpine-toolkit-common
    alpine-toolkit
)

if(ANDROID)
  target_sources(alpine-toolkit-app
    PRIVATE
      base/platform_abstraction/android_platform.cpp
      base/platform_abstraction/android_permission_manager.cpp

      # base/platform_abstraction/android_native.cpp
  )

  # androidextras
endif(ANDROID)

if(LINUX)
  target_sources(alpine-toolkit-app
    PRIVATE
      base/platform_abstraction/linux_platform.cpp
  )
endif(LINUX)

# Not available
# qtquick_compiler_add_resources(resources ../resources/alpine-toolkit.qrc)
