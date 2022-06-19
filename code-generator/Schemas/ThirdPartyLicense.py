####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

output = ('src', 'data_sources', 'third_party_license', 'third_party_license_schema')

####################################################################################################

from CodeGenerator.Orm import (SchemaRepository,
                               Schema, Field, ForeignKey,  RelationShip)
from CodeGenerator.Orm.StandardType import (Integer, UnsignedInteger, Boolean,
                                            String, StringList, Url,
                                            DateTime)

####################################################################################################

class ThirdPartyLicense(Schema):

    __table_name__ = 'third_party_license'

    __order__ = (
        'id',
        'used',
        'show',
        'third_party_name',
        'third_party_url',
        'third_party_version',
        'license_name',
        'license_url',
        'license_text',
        'license_note',
    )

    id = Field(Integer, primary_key=True, on_json=False)
    third_party_name = Field(String)
    used = Field(Boolean)
    show = Field(Boolean)
    third_party_url = Field(Url)
    third_party_version = Field(String)
    license_name = Field(String)
    license_url = Field(Url)
    license_text = Field(String)
    license_note = Field(String)

####################################################################################################

class ThirdPartyLicenseDatabaseSchema(SchemaRepository):

    __schemas__ = (
        ThirdPartyLicense,
    )
