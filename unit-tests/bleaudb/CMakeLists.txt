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

foreach(name
    bleaudb
    bleau_database
    )
  add_executable(test_${name} test_${name}.cpp)
  target_link_libraries(test_${name} Qt5::Test alpine_toolkit)
  add_test(NAME ${name} COMMAND test_${name})
endforeach(name)

####################################################################################################
#
# End
#
####################################################################################################
