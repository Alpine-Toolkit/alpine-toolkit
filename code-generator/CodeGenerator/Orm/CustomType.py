####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

from .StandardType import GeoCoordinate
from CodeGenerator.CppType import TypeConversion

####################################################################################################

class JsonGeoCoordinate(GeoCoordinate):
    # Fixme: spatialite
    __type_conversion__ = TypeConversion(
        cast_from_json = 'orm_type_conversion::load_json_coordinate',
        cast_to_json = 'orm_type_conversion::dump_json_coordinate',
        # cast_from_sql = 'orm_type_conversion::load_sql_coordinate',
        # cast_to_sql = 'orm_type_conversion::dump_sql_coordinate',
        cast_from_sql = 'orm_type_conversion::load_wkb_point',
        cast_to_sql = 'orm_type_conversion::dump_wkb_point',
    )
    __sql_column_ctor__ = "SELECT AddGeometryColumn('{0.table_name}', '{0.name}', 4326, 'POINT', 'XY');"
    __sql_value_ctor__ = 'ST_GeomFromWKB()'
    __sql_value_getter__ = 'ST_AsBinary(QoSqlField((QLatin1String("{0.sql_name}"))))' # Fixme
