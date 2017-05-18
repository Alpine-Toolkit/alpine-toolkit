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

output = ('src', 'settings', 'settings_schema')

####################################################################################################

from CodeGenerator.Orm import SchemaRepository, Schema, Field, ForeignKey, RelationShip
from CodeGenerator.Orm.StandardType import Integer, String, Variant

####################################################################################################

class Directory(Schema):

    __table_name__ = 'directory'

    __order__ = (
        'id',
        'name',
        'parent',
        )

    id = Field(Integer, primary_key=True)
    name = Field(String)
    parent = Field(Integer, ForeignKey('directory.id'))

    keys = RelationShip('Key', order_by='Key.name', back_populates='directory')

####################################################################################################

class Key(Schema):

    __table_name__ = 'key'

    __order__ = (
        'id',
        'name',
        'directory_id',
        'value',
        )

    id = Field(Integer, primary_key=True)
    name = Field(String) # pk ???
    directory_id = Field(Integer, ForeignKey('directory.id'))
    value = Field(Variant)

    directory = RelationShip('Directory', back_populates='keys')

####################################################################################################

class BlogApplicationSchema(SchemaRepository):

    __schemas__ = (
        Directory,
        Key,
    )
