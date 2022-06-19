####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

output = ('src', 'data_sources', 'bleaudb', 'bleau_schema')

####################################################################################################

from CodeGenerator.Orm import (SchemaRepository,
                               Schema, Field, ForeignKey,  RelationShip)
from CodeGenerator.Orm.StandardType import (Integer, UnsignedInteger,
                                            String, StringList, Url,
                                            DateTime)
from CodeGenerator.Orm.CustomType import JsonGeoCoordinate

####################################################################################################

# "places": [
#   {
#     "category": "point d'eau",
#     "coordinate": {
#       "latitude": 48.41661764548987,
#       "longitude": 2.725392699242297
#     },
#     "name": "Fontaine d'Avon",
#     "note": null
#   }, ... ]

# "boulders": [
#   {
#     "comment": "mur.",
#     "coordinate": null,
#     "grade": "5-",
#     "name": "",
#     "number": 1
#   }, ... ]

# "circuits": [
#   {
#     "boulders": [ ... ]
#     "colour": "rouge",
#     "coordinate": {
#       "latitude": 48.377501,
#       "longitude": 2.519742
#     "creation_date": null,
#     "gestion": "ONF77",
#     "grade": "TD-",
#     "massif": "91_1",
#     "note": null,
#     "number": 1,
#     "opener": "...",
#     "refection_date": 2011,
#     "refection_note": null,
#     "status": "liste SNE",
#     "topos": [
#       "http://..."
#     ]
# },

# "massifs": [
#   {
#     "acces": "...",
#     "alternative_name": null,
#     "chaos_type": "E/D",
#     "coordinate": {
#       "latitude": 48.37722,
#       "longitude": 2.51919
#     },
#     "name": "91_1",
#     "note": null,
#     "parcelles": "135 141 TP",
#     "rdv": "...",
#     "secteur": "Trois Pignons",
#     "velo": "..."
#   }, ... ]

####################################################################################################

class BleauPlace(Schema):

    __table_name__ = 'place'

    __order__ = (
        'id',
        'coordinate',
        'name',
        'category',
        'note',
    )

    id = Field(Integer, primary_key=True, on_json=False)
    coordinate = Field(JsonGeoCoordinate)
    name = Field(String)
    category = Field(String) # BleauPlaceCategory = QString
    note = Field(String)

####################################################################################################

class BleauMassif(Schema):

    __table_name__ = 'massif'

    __order__ = (
        'id',
        'coordinate',
        'name',
        'access',
        'alternative_name',
        'chaos_type',
        'note',
        'parcelles',
        'rdv',
        'secteur',
        'velo',
    )

    id = Field(Integer, primary_key=True, on_json=False)
    coordinate = Field(JsonGeoCoordinate)
    name = Field(String) # unique=True
    access = Field(String)
    alternative_name = Field(String)
    chaos_type = Field(String) # BleauChaosType
    note = Field(String)
    parcelles = Field(String)
    rdv = Field(String)
    secteur = Field(String)
    velo = Field(String)

    circuits = RelationShip('BleauCircuit', back_populates='massif')

####################################################################################################

class BleauBoulder(Schema):

    __table_name__ = 'boulder'

    __order__ = (
        'id',
        'coordinate',
        'name',
        'comment',
        'grade',
        'number',
        'circuit_id',
    )

    id = Field(Integer, primary_key=True, on_json=False)
    coordinate = Field(JsonGeoCoordinate)
    name = Field(String)
    comment = Field(String)
    grade = Field(String) # BleauGrade
    number = Field(String) # BleauWayNumber

    circuit_id = Field(Integer, ForeignKey('circuit.id'), on_json=False)
    circuit = RelationShip('BleauCircuit', back_populates='boulders')

####################################################################################################

class BleauCircuit(Schema):

    __table_name__ = 'circuit'

    __order__ = (
        'id',
        'coordinate',
        'colour',
        'creation_date',
        'gestion',
        'grade',
        'massif_id',
        'note',
        'number',
        'opener',
        'refection_date',
        'refection_note',
        'status',
        'topos',
        )

    id = Field(Integer, primary_key=True, on_json=False)
    coordinate = Field(JsonGeoCoordinate)
    colour = Field(String)
    creation_date = Field(Integer) # UnsignedInteger
    gestion = Field(String)
    grade = Field(String) # BleauAlpineGrade
    massif_id = Field(Integer, ForeignKey('massif.id'), on_json=False) # Fixme: JSON massif/string vs massif_id/int
    note = Field(String)
    number = Field(Integer) # UnsignedInteger
    opener = Field(String) # BleauOpeners
    refection_date = Field(Integer) # UnsignedInteger
    refection_note = Field(String) # BleauRefectionNote
    status = Field(String)
    topos = Field(StringList)

    massif = RelationShip(BleauMassif, back_populates='circuits')
    boulders = RelationShip(BleauBoulder, back_populates='circuit')

####################################################################################################

class BleauSchema(SchemaRepository):

    __schemas__ = (
        BleauPlace,
        BleauMassif,
        BleauCircuit,
        BleauBoulder,
    )
