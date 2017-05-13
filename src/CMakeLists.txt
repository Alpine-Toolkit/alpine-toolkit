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
  bleaudb/bleau_database.cpp
  bleaudb/bleau_schema.cpp
  bleaudb/bleau_sqlite_database.cpp
  camptocamp/camptocamp_api_cache.cpp
  camptocamp/camptocamp_client.cpp
  camptocamp/camptocamp_document.cpp
  camptocamp/camptocamp_login.cpp
  camptocamp/camptocamp_login_data.cpp
  camptocamp/camptocamp_media_cache.cpp
  camptocamp/camptocamp_qml.cpp
  camptocamp/camptocamp_search_settings.cpp
  database/database.cpp
  database/database_connection.cpp
  database/database_schema.cpp
  database/database_table.cpp
  database/type_conversion.cpp
  database/network_database.cpp
  database/schema.cpp
  database/sqlite_database.cpp
  document/document.cpp
  document/document_database.cpp
  #document/document_manager.cpp
  ephemeride/ephemeride.cpp
  international_morse_code_engine/international_morse_code_engine.cpp
  network/network_downloader.cpp
  network/network_fetcher.cpp
  network/network_reply.cpp
  network/network_ressource_request.cpp
  refuge/refuge_schema.cpp
  refuge/refuge.cpp
  rrd/rrd.cpp
  settings/settings_database.cpp
  sql_model/SqlQueryModel.cpp
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
  satellite_model/satellite_model.cpp
  sensors/qml_barimeter_altimeter_sensor.cpp
  sensors/qmlsensor.cpp
  sensors/qmlsensorrange.cpp
  startup/load_sqlite.cpp
  startup/load_translation.cpp
  startup/register_qml_type.cpp
  startup/set_context_properties.cpp
  startup/test.cpp
  startup/user_directory.cpp
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
