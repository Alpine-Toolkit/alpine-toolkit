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

import pygit2 as git

from sqlalchemy import Enum
import sqlalchemy.sql.sqltypes as sqltypes
import c2corg_api.models.utils as utils

####################################################################################################

def git_head_hex(path):
    repository_path = git.discover_repository(path)
    repository = git.Repository(repository_path)
    commit = repository.revparse_single('HEAD')
    return commit.hex

####################################################################################################

def yield_module_attributes(module, *types):

    module_dict = module.__dict__
    for obj_name, obj in module_dict.items():
        if (not obj_name.startswith('_') and
            (not types or isinstance(obj, types))):
            yield obj_name, obj

####################################################################################################

def yield_list_in_module(module):
    yield from yield_module_attributes(module, (list, tuple))

def yield_dict_in_module(module):
    yield from yield_module_attributes(module, dict)

def yield_string_in_module(module):
    yield from yield_module_attributes(module, str)

def yield_sqlachemy_enum(module):
    yield from yield_module_attributes(module, Enum)

####################################################################################################

def printi(*args):
    print(' ', *args)

####################################################################################################

def table_to_json(cls):

    table_name = cls.__tablename__

    columns = {}
    for column in cls.__table__.columns:
        column_type = column.type
        # print('\n' + column.name)
        # print(column.__dict__)
        # print(column_type.__dict__)
        # printi(repr(column_type))
        # printi(type(column_type))
        json_column = {}
        json_column['type'] = column_type.__class__.__name__
        if column.default is not None:
            json_column['default'] = repr(column.default)
        if column.nullable:
            json_column['nullable'] = column.nullable
        if column.unique:
            json_column['unique'] = column.unique
        if column.primary_key:
            json_column['primary_key'] = column.primary_key
        if isinstance(column_type, utils.ArrayOfEnum):
            enum = column_type.item_type
            json_column['enum'] = enum.name
            json_column['enums'] = enum.enums
        else:
            # column_type.name
            json_column['sql'] = str(column_type)
            if isinstance(column_type, sqltypes.Enum):
                json_column['enum'] = column_type.name
                json_column['enums'] = column_type.enums

        columns[column.name] = json_column

    return table_name, columns
