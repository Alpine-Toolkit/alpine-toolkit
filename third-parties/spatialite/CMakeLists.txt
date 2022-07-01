# -*- CMake -*-

####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

set(SPATIALITE_SOURCE_PATH "spatialite-sources")

####################################################################################################

set(PACKAGE libspatialite)
set(VERSION "4.4.0-RC1")
# a.furieri@lqt.it

####################################################################################################

add_compile_definitions(
  # HAVE_USLEEP=1
  # SQLITE_DEFAULT_JOURNAL_SIZE_LIMIT=1048576
  # SQLITE_THREADSAFE=1
  # NDEBUG=1
  # SQLITE_ENABLE_MEMORY_MANAGEMENT=1
  # SQLITE_DEFAULT_AUTOVACUUM=1
  # SQLITE_TEMP_STORE=3
  # SQLITE_ENABLE_FTS3
  # SQLITE_ENABLE_FTS3_BACKWARDS
  # SQLITE_ENABLE_RTREE=1
  # SQLITE_DEFAULT_FILE_FORMAT=4

  SQLITE_ENABLE_FTS3 # version 3 of the full-text search engine
  SQLITE_ENABLE_FTS3_PARENTHESIS
  SQLITE_ENABLE_FTS5
  SQLITE_ENABLE_JSON1 # JSON SQL functions
  SQLITE_ENABLE_RTREE # R*Tree index extension
)

add_compile_definitions(
  OMIT_FREEXL
  # "TARGET_CPU=$(TARGET_ARCH_ABI)"
  fdatasync=fsync
  SQLITE_ENABLE_RTREE=1
  # ENABLE_GCP=1
  # ENABLE_GEOPACKAGE=1
  # ENABLE_LIBXML2=1
  # ENABLE_LWGEOM=1
  SQLITE_OMIT_BUILTIN_TEST=1

  LOADABLE_EXTENSION=1
)

# ENABLE_GCP
# ENABLE_GEOPACKAGE
# ENABLE_LIBXML2
# ENABLE_RTTOPO
# OMIT_EPSG
# OMIT_FREEXL
# OMIT_GEOCALLBACKS
# OMIT_GEOS
# SET(OMIT_ICONV) # ICONV is absolutely required
# OMIT_KNN
# OMIT_MATHSQL
# OMIT_PROJ

####################################################################################################

include(CheckIncludeFiles)
include(CheckFunctionExists)
include(AC_HEADER_STDC)
include(AutoconfHelper)

# Checks for header files.
check_include_files(dlfcn.h HAVE_DLFCN_H)
check_include_files(fcntl.h HAVE_FCNTL_H)
check_include_files(float.h HAVE_FLOAT_H)
check_include_files(freexl.h HAVE_FREEXL_H)
check_include_files(geos_c.h HAVE_GEOS_C_H)
check_include_files(iconv.h HAVE_ICONV_H)
check_include_files(inttypes.h HAVE_INTTYPES_H)
check_include_files(librttopo.h HAVE_LIBRTTOPO_H)
check_include_files(math.h HAVE_MATH_H)
check_include_files(memory.h HAVE_MEMORY_H)
check_include_files(proj_api.h HAVE_PROJ_API_H)
check_include_files(sqlite3ext.h HAVE_SQLITE3EXT_H)
check_include_files(sqlite3.h HAVE_SQLITE3_H)
check_include_files(stddef.h HAVE_STDDEF_H)
check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(stdio.h HAVE_STDIO_H)
check_include_files(stdlib.h HAVE_STDLIB_H)
check_include_files(strings.h HAVE_STRINGS_H)
check_include_files(string.h HAVE_STRING_H)
check_include_files(sys/stat.h HAVE_SYS_STAT_H)
check_include_files(sys/time.h HAVE_SYS_TIME_H)
check_include_files(sys/types.h HAVE_SYS_TYPES_H)
check_include_files(unistd.h HAVE_UNISTD_H)
check_include_files(zlib.h HAVE_ZLIB_H)

# Checks for typedefs, structures, and compiler characteristics.
ac_c_const()
ac_type_off_t()
ac_type_size_t()
ac_header_time()
ac_struct_tm()
# AC_C_VOLATILE

# Checks for library functions.
# check_function_exists(AC_FUNC_LSTAT)
# check_function_exists(AC_FUNC_LSTAT_FOLLOWS_SLASHED_SYMLINK)
# check_function_exists(AC_FUNC_MEMCMP)
# check_function_exists(AC_FUNC_STAT)
set(CMAKE_REQUIRED_INCLUDES math.h strings.h)
set(CMAKE_REQUIRED_LIBRARIES m)
check_function_exists(fdatasync HAVE_FDATASYNC)
check_function_exists(ftruncate HAVE_FTRUNCATE)
check_function_exists(getcwd HAVE_GETCWD)
check_function_exists(gettimeofday HAVE_GETTIMEOFDAY)
check_function_exists(localtime_r HAVE_LOCALTIME_R)
check_function_exists(memmove HAVE_MEMMOVE)
check_function_exists(memset HAVE_MEMSET)
check_function_exists(sqrt HAVE_SQRT)
check_function_exists(strcasecmp HAVE_STRCASECMP)
check_function_exists(strerror HAVE_STRERROR)
check_function_exists(strftime HAVE_STRFTIME)
check_function_exists(strncasecmp HAVE_STRNCASECMP)
check_function_exists(strstr HAVE_STRSTR)

