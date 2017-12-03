# -*- mode: qmake -*-

####################################################################################################

HEADERS += \
  cache/file_tile_cache.h \
  cache/offline_cache.h \
  cache/offline_cache_database.h \
  cache/tile_image.h

HEADERS += \
  coordinate/mercator.h \
  coordinate/projection.h \
  coordinate/sexagesimal_angle.h \
  coordinate/wgs84.h \
  coordinate/debug_tools.h

HEADERS += \
  database/database.h

HEADERS += \
  geo_data_format/gpx.h \
  geo_data_format/route.h \
  geo_data_format/waypoint.h \
  geo_data_format/wkb.cpp \
  geo_data_format/xml_reader.h

HEADERS += \
  geometry/line.h \
  geometry/path.h \
  geometry/polygon.h \
  geometry/vector.h

SOURCES += \
  logging/logger.h

HEADERS += \
  map/location_circle_data.h \
  map/map_event_router.h \
  map/map_path_editor.h \
  map/map_view.h \
  map/path_property.h \
  map/viewport.h \
  map/decorated_path.h

HEADERS += \
  math/interval.h \
  math/qc_math.h \
  math/rational.h

HEADERS += \
  scene/location_circle_material_shader.h \
  scene/location_circle_node.h \
  scene/map_scene.h \
  scene/path_material_shader.h \
  scene/path_node.h \
  scene/point_material_shader.h

HEADERS += \
  wmts/elevation_service_reply.h \
  wmts/location_service_query.h \
  wmts/location_service_reply.h \
  wmts/network_reply.h \
  wmts/providers/artic_web_map/artic_web_map_plugin.h \
  wmts/providers/austria/austria_plugin.h \
  wmts/providers/esri/esri_plugin.h \
  wmts/providers/geoportail/geoportail_elevation_service_reply.h \
  wmts/providers/geoportail/geoportail_license.h \
  wmts/providers/geoportail/geoportail_location_service_reply.h \
  wmts/providers/geoportail/geoportail_plugin.h \
  wmts/providers/germany/germany_plugin.h \
  wmts/providers/osm/osm_plugin.h \
  wmts/providers/spain/spain_plugin.h \
  wmts/providers/swiss_confederation/swiss_confederation_plugin.h \
  wmts/tile_matrix_index.h \
  wmts/tile_matrix_set.h \
  wmts/tile_spec.h \
  wmts/wmts_manager.h \
  wmts/wmts_network_reply.h \
  wmts/wmts_network_tile_fetcher.h \
  wmts/wmts_plugin.h \
  wmts/wmts_plugin_manager.h \
  wmts/wmts_reply.h \
  wmts/wmts_request_manager.h \
  wmts/wmts_tile_fetcher.h

####################################################################################################

SOURCES += \
  cache/file_tile_cache.cpp \
  cache/offline_cache.cpp \
  cache/offline_cache_database.cpp \
  cache/tile_image.cpp

SOURCES += \
  coordinate/debug_tools.cpp \
  coordinate/mercator.cpp \
  coordinate/projection.cpp \
  coordinate/sexagesimal_angle.cpp \
  coordinate/wgs84.cpp

SOURCES += \
  database/database.cpp

# data_structure/pooled_string.cpp
# data_structure/simd.cpp

SOURCES += \
  geo_data_format/gpx.cpp \
  geo_data_format/route.cpp \
  geo_data_format/waypoint.cpp \
  geo_data_format/wkb.cpp \
  geo_data_format/xml_reader.cpp

SOURCES += \
  geometry/line.cpp \
  geometry/path.cpp \
  geometry/polygon.cpp \
  geometry/polygon_seidler_triangulation.cpp \
  geometry/vector.cpp

SOURCES += \
  logging/logger.cpp

SOURCES += \
  map/decorated_path.cpp \
  map/location_circle_data.cpp \
  map/map_event_router.cpp \
  map/map_path_editor.cpp \
  map/map_view.cpp \
  map/path_property.cpp \
  map/viewport.cpp

SOURCES += \
  math/interval.cpp \
  math/qc_math.cpp \
  math/rational.cpp

# openstreetmap/osm.cpp
# openstreetmap/osm_database.cpp
# openstreetmap/osm_pbf.cpp
# ${PROTO_SRCS}

SOURCES += \
  scene/location_circle_material_shader.cpp \
  scene/location_circle_node.cpp \
  scene/map_layer_scene.cpp \
  scene/map_scene.cpp \
  scene/path_material_shader.cpp \
  scene/path_node.cpp \
  scene/point_material_shader.cpp

SOURCES += \
  wmts/elevation_service_reply.cpp \
  wmts/location_service_query.cpp \
  wmts/location_service_reply.cpp \
  wmts/network_reply.cpp \
  wmts/providers/artic_web_map/artic_web_map_plugin.cpp \
  wmts/providers/austria/austria_plugin.cpp \
  wmts/providers/esri/esri_plugin.cpp \
  wmts/providers/geoportail/geoportail_elevation_service_reply.cpp \
  wmts/providers/geoportail/geoportail_license.cpp \
  wmts/providers/geoportail/geoportail_location_service_reply.cpp \
  wmts/providers/geoportail/geoportail_plugin.cpp \
  wmts/providers/germany/germany_plugin.cpp \
  wmts/providers/osm/osm_plugin.cpp \
  wmts/providers/spain/spain_plugin.cpp \
  wmts/providers/swiss_confederation/swiss_confederation_plugin.cpp \
  wmts/tile_matrix_index.cpp \
  wmts/tile_matrix_set.cpp \
  wmts/tile_spec.cpp \
  wmts/wmts_manager.cpp \
  wmts/wmts_network_reply.cpp \
  wmts/wmts_network_tile_fetcher.cpp \
  wmts/wmts_plugin.cpp \
  wmts/wmts_plugin_manager.cpp \
  wmts/wmts_reply.cpp \
  wmts/wmts_request_manager.cpp \
  wmts/wmts_tile_fetcher.cpp
