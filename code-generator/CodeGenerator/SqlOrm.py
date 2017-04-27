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

from .CppCodeGenerator import (Header, Source, ClassDefinition, Variable, MethodDefinition, Type)

####################################################################################################

class Field:

    __TYPE_TO_CPP__ = {
        'integer': 'int',
        'text': 'QString',
        }

    ##############################################

    def __init__(self, name,
                 sql_type,
                 sql_qualifier='',
                 qt_type=None,
                 sql_name=None,
                 json_name=None,
                 title='',
                 description='',
    ):

        self._name = name
        self._sql_type = sql_type
        self._sql_qualifier = sql_qualifier

        if qt_type is None:
            qt_type = self.__TYPE_TO_CPP__[sql_type]
        self._qt_type = qt_type

        if sql_name is None:
            sql_name = name
        self._sql_name = sql_name

        if json_name is None:
            json_name = name
        self._json_name = json_name

        self._title = title
        self._description = description

        self._variable = Variable(self._name, self._qt_type)

    ##############################################

    @property
    def name(self):
        return self._name

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

    ##############################################

    def to_sql(self):

        sql = ' '.join((self._name, self._sql_type))
        if self._sql_attributes:
            sql += ' ' + self._sql_attributes
        return sql

####################################################################################################

class Schema:

    ##############################################

    def __init__(self, name, json_data):

        self._name = name
        self._fields = []
        self._parse_json_data(json_data)

    ##############################################

    def _parse_json_data(self, json_data):

        for field in json_data:
            field = Field(field['name'],
                          field['type'],
                          field.get('sql_attributes', ''),
                          field.get('qt_type', None))
            self._fields.append(field)

    ##############################################

    @property
    def name(self):
        return self._name

    ##############################################

    def __iter__(self):

        return iter(self._fields)

    ##############################################

    def to_sql(self):

        sql = 'CREATE TABLE {} ('.format(self._name)
        fields = [field.to_sql() for field in self]
        sql += ', '.join(fields)
        sql += ')'
        return sql

    ##############################################

    @staticmethod
    def includes(members):

        include_classes = set([member.type for member in members if member.type.startswith('Q')])
        include_classes |= set((
            # 'QObject',
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

    def generate_source(self, filename, generator_settings):

        class_name = self._name # .title()

        members = [field.variable for field in self]
        member_types = sorted(set([member.type for member in members]))
        private_members = [Variable('bits', 'QBitArray', value=len(members))]
        all_members = private_members + members

        generator_comment = "This file was automatically generated by SqlOrm" # on {}".format(datetime.datetime.now())

        header = Header(filename, generator_settings)
        header.cpp_mode()
        header.comment(generator_comment)
        header.header()
        for include in self.includes(all_members):
            header.include(include)
        header.new_line()
        header.include('database/schema.h', local=True)
        header.new_line()
        header.rule()
        header.new_line()
        header.render('json-class.h', class_name=class_name, members=members)
        header.new_line()
        header.footer()

        source = Source(filename, generator_settings)
        source.comment(generator_comment)
        source.header()
        source.include(filename, local=True)
        source.new_line()
        source.rule()
        source.new_line()
        source.comment('QC_BEGIN_NAMESPACE')
        source.render('json-class.cpp',
                      class_name=class_name,
                      members=members, all_members=all_members, member_types=member_types, fields=self._fields)
        source.new_line()
        source.comment('QC_END_NAMESPACE')
        source.footer()

        # class_definition = ClassDefinition(class_name, 'QObject',
        #                                    members,
        #                                    private_members=private_members,
        #                                    generator_settings=generator_settings)
        # class_definition.begin()
        # for member in members:
        #     class_definition.property(member)
        # class_definition.public()
        # class_definition.render('member-enum.h', members=members)
        # class_definition.public()
        # class_definition.ctor()
        # class_definition.json_ctor()
        # class_definition.dtor()
        # class_definition.new_line()
        # class_definition.copy_operator()
        # for member in members:
        #     class_definition.new_line()
        #     class_definition.inline_getter(member)
        #     # class_definition.inline_setter(member)
        #     class_definition.setter(member)
        # class_definition.new_line()
        # class_definition.json_serializer()
        # class_definition.signals()
        # for member in members:
        #     class_definition.property_changed_signal(member)
        # class_definition.private()
        # for member in class_definition.all_members:
        #     class_definition.member(member)
        # class_definition.close()
        # header.append(class_definition)

        # class_implementation = class_definition.to_implementation()
        # class_implementation.ctor()
        # class_implementation.new_line()
        # class_implementation.copy_ctor()
        # class_implementation.new_line()
        # class_implementation.json_ctor()
        # class_implementation.new_line()
        # class_implementation.dtor()
        # class_implementation.new_line()
        # class_implementation.copy_operator_ctor()
        # for member in members:
        #     class_implementation.new_line()
        #     class_implementation.setter(member)
        # class_implementation.new_line()
        # class_implementation.json_serializer()
        # source.append(class_implementation)

        return str(header), str(source)

####################################################################################################

class SchemaRepository:

    ##############################################

    def __init__(self, json_data):

        self._tables = []

        json_dict = json.loads(json_data)
        for name, d in json_dict.items():
            table = Schema(name, d)
            self._tables.append(table)

    ##############################################

    def __iter__(self):

        return iter(self._tables)
