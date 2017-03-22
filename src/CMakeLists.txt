# -*- CMake -*-

####################################################################################################
#
# Include directories
#

# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

####################################################################################################

####################################################################################################
#
# Library
#

set(alpine_toolkit_library_files
  bleaudb/bleaudb.cpp
  bleaudb/bleaudb_json_loader.cpp
  camptocamp/camptocamp_cache.cpp
  camptocamp/camptocamp_client.cpp
  camptocamp/camptocamp_document.cpp
  camptocamp/camptocamp_login.cpp
  camptocamp/camptocamp_qml.cpp
  database/database.cpp
  ephemeride/ephemeride.cpp
  international_morse_code_engine/international_morse_code_engine.cpp
  network/network_downloader.cpp
  network/network_fetcher.cpp
  network/network_reply.cpp
  network/network_ressource_request.cpp
  refuge/refuge.cpp
  rrd/rrd.cpp
  sql_model/SqlQueryModel.cpp
  )
add_library(alpine_toolkit SHARED ${alpine_toolkit_library_files})
target_link_libraries(alpine_toolkit Qt5::Core Qt5::Sql Qt5::Positioning Qt5::Network)

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
  )
add_executable(alpine-toolkit ${alpine_toolkit_executable_files} ../alpine-toolkit.qrc)
target_link_libraries(alpine-toolkit alpine_toolkit Qt5::Qml Qt5::Widgets Qt5::Sensors)

####################################################################################################
#
# End
#
####################################################################################################
