####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

set(blog_files
  blog.cpp
  blog_database.cpp
  test_blog.cpp
  )
add_executable(test_blog ${blog_files})
target_link_libraries(test_blog Qt6::Test alpine-toolkit)
add_test(NAME blog COMMAND test_blog)

####################################################################################################

foreach(name
    query
    )
  add_executable(test_${name} test_${name}.cpp)
  target_link_libraries(test_${name} Qt6::Test alpine-toolkit)
  add_test(NAME ${name} COMMAND test_${name})
endforeach(name)
