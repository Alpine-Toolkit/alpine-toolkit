# -*- CMake -*-

####################################################################################################
#
# Include directories
#

# include_directories(${CMAKE_CURRENT_BINARY_DIR})

####################################################################################################
#
# Library
#

set(alpine_toolkit_service_library_files
  main.cpp
  service.cpp
  )
qt5_generate_repc(alpine_toolkit_service_library_files service.rep SOURCE)
# add_library(alpine_toolkit_service SHARED ${alpine_toolkit_service_library_files})
add_executable(alpine-toolkit-service ${alpine_toolkit_service_library_files})
target_link_libraries(alpine-toolkit-service Qt5::Core Qt5::RemoteObjects)

####################################################################################################
#
# End
#
####################################################################################################
