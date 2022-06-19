####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

from .FieldType import FieldType
from CodeGenerator.CppType import TypeConversion

####################################################################################################

class Boolean(FieldType):
    def __init__(self):
        FieldType.__init__(self, sql_type='integer', qt_type='bool')

class Integer(FieldType):
    def __init__(self):
        FieldType.__init__(self, sql_type='integer', qt_type='int')

class UnsignedInteger(FieldType):
    def __init__(self):
        FieldType.__init__(self, sql_type='integer', qt_type='unsigned int')

class Real(FieldType):
    def __init__(self):
        FieldType.__init__(self, sql_type='real', qt_type='qreal')

class Char(FieldType):
    def __init__(self):
        FieldType.__init__(self, sql_type='text', qt_type='QChar')

class String(FieldType):
    def __init__(self):
        FieldType.__init__(self, sql_type='text', qt_type='QString')

class StringList(FieldType):
    def __init__(self):
        FieldType.__init__(self, sql_type='text', qt_type='QStringList')

class Url(FieldType):
    def __init__(self):
        FieldType.__init__(self, sql_type='text', qt_type='QUrl')

class Date(FieldType):
    def __init__(self):
        FieldType.__init__(self, sql_type='text', qt_type='QDate')

class DateTime(FieldType):
    def __init__(self):
        FieldType.__init__(self, sql_type='text', qt_type='QDateTime')

class GeoCoordinate(FieldType):
    def __init__(self):
        FieldType.__init__(self, sql_type='text', qt_type='QGeoCoordinate')

class ByteArray(FieldType):
    def __init__(self):
        FieldType.__init__(self, sql_type='blob', qt_type='QByteArray')

class Variant(FieldType):
    def __init__(self):
        FieldType.__init__(self, sql_type='blob', qt_type='QVariant')

####################################################################################################

class IsoDateTime(DateTime):

    __type_conversion__ = TypeConversion(
        # Fixme: handle None
        cast_from_json = 'orm_type_conversion::load_datetime',
        cast_to_json = 'orm_type_conversion::dump_datetime',
        cast_from_sql = 'orm_type_conversion::load_sql_datetime',
        cast_to_sql = 'orm_type_conversion::dump_sql_datetime'
    )

class UnixDateTime(FieldType):

    __type_conversion__ = TypeConversion(
        # Fixme: handle None
        cast_from_json = 'orm_type_conversion::load_datetime',
        cast_to_json = 'orm_type_conversion::dump_datetime',
        cast_from_sql = 'orm_type_conversion::load_sql_datetime_as_epoch',
        cast_to_sql = 'orm_type_conversion::dump_sql_datetime_as_epoch'
    )

    ##############################################

    def __init__(self):
        FieldType.__init__(self, sql_type='integer', qt_type='QDateTime')
