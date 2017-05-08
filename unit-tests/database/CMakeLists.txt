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

set(blog_files
  blog.cpp
  blog_database.cpp
  test_blog.cpp
  )
add_executable(test_blog ${blog_files})
target_link_libraries(test_blog Qt5::Test alpine_toolkit)
add_test(NAME blog COMMAND test_blog)

####################################################################################################
#
# End
#
####################################################################################################
