# -*- CMake -*-

####################################################################################################
#
# Include directories
#

# include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# to embed QtCarto Module
include_directories(${CMAKE_SOURCE_DIR}/imports/QtCarto/)
include_directories(${Qt6Quick_PRIVATE_INCLUDE_DIRS})

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
  qtcarto # to embed QtCarto Module
  )
