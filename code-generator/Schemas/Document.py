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

output = ('src', 'document', 'document')

####################################################################################################

# from CodeGenerator.CppType import TypeConversion
from CodeGenerator.Orm import (SchemaRepository,
                               Schema, Field, ForeignKey,  RelationShip)
from CodeGenerator.Orm.StandardType import (Integer, UnsignedInteger,
                                            String, StringList, Url,
                                            DateTime, UnixDateTime)

####################################################################################################

# "name": "ffcam-refuges.json",
# "author": "Fabrice Salvaire",
# "version": 1,
# "date": "2017-04-21T18:28:11Z",
# "description": "Base de données  des refuges FFCAM",
# "url": "filer_public/ef/c7/efc713f4-e797-458c-9844-9bc3ae8fe3eb/ffcam-refuges.json",
# "size": 74840

####################################################################################################

class Document(Schema):

    __table_name__ = 'document'

    __order__ = (
        'id',
        'name',
        'author',
        'version',
        'date',
        'description',
        'url',
        'size',
    )

    id = Field(Integer, primary_key=True)
    name= Field(String)
    author= Field(String)
    version = Field(Integer)
    date = Field(UnixDateTime)
    description= Field(String)
    url = Field(Url)
    size = Field(Integer)

####################################################################################################

class DocumentDatabaseSchema(SchemaRepository):

    __schemas__ = (
        Document,
        )
