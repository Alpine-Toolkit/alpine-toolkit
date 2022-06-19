# -*- CMake -*-

####################################################################################################
#
# $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
#
# This file is part of the Alpine Toolkit software.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# $ALPINE_TOOLKIT_END_LICENSE$
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
#
# Include directories
#

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/base)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/data_sources)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/qml)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils)
include_directories(${CMAKE_SOURCE_DIR}/src/qml/QtCarto)
include_directories(${Qt6Quick_PRIVATE_INCLUDE_DIRS})

####################################################################################################

add_subdirectory(service)
# add_subdirectory(qml)

####################################################################################################
#
# Library
#

set(alpine_toolkit_common_library_files
  base/logging/handler.cpp
  base/logging/logger.cpp
  configuration/configuration.cpp
  configuration/linux_configuration.cpp
  utils/debug_data/debug_data.cpp
  utils/platform/platform.cpp
  )
add_library(alpine_toolkit_common SHARED ${alpine_toolkit_common_library_files})
target_link_libraries(alpine_toolkit_common
  Qt6::Core
  Qt6::Core5Compat
  Qt6::Network
  Qt6::Widgets # for platform.cpp
  )

####################################################################################################
#
# QtCarto Library
#

add_subdirectory(qtcarto)

####################################################################################################
#
# Alpine Toolkit Library
#

set(alpine_toolkit_library_files
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
add_library(alpine_toolkit SHARED ${alpine_toolkit_library_files})
target_link_libraries(alpine_toolkit
  Qt6::Core
  Qt6::Core5Compat
  Qt6::Sql
  Qt6::Positioning
  Qt6::Network
  Qt6::Qml
  Qt6::Gui
  Qt6::Quick
  # cmark
  snowball
  qtcarto
  )

####################################################################################################
#
# Application
#

set(alpine_toolkit_executable_files
  main.cpp
  application/application.cpp
  application/test.cpp
  qml/satellite_model/satellite_model.cpp
  qml/sensors/qml_barimeter_altimeter_sensor.cpp
  qml/sensors/qmlsensor.cpp
  qml/sensors/qmlsensorrange.cpp
  service/client.cpp
  )

add_executable(alpine-toolkit ${alpine_toolkit_executable_files})

add_subdirectory(resources)

# Not available
# qtquick_compiler_add_resources(resources ../resources/alpine-toolkit.qrc)

qt_add_repc_replicas(alpine-toolkit service/service.rep)
target_link_libraries(alpine-toolkit
  alpine_toolkit_common
  alpine_toolkit
  Qt6::Qml
  Qt6::Sensors
  Qt6::RemoteObjects
  )

if(ANDROID)
  target_sources(alpine-toolkit PRIVATE base/platform_abstraction/android_native.cpp)
endif()
