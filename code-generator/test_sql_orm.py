####################################################################################################
#
# $QTCARTO_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2016 Fabrice Salvaire
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
# $QTCARTO_END_LICENSE$
#
####################################################################################################

####################################################################################################

import json

from SqlOrm import SchemaRepository

from GeneratorSettings import generator_settings

####################################################################################################

json_schema = {
    'table1': {
        'field1': { 'type':'integer' },
        'field2': { 'type':'text' },
    }
}

json_data = json.dumps(json_schema, indent=4)
print(json_data)

schema_repository = SchemaRepository(json_data)

for table in schema_repository:
    print('Table', table.name)
    print(table.to_sql())
    header, source = table.generate_source(table.name, generator_settings)
    print(header)
    print(source)
