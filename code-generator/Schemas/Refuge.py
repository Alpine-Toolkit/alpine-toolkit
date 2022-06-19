#! /usr/bin/env python3
# -*- Python -*-

####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

output = ('src', 'data_sources', 'refuge', 'refuge_schema')

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