# Checks for installed libraries
# AC_CHECK_LIB(sqlite3,sqlite3_prepare_v2,,AC_MSG_ERROR(['libsqlite3' is required but it doesn't seem to be installed on this system.]),-lm)
# AC_CHECK_LIB(z,inflateInit_,,AC_MSG_ERROR(['libz' is required but it doesn't seem to be installed on this system.]),-lm)

set(TARGET_CPU "arm")

message(STATUS "Generating Spatialite ${CMAKE_CURRENT_BINARY_DIR}/config.h")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/config.h)

####################################################################################################

include_directories(${CMAKE_CURRENT_BINARY_DIR})
# include_directories(${SPATIALITE_SOURCE_PATH})
include_directories(${SPATIALITE_SOURCE_PATH}/src/headers)
include_directories(${SPATIALITE_SOURCE_PATH}/src/topology)

include_directories(${CMAKE_SOURCE_DIR}/third-parties/sqlite/sqlite-amalgamation)

include_directories(${CMAKE_SOURCE_DIR}/third-parties/libiconv/libiconv-sources)
include_directories(${CMAKE_SOURCE_DIR}/third-parties/libiconv/libiconv-sources/include)
include_directories(${CMAKE_SOURCE_DIR}/third-parties/libiconv/libiconv-sources/lib)
include_directories(${CMAKE_SOURCE_DIR}/third-parties/libiconv/libiconv-sources/libcharset/include)
include_directories(${CMAKE_BINARY_DIR}/third-parties/libiconv)
include_directories(${CMAKE_BINARY_DIR}/third-parties/libiconv/include)

include_directories(${CMAKE_SOURCE_DIR}/third-parties/proj4/proj4-sources/src)

include_directories(${CMAKE_SOURCE_DIR}/third-parties/geos/geos-sources/include)
include_directories(${CMAKE_BINARY_DIR}/third-parties/geos/capi)
include_directories(${CMAKE_BINARY_DIR}/third-parties/geos/include)

####################################################################################################

