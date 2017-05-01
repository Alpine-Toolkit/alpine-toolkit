####################################################################################################
#
# $QTCARTO_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2016 Fabrice Salvaire
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
# $QTCARTO_END_LICENSE$
#
####################################################################################################

####################################################################################################

import datetime
import json
import os

from .CppCodeGenerator import (Variable, Type,
                               ClassDefinition, MethodDefinition,
                               Header, Source)
from .CppType import TypeConversion

####################################################################################################

class Field:

    __context__ = None

    ##############################################

    def __init__(self, name,
                 sql_type,
                 qt_type,
                 sql_qualifier='',
                 sql_name=None,
                 json_name=None,
                 title='',
                 description='',
    ):

        self._sql_type = sql_type
        self._qt_type = qt_type
        self._sql_qualifier = sql_qualifier

        if sql_name is None:
            sql_name = name
        self._sql_name = sql_name

        if json_name is None:
            json_name = name
        self._json_name = json_name

        self._title = title
        self._description = description

        self.name = name

    ##############################################

    def __repr__(self):

        return '{0.__class__.__name__} {0._name}'.format(self)

    ##############################################

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, name):
        self._name = name
        self._variable = Variable(self._name, self._qt_type, context=self.__context__)
        if self._sql_name is None:
            self._sql_name = name
        if self._json_name is None:
            self._json_name = name

    ##############################################

    @property
    def sql_type(self):
        return self._sql_type

    @property
    def sql_qualifier(self):
        return self._sql_qualifier

    @property
    def qt_type(self):
        return self._qt_type

    @property
    def sql_name(self):
        return self._sql_name

    @property
    def json_name(self):
        return self._json_name

    @property
    def title(self):
        return self._title

    @property
    def description(self):
        return self._description

    @property
    def variable(self):
        return self._variable

    @property
    def context(self):
        return self.__context__

    ##############################################

    def to_sql(self):

        sql = ' '.join((self._name, self._sql_type))
        if self._sql_attributes:
            sql += ' ' + self._sql_attributes
        return sql

####################################################################################################

class IntegerField(Field):
    def __init__(self, **kwargs):
        Field.__init__(self, name=None, sql_type='integer', qt_type='int', **kwargs)

class UnsignedIntegerField(Field):
    def __init__(self, **kwargs):
        Field.__init__(self, name=None, sql_type='integer', qt_type='unsigned int', **kwargs)

class RealField(Field):
    def __init__(self, **kwargs):
        Field.__init__(self, name=None, sql_type='real', qt_type='qreal', **kwargs)

class StringField(Field):
    def __init__(self, **kwargs):
        Field.__init__(self, name=None, sql_type='text', qt_type='QString', **kwargs)

class StringListField(Field):
    def __init__(self, **kwargs):
        Field.__init__(self, name=None, sql_type='text', qt_type='QStringList', **kwargs)

class UrlField(Field):
    def __init__(self, **kwargs):
        Field.__init__(self, name=None, sql_type='text', qt_type='QUrl', **kwargs)

class DateTimeField(Field):
    def __init__(self, **kwargs):
        Field.__init__(self, name=None, sql_type='text', qt_type='QDateTime', **kwargs)

class GeoCoordinateField(Field):
    def __init__(self, **kwargs):
        Field.__init__(self, name=None, sql_type='text', qt_type='QGeoCoordinate', **kwargs)

####################################################################################################

class IsoDateTimeField(DateTimeField):

    __context__ = TypeConversion(
        # Fixme: handle None
        cast_from_json = 'json_helper::load_datetime',
        cast_to_json = 'json_helper::dump_datetime',
        cast_from_sql_variant = 'json_helper::load_sql_datetime',
        cast_to_sql_variant = 'json_helper::dump_sql_datetime'
    )


class UnixDateTimeField(Field):

    __context__ = TypeConversion(
        # Fixme: handle None
        cast_from_json = 'json_helper::load_datetime',
        cast_to_json = 'json_helper::dump_datetime',
        cast_from_sql_variant = 'json_helper::load_sql_datetime_as_epoch',
        cast_to_sql_variant = 'json_helper::dump_sql_datetime_as_epoch'
    )

    ##############################################

    def __init__(self, **kwargs):
        Field.__init__(self, name=None, sql_type='integer', qt_type='QDateTime', **kwargs)

####################################################################################################

