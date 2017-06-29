####################################################################################################
#
# $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
#
# This file is part of the QtCarto library.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# $ALPINE_TOOLKIT_END_LICENSE$
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
    __sql_value_getter__ = 'ST_AsBinary(QcSqlField((QLatin1String("{0.sql_name}"))))' # Fixme
