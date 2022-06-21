####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2022 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

add_library(qmlqtcartoplugin SHARED)

target_sources(qmlqtcartoplugin
  PRIVATE
    declarative_map_item.cpp
    geo_coordinate_animation.cpp
    map_gesture_area.cpp
    plugin_data.cpp
    qtcarto.cpp
)

target_include_directories(qmlqtcartoplugin
  PUBLIC
    ${Qt6Quick_PRIVATE_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(qmlqtcartoplugin
  PRIVATE
    Qt6::Qml
    Qt6::Quick
    Qt6::Positioning

    qtcarto
)

####################################################################################################

# https://doc.qt.io/qt-6/qt-add-qml-module.html
# qt_add_qml_module(
#     qmlqtcartoplugin
#     URI QtCarto
#     VERSION 1.0
#     [PAST_MAJOR_VERSIONS ...]
#     [STATIC | SHARED]
#     [PLUGIN_TARGET plugin_target]
#     [OUTPUT_DIRECTORY output_dir]
#     [RESOURCE_PREFIX resource_prefix]
#     [CLASS_NAME class_name]
#     [TYPEINFO typeinfo]
#     [IMPORTS ...]
#     [OPTIONAL_IMPORTS ...]
#     [DEPENDENCIES ...]
#     [IMPORT_PATH ...]
#     SOURCES ${qtcarto_files}
#     [QML_FILES ...]
#     [RESOURCES ...]
#     [OUTPUT_TARGETS out_targets_var]
#     [DESIGNER_SUPPORTED]
#     [FOLLOW_FOREIGN_VERSIONING]
#     [NO_PLUGIN_OPTIONAL]
#     [NO_CREATE_PLUGIN_TARGET]
#     NO_GENERATE_PLUGIN_SOURCE
#     [NO_GENERATE_QMLTYPES]
#     [NO_GENERATE_QMLDIR]
#     [NO_LINT]
#     [NO_CACHEGEN]
#     [NO_RESOURCE_TARGET_PATH]
#     [NO_IMPORT_SCAN]
# )
