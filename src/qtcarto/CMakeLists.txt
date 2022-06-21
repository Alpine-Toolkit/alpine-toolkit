####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

# add_subdirectory(openstreetmap)

# Generate in source !
# https://cmake.org/cmake/help/v3.6/module/FindProtobuf.html
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS openstreetmap/fileformat.proto openstreetmap/osmformat.proto)
# cmake --help-policy CMP0071
foreach(file IN LISTS
    fileformat.pb.cc
    fileformat.pb.h
    osmformat.pb.cc
    osmformat.pb.h
  )
  set_property(SOURCE ${file} PROPERTY SKIP_AUTOMOC ON)
endforeach()

####################################################################################################

add_library(qtcarto SHARED)

target_sources(qtcarto
  PRIVATE
    # geometry/polygon_seidler_triangulation.cpp

    cache/file_tile_cache.cpp
    cache/offline_cache.cpp
    cache/offline_cache_database.cpp
    cache/tile_image.cpp

    coordinate/mercator.cpp
    coordinate/projection.cpp
    coordinate/sexagesimal_angle.cpp
    coordinate/wgs84.cpp
    coordinate/debug_tools.cpp

    data_structure/pooled_string.cpp
    data_structure/simd.cpp

    database/database.cpp

    geo_data_format/gpx.cpp
    geo_data_format/route.cpp
    geo_data_format/waypoint.cpp
    geo_data_format/xml_reader.cpp
    geo_data_format/wkb.cpp

    geometry/line.cpp
    geometry/path.cpp
    geometry/polygon.cpp
    geometry/polygon_seidler_triangulation.cpp
    geometry/vector.cpp

    logging/logger.cpp

    map/location_circle_data.cpp
    map/map_event_router.cpp
    map/map_path_editor.cpp
    map/map_view.cpp
    map/path_property.cpp
    map/viewport.cpp
    map/decorated_path.cpp

    math/interval.cpp
    math/qc_math.cpp
    math/rational.cpp

    scene/location_circle_node.cpp
    scene/map_layer_scene.cpp
    scene/map_scene.cpp
    scene/path_node.cpp

    wmts/elevation_service_reply.cpp
    wmts/location_service_query.cpp
    wmts/location_service_reply.cpp
    wmts/network_reply.cpp
    wmts/providers/artic_web_map/artic_web_map_plugin.cpp
    wmts/providers/austria/austria_plugin.cpp
    wmts/providers/esri/esri_plugin.cpp
    wmts/providers/geoportail/geoportail_elevation_service_reply.cpp
    wmts/providers/geoportail/geoportail_license.cpp
    wmts/providers/geoportail/geoportail_location_service_reply.cpp
    wmts/providers/geoportail/geoportail_plugin.cpp
    wmts/providers/germany/germany_plugin.cpp
    wmts/providers/osm/osm_plugin.cpp
    wmts/providers/spain/spain_plugin.cpp
    wmts/providers/swiss_confederation/swiss_confederation_plugin.cpp
    wmts/tile_matrix_index.cpp
    wmts/tile_matrix_set.cpp
    wmts/tile_spec.cpp
    wmts/wmts_manager.cpp
    wmts/wmts_network_reply.cpp
    wmts/wmts_network_tile_fetcher.cpp
    wmts/wmts_plugin.cpp
    wmts/wmts_plugin_manager.cpp
    wmts/wmts_reply.cpp
    wmts/wmts_request_manager.cpp
    wmts/wmts_tile_fetcher.cpp

    ${CMAKE_SOURCE_DIR}/src/qml/QtCarto/declarative_map_item.cpp
    ${CMAKE_SOURCE_DIR}/src/qml/QtCarto/geo_coordinate_animation.cpp
    ${CMAKE_SOURCE_DIR}/src/qml/QtCarto/map_gesture_area.cpp
    ${CMAKE_SOURCE_DIR}/src/qml/QtCarto/plugin_data.cpp
)

# https://doc-snapshots.qt.io/qt6-dev/qtshadertools-build.html
qt6_add_shaders(qtcarto "qtcarto_shaders"
  BATCHABLE
  GLSL "460, 310es, 120es"
  NOHLSL
  NOMSL
  PREFIX "/scene/shaders/"
  FILES
  shaders/location_circle.frag
  shaders/location_circle.vert
  shaders/path.frag
  shaders/path.vert
  shaders/point.frag
  shaders/point.vert
)

target_include_directories(qtcarto
  PRIVATE
    ${CMAKE_BINARY_DIR} # for config.h
  PUBLIC
    ${Qt6Quick_PRIVATE_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/qml/QtCarto
)

target_link_libraries(qtcarto
  PRIVATE
    Qt6::Core
    Qt6::Core5Compat
    Qt6::Qml
    Qt6::Quick

    # ${PROJ4_LIBRARIES}
    proj

  PUBLIC
    Qt6::Gui
    Qt6::Network
    Qt6::Positioning
    Qt6::Sql

    alpine-toolkit-common
)

if (NOT ANDROID)
  target_sources(qtcarto
    PRIVATE
      openstreetmap/osm.cpp
      openstreetmap/osm_database.cpp
      openstreetmap/osm_pbf.cpp
      ${PROTO_SRCS}
      # ${PROTO_HDRS}
  )

target_link_libraries(qtcarto
  PRIVATE
    ${ZLIB_LIBRARY}
    ${PROTOBUF_LITE_LIBRARIES}
  )
endif()
