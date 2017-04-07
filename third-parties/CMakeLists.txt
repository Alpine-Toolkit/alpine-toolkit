# -*- CMake -*-

####################################################################################################

add_subdirectory(cmark)

if(ANDROID)
add_subdirectory(sqlite)
add_subdirectory(proj4) # x86: android log
add_subdirectory(geos) # x86: compile errors ???
add_subdirectory(libiconv)
add_subdirectory(spatialite) # x86: dependencies
endif(ANDROID)

####################################################################################################
#
# End
#
####################################################################################################
