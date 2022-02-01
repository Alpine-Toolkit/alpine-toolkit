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

add_executable(tile-loader tile-loader.cpp)
target_link_libraries(tile-loader
  alpine_toolkit_common
  qtcarto
  )

add_executable(spatialite-test spatialite-test.cpp)
target_link_libraries(spatialite-test Qt6::Sql)
