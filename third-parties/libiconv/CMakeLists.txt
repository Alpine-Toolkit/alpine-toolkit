# -*- CMake -*-

# see https://github.com/LuaDist/libiconv

####################################################################################################

set(LIBICONV_SOURCE_PATH "libiconv-sources")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ${CMAKE_MODULE_PATH})

include(configure)
# include(dist)

####################################################################################################

# Configure file replacement that patches some header files when building on Microsoft Visual
# Studio Compilers If not MSVC this function will fall back to the default configure_file
## implementation from cmake
macro(iconv_configure_file)
  include(CMakeParseArguments)
  set(options)
  set(oneValueArgs LIBRARY_NAME INPUT OUTPUT)
  set(multiValueArgs)
  cmake_parse_arguments(arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  configure_file(${arg_INPUT} ${arg_OUTPUT} ${arg_UNPARSED_ARGUMENTS})
endmacro()

####################################################################################################

# -Wno-multichar

ADD_DEFINITIONS(
  -D_ANDROID
  -DBUILDING_LIBICONV
  -DIN_LIBRARY
  )

####################################################################################################

include(CheckIncludeFiles)
include(CheckFunctionExists)

CHECK_INCLUDE_FILES(whar.h HAVE_WCHAR_T)

set(CMAKE_REQUIRED_INCLUDES wchar.h)
#set(CMAKE_REQUIRED_LIBRARIES )
CHECK_FUNCTION_EXISTS(wcrtomb USE_MBSTATE_T) # mbrtowc

set(ICONV_CONST const)

# iconv.h
set(USE_MBSTATE_T 1)
set(BROKEN_WCHAR_H 0)
set(HAVE_WCHAR_T 0)

# @DLL_VARIABLE@
# @EILSEQ@

####################################################################################################

message(STATUS "Generating libiconv ${CMAKE_CURRENT_BINARY_DIR}/include/iconv.h")
configure_file(${LIBICONV_SOURCE_PATH}/include/iconv.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/iconv.h
  @ONLY)

configure_file(config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/include/config.h)

set(LIBDIR '"to_be_defined"')
configure_file(configmake.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/configmake.h)

set(LIBRARY_NAME libiconv)

# iconv_configure_file(LIBRARY_NAME iconv
#   INPUT ${LIBICONV_SOURCE_PATH}/include/iconv.h.build.in
#   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/iconv.h )

# iconv_configure_file(LIBRARY_NAME iconv
#   INPUT ${LIBICONV_SOURCE_PATH}/srclib/alloca.in.h
#   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/srclib/alloca.h )

# iconv_configure_file(LIBRARY_NAME iconv
#   INPUT ${LIBICONV_SOURCE_PATH}/include/iconv.h.build.in
#   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/iconv.h)

# iconv_configure_file(LIBRARY_NAME iconv
#   INPUT ${LIBICONV_SOURCE_PATH}/srclib/unistd.in.h
#   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/srclib/unistd.h @ONLY)

# iconv_configure_file(LIBRARY_NAME iconv
#   INPUT ${LIBICONV_SOURCE_PATH}/srclib/unitypes.in.h
#   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/srclib/unitypes.h)

# iconv_configure_file(LIBRARY_NAME charset
#   INPUT ${LIBICONV_SOURCE_PATH}/libcharset/include/libcharset.h.ind
#   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/libcharset.h)

iconv_configure_file(LIBRARY_NAME charset
  INPUT ${LIBICONV_SOURCE_PATH}/libcharset/include/localcharset.h.build.in
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/include/localcharset.h)

####################################################################################################

include_directories(${LIBICONV_SOURCE_PATH})
include_directories(${LIBICONV_SOURCE_PATH}/include)
include_directories(${LIBICONV_SOURCE_PATH}/lib)
include_directories(${LIBICONV_SOURCE_PATH}/libcharset/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include)

####################################################################################################

SET(LIBICONV_SOURCES
  lib/iconv.c
  lib/relocatable.c
  libcharset/lib/localcharset.c
  )

PREPEND(LIBICONV_SOURCES ${LIBICONV_SOURCE_PATH} ${LIBICONV_SOURCES})

add_library(iconv
  STATIC
  ${LIBICONV_SOURCES}
  )

####################################################################################################
#
# End
#
####################################################################################################
