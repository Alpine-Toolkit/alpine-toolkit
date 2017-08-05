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

output = ('src', 'third_party_license', 'license_schema')

####################################################################################################

from CodeGenerator.Orm import (SchemaRepository,
                               Schema, Field, ForeignKey,  RelationShip)
from CodeGenerator.Orm.StandardType import (Integer, UnsignedInteger,
                                            String, StringList, Url,
                                            DateTime)

####################################################################################################

class ThirdPartyLicense(Schema):

    __table_name__ = 'third_party_license'

    __order__ = (
        'id',
        'third_party_name',
        'third_party_url',
        'third_party_version',
        'license_name',
        'license_url',
        'license_text',
    )

    id = Field(Integer, primary_key=True, on_json=False)
    third_party_name = Field(String)
    third_party_url = Field(Url)
    third_party_version = Field(String)
    license_name = Field(String)
    license_url = Field(Url)
    license_text = Field(String)

####################################################################################################

class ThirdPartyLicenseSchema(SchemaRepository):

    __schemas__ = (
        ThirdPartyLicense,
    )
