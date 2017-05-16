# -*- CMake -*-

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
  document/document.cpp
  document/document_database.cpp
  ephemeride/ephemeride.cpp
  international_morse_code_engine/international_morse_code_engine.cpp
  network/network_downloader.cpp
  network/network_fetcher.cpp
  network/network_reply.cpp
  network/network_ressource_request.cpp
  orm/SqlQueryModel.cpp
  orm/database.cpp
  orm/database_connection.cpp
  orm/database_schema.cpp
  orm/database_table.cpp
  orm/network_database.cpp
  orm/schema.cpp
  orm/schema_manager.cpp
  orm/sqlite_database.cpp
  orm/type_conversion.cpp
  phonetic_algorithm/soundex.cpp
  refuge/refuge_schema.cpp
  refuge/refuge_schema_custom_code.cpp
  refuge/refuge_schema_manager.cpp
  rrd/rrd.cpp
  settings/settings_database.cpp
  )
add_library(alpine_toolkit SHARED ${alpine_toolkit_library_files})
target_link_libraries(alpine_toolkit Qt5::Core Qt5::Sql Qt5::Positioning Qt5::Network Qt5::Qml cmark)

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
add_executable(alpine-toolkit ${alpine_toolkit_executable_files} ../ressources/alpine-toolkit.qrc)
target_link_libraries(alpine-toolkit alpine_toolkit Qt5::Qml Qt5::Widgets Qt5::Sensors Qt5::RemoteObjects)

####################################################################################################
#
# End
#
####################################################################################################
