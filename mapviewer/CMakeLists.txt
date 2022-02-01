# -*- CMake -*-

####################################################################################################
#
# Include directories
#

# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

####################################################################################################
#
# Executable
#

add_executable(mapviewer main.cpp mapviewer.qrc)
target_link_libraries(mapviewer
  Qt6::Core
  Qt6::Core5Compat
  Qt6::Gui
  Qt6::Qml
  Qt6::Quick
  Qt6::QuickWidgets
  Qt6::Svg
  alpine_toolkit_common
  )
