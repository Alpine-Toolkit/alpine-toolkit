#! /usr/bin/env python3
# -*- Python -*-

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

output = ('src', 'refuge', 'refuge_schema')

####################################################################################################

# from CodeGenerator.CppType import TypeConversion

from CodeGenerator.Orm import SchemaRepository, Schema, Field, ComputedField
from CodeGenerator.Orm.CustomType import JsonGeoCoordinate
from CodeGenerator.Orm.StandardType import Integer, Char, String
from CodeGenerator.Template import CustomCode

####################################################################################################

class Refuge(Schema):

    __table_name__ = 'refuge'

    __order__ = (
        'id',
        'name',
        'short_name',
        'altitude',
        'description',
        'owner',
        'guardian',
        'picture_path',
        'coordinate',
        'number_of_places',
        'region',
        'url',
        'phone',
    )

    id = Field(Integer, primary_key=True)
    name = Field(String)
    short_name = Field(String)
    altitude = Field(Integer)
    description = Field(String)
    owner = Field(String)
    guardian = Field(String)
    picture_path = Field(String)
    coordinate = Field(JsonGeoCoordinate)
    number_of_places = Field(String)
    region = Field(String)
    url = Field(String)
    phone = Field(String)

    first_letter = ComputedField(Char)

    __has_post_init__ = True

    __custom_code__ = {
        # Fixme: Mixin ???
        'cls_decl': CustomCode("""
public:
  bool operator<(const {{schema.cls_name}} & other) const;

  QChar first_letter() const { return m_first_letter; }

private slots:
  void set_first_letter();

private:
  QChar m_first_letter;
"""),
    }

####################################################################################################

class RefugeDatabaseSchema(SchemaRepository):

    __schemas__ = (
        Refuge,
    )
