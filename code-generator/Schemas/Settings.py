####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

output = ('src', 'data_sources', 'settings', 'settings_schema')

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
