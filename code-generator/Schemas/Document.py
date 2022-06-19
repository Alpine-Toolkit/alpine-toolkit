####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

output = ('src', 'data_sources', 'document', 'document')

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