SET(SPATIALITE_SOURCES
  connection_cache/alloc_cache.c
  # connection_cache/generator/code_generator.c
  connection_cache/gg_sequence.c
  control_points/gaia_control_points.c
  control_points/grass_crs3d.c
  control_points/grass_georef.c
  control_points/grass_georef_tps.c
  cutter/gaia_cutter.c
  dxf/dxf_load_distinct.c
  dxf/dxf_loader.c
  dxf/dxf_load_mixed.c
  dxf/dxf_parser.c
  dxf/dxf_writer.c
  gaiaaux/gg_sqlaux.c
  gaiaaux/gg_utf8.c
  gaiaexif/gaia_exif.c
  gaiageo/Ewkt.c
  gaiageo/geoJSON.c
  gaiageo/gg_advanced.c
  gaiageo/gg_endian.c
  gaiageo/gg_ewkt.c
  gaiageo/gg_extras.c
  gaiageo/gg_geodesic.c
  gaiageo/gg_geoJSON.c
  gaiageo/gg_geometries.c
  gaiageo/gg_geoscvt.c
  gaiageo/gg_gml.c
  gaiageo/gg_kml.c
  gaiageo/gg_matrix.c
  gaiageo/gg_relations.c
  gaiageo/gg_relations_ext.c
  gaiageo/gg_rttopo.c
  gaiageo/gg_shape.c
  gaiageo/gg_transform.c
  gaiageo/gg_vanuatu.c
  gaiageo/gg_voronoj.c
  gaiageo/gg_wkb.c
  gaiageo/gg_wkt.c
  gaiageo/gg_xml.c
  gaiageo/Gml.c
  gaiageo/Kml.c
  gaiageo/lemon/lemon_src/lemon.c
  gaiageo/lemon/lemon_src/lempar.c
  gaiageo/lex.Ewkt.c
  gaiageo/lex.GeoJson.c
  gaiageo/lex.Gml.c
  gaiageo/lex.Kml.c
  gaiageo/lex.VanuatuWkt.c
  gaiageo/vanuatuWkt.c
  geopackage/gaia_cvt_gpkg.c
  geopackage/gpkgAddGeometryColumn.c
  geopackage/gpkg_add_geometry_triggers.c
  geopackage/gpkg_add_spatial_index.c
  geopackage/gpkg_add_tile_triggers.c
  geopackage/gpkgBinary.c
  geopackage/gpkgCreateBaseTables.c
  geopackage/gpkgCreateTilesTable.c
  geopackage/gpkgCreateTilesZoomLevel.c
  geopackage/gpkgGetImageType.c
  geopackage/gpkg_get_normal_row.c
  geopackage/gpkg_get_normal_zoom.c
  geopackage/gpkgInsertEpsgSRID.c
  geopackage/gpkgMakePoint.c
  md5/gaia_md5.c
  md5/md5.c
  shapefiles/shapefiles.c
  shapefiles/validator.c
  spatialite/create_routing.c
  spatialite/dbobj_scopes.c
  spatialite/extra_tables.c
  spatialite/mbrcache.c
  spatialite/metatables.c
  spatialite/pause.c
  spatialite/se_helpers.c
  spatialite/spatialite.c
  spatialite/spatialite_init.c
  spatialite/srid_aux.c
  spatialite/statistics.c
  spatialite/table_cloner.c
  spatialite/virtualbbox.c
  spatialite/virtualdbf.c
  spatialite/virtualelementary.c
  spatialite/virtualfdo.c
  spatialite/virtualgeojson.c
  spatialite/virtualgpkg.c
  spatialite/virtualknn.c
  spatialite/virtualnetwork.c
  spatialite/virtualrouting.c
  spatialite/virtualshape.c
  spatialite/virtualspatialindex.c
  spatialite/virtualXL.c
  spatialite/virtualxpath.c
  srsinit/epsg_inlined_00.c
  srsinit/epsg_inlined_01.c
  srsinit/epsg_inlined_02.c
  srsinit/epsg_inlined_03.c
  srsinit/epsg_inlined_04.c
  srsinit/epsg_inlined_05.c
  srsinit/epsg_inlined_06.c
  srsinit/epsg_inlined_07.c
  srsinit/epsg_inlined_08.c
  srsinit/epsg_inlined_09.c
  srsinit/epsg_inlined_10.c
  srsinit/epsg_inlined_11.c
  srsinit/epsg_inlined_12.c
  srsinit/epsg_inlined_13.c
  srsinit/epsg_inlined_14.c
  srsinit/epsg_inlined_15.c
  srsinit/epsg_inlined_16.c
  srsinit/epsg_inlined_17.c
  srsinit/epsg_inlined_18.c
  srsinit/epsg_inlined_19.c
  srsinit/epsg_inlined_20.c
  srsinit/epsg_inlined_21.c
  srsinit/epsg_inlined_22.c
  srsinit/epsg_inlined_23.c
  srsinit/epsg_inlined_24.c
  srsinit/epsg_inlined_25.c
  srsinit/epsg_inlined_26.c
  srsinit/epsg_inlined_27.c
  srsinit/epsg_inlined_28.c
  srsinit/epsg_inlined_29.c
  srsinit/epsg_inlined_30.c
  srsinit/epsg_inlined_31.c
  srsinit/epsg_inlined_32.c
  srsinit/epsg_inlined_33.c
  srsinit/epsg_inlined_34.c
  srsinit/epsg_inlined_35.c
  srsinit/epsg_inlined_36.c
  srsinit/epsg_inlined_37.c
  srsinit/epsg_inlined_38.c
  srsinit/epsg_inlined_39.c
  srsinit/epsg_inlined_40.c
  srsinit/epsg_inlined_41.c
  srsinit/epsg_inlined_42.c
  srsinit/epsg_inlined_43.c
  srsinit/epsg_inlined_44.c
  srsinit/epsg_inlined_45.c
  srsinit/epsg_inlined_46.c
  srsinit/epsg_inlined_47.c
  srsinit/epsg_inlined_48.c
  srsinit/epsg_inlined_49.c
  srsinit/epsg_inlined_50.c
  srsinit/epsg_inlined_51.c
  srsinit/epsg_inlined_52.c
  srsinit/epsg_inlined_53.c
  srsinit/epsg_inlined_54.c
  srsinit/epsg_inlined_55.c
  srsinit/epsg_inlined_56.c
  srsinit/epsg_inlined_57.c
  srsinit/epsg_inlined_58.c
  srsinit/epsg_inlined_59.c
  srsinit/epsg_inlined_extra.c
  srsinit/epsg_inlined_prussian.c
  srsinit/epsg_inlined_wgs84_00.c
  srsinit/epsg_inlined_wgs84_01.c
  srsinit/epsg_update/auto_epsg.c
  srsinit/epsg_update/auto_epsg_ext.c
  srsinit/epsg_update/epsg_from_gdal.c
  srsinit/epsg_update/epsg_from_gdal-proj6.c
  srsinit/srs_init.c
  stored_procedures/stored_procedures.c
  topology/gaia_auxnet.c
  topology/gaia_auxtopo.c
  topology/gaia_auxtopo_table.c
  topology/gaia_netstmts.c
  topology/gaia_network.c
  topology/gaia_topology.c
  topology/gaia_topostmts.c
  topology/lwn_network.c
  topology/net_callbacks.c
  topology/topo_callbacks.c
  versioninfo/version.c
  virtualtext/virtualtext.c
  wfs/wfs_in.c
)

prepend(SPATIALITE_SOURCES ${SPATIALITE_SOURCE_PATH}/src ${SPATIALITE_SOURCES})

add_library(spatialite
  SHARED
  ${SPATIALITE_SOURCES}
)
# missing function crc32 : z
target_link_libraries(spatialite sqlite_at iconv qtcarto_proj4 geos z)
# libljson-c liblwgeom libxml2