class Schema:

    # Fixme: name clash !

    __order__ = None
    __table_name__ = None
    __custom_header__ = None
    __custom_source__ = None

    ##############################################

    def __init__(self):

        self._name = self.__class__.__name__

        self._fields = []
        d = self.__class__.__dict__
        if self.__order__ is not None:
            field_names = self.__order__
        else:
            field_names = d.keys()
        for name in field_names:
            field = d[name]
            if isinstance(field, Field):
                field.name  = name
                self._fields.append(field)

        self._members = [field.variable for field in self._fields]
        self._member_types = sorted(set([member.type for member in self._members]))
        self._private_members = [Variable('bits', 'QBitArray', value=len(self._members))]
        self._all_members = self._private_members + self._members

    ##############################################

    @property
    def cls_name(self): # to don't clash with "name" field
        return self._name

    @property
    def table_name(self):
        return self.__table_name__

    ##############################################

    def __iter__(self):

        return iter(self._fields)

    ##############################################

    def to_sql(self):

        sql = 'CREATE TABLE {} ('.format(self.__table_name__)
        fields = [field.to_sql() for field in self]
        sql += ', '.join(fields)
        sql += ')'
        return sql

    ##############################################

    @property
    def includes(self):

        include_classes = set([member.type for member in self._members if member.type.startswith('Q')])
        include_classes |= set((
            # 'QObject',
            'QBitArray',
            'QDataStream',
            'QJsonObject',
            'QSqlQuery',
            'QSqlRecord',
            'QVariant',
            'QVariantList',
            'QtDebug',
        ))
        return sorted(include_classes)

    ##############################################

    def generate_header(self, header):

        header.render('row-class.h',
                      schema=self,
                      class_name=self._name,
                      members=self._members,
                      custom_header=self.__custom_header__
        )

    ##############################################

    def generate_source(self, source):

        source.render('row-class.cpp',
                      schema=self,
                      class_name=self._name,
                      members=self._members,
                      all_members=self._all_members,
                      member_types=self._member_types,
                      custom_source=self.__custom_source__
        )

####################################################################################################

class SchemaRepository:

    ##############################################

    def __init__(self, name, *schemas):

        self._name = name
        self._schemas = [cls() for cls in schemas]

    ##############################################

    @property
    def name(self):
        return self._name

    ##############################################

    def __iter__(self):

        return iter(self._schemas)

    ##############################################

    @property
    def includes(self):

        headers = set()
        for schema in self:
            headers |= set(schema.includes)
        return sorted(headers)

    ##############################################

    def generate_source(self,
                        filename,
                        generator_settings,
                        pre_header=None, post_header=None,
                        pre_source=None, post_source=None):

        generator_comment = "This file was automatically generated by SqlOrm" # on {}".format(datetime.datetime.now())

        header = Header(filename, generator_settings)
        header.cpp_mode()
        header.comment(generator_comment)
        header.header()
        for include in self.includes:
            header.include(include)
        header.new_line()
        header.include('database/schema.h', local=True)
        header.include('database/database_schema.h', local=True)
        header.new_line()
        header.rule()
        header.new_line()
        if pre_header is not None:
            header.render(pre_header)
            header.new_line()
            header.rule()
            header.new_line()
        for schema in self:
            schema.generate_header(header)
            header.new_line()
            header.rule()
            header.new_line()
        header.render('schema.h',
                      database_schema=self)
        header.new_line()
        header.rule()
        header.new_line()
        if post_header is not None:
            header.render(post_header)
            header.new_line()
            header.rule()
            header.new_line()
        header.footer()

        source = Source(filename, generator_settings)
        source.comment(generator_comment)
        source.header()
        source.include(filename, local=True)
        # Fixme: auto ? / function in CppCodeGenerator ?
        #! if 'QStringList' in self.includes:
        source.new_line()
        source.include('database/json_helper.h', local=True)
        source.new_line()
        source.rule()
        source.new_line()
        source.comment('QC_BEGIN_NAMESPACE')
        source.new_line()
        if pre_source is not None:
            source.render(pre_source)
        for schema in self:
            schema.generate_source(source)
            source.new_line()
            source.rule()
            source.new_line()
        source.render('schema.cpp',
                      database_schema=self)
        source.new_line()
        source.rule()
        source.new_line()
        if post_source is not None:
            source.render(post_source)
            source.new_line()
            source.rule()
            source.new_line()
        source.comment('QC_END_NAMESPACE')
        source.footer()

        return str(header), str(source)

    ##############################################

    def write_source(self, path, *args, **kwargs):

        filename = os.path.basename(path)
        header, source = self.generate_source(filename, *args, **kwargs)

        with open(path + '.h', 'w') as f:
            f.write(str(header))
        with open(path + '.cpp', 'w') as f:
            f.write(str(source))

