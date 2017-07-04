# -*- CMake -*-

####################################################################################################
#
# $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
#
# This file is part of the QtCarto library.
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

add_subdirectory(qtcarto)

####################################################################################################
#
# Include directories
#

include_directories(${CMAKE_SOURCE_DIR})

####################################################################################################
#
# Library
#

set(alpine_toolkit_library_files
  #document/document_manager.cpp
  bleaudb/bleau_schema.cpp
  bleaudb/bleau_schema_manager.cpp
  bleaudb/bleau_sqlite_database.cpp
  camptocamp/camptocamp_api_cache.cpp
  camptocamp/camptocamp_client.cpp
  camptocamp/camptocamp_document.cpp
  camptocamp/camptocamp_login.cpp
  camptocamp/camptocamp_login_data.cpp
  camptocamp/camptocamp_media_cache.cpp
  camptocamp/camptocamp_qml.cpp
  camptocamp/camptocamp_search_settings.cpp
  camptocamp/camptocamp_schema.cpp
  document/document.cpp
  document/document_database.cpp
  ephemeride/ephemeride.cpp
  full_text_search/text_document.cpp
  full_text_search/phonetic_encoder.cpp
  full_text_search/stemmer.cpp
  full_text_search/token.cpp
  full_text_search/tokenizer.cpp
  international_morse_code_engine/international_morse_code_engine.cpp
  network/network_downloader.cpp
  network/network_reply.cpp
  network/network_request.cpp
  network/network_request_manager.cpp
  orm/database.cpp
  orm/database_connection.cpp
  orm/database_query.cpp
  orm/database_schema.cpp
  orm/database_table.cpp
  orm/json_adaptator.cpp
  orm/network_database.cpp
  orm/schema.cpp
  orm/schema_manager.cpp
  orm/sql_query_model.cpp
  orm/sqlite_database.cpp
  orm/type_conversion.cpp
  refuge/refuge_schema.cpp
  refuge/refuge_schema_custom_code.cpp
  refuge/refuge_schema_manager.cpp
  refuge/refuge_sqlite_database.cpp
  rrd/rrd.cpp
  settings/settings_database.cpp
  settings/settings_tree.cpp
  )
add_library(alpine_toolkit SHARED ${alpine_toolkit_library_files})
target_link_libraries(alpine_toolkit
  Qt5::Core
  Qt5::Sql
  Qt5::Positioning
  Qt5::Network
  Qt5::Qml
  Qt5::Gui
  Qt5::Quick
  cmark
  snowball
  qtcarto
  )

####################################################################################################
#
# Application
#

# android_activity/android_activity.cpp

set(alpine_toolkit_executable_files
  main.cpp
  application/application.cpp
  application/test.cpp
  configuration/configuration.cpp
  satellite_model/satellite_model.cpp
  sensors/qml_barimeter_altimeter_sensor.cpp
  sensors/qmlsensor.cpp
  sensors/qmlsensorrange.cpp
  tools/debug_data.cpp
  tools/logger.cpp
  tools/platform.cpp
  ${CMAKE_SOURCE_DIR}/service/client.cpp
  )
qt5_generate_repc(alpine_toolkit_executable_files ${CMAKE_SOURCE_DIR}/service/service.rep REPLICA)
qt5_add_resources(ressources ../ressources/alpine-toolkit.qrc)
# Not available
# qtquick_compiler_add_resources(ressources ../ressources/alpine-toolkit.qrc)
add_executable(alpine-toolkit ${alpine_toolkit_executable_files} ${ressources})
target_link_libraries(alpine-toolkit
  alpine_toolkit
  Qt5::Qml
  Qt5::Widgets
  Qt5::Sensors
  Qt5::RemoteObjects
  )

####################################################################################################
#
# End
#
####################################################################################################
