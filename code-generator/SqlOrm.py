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

from CppCodeGenerator import (Header, Source, ClassDefinition, Variable, MethodDefinition, Type)
from TemplateGenerator import TemplateGenerator

####################################################################################################

class Field:

    __TYPE_TO_CPP__ = {
        'integer': 'int',
        'text': 'QString',
        }

    ##############################################

    def __init__(self, name, data_type, sql_attributes):

        self._name = name
        self._data_type = data_type
        self._sql_attributes = sql_attributes

    ##############################################

    @property
    def name(self):
        return self._name

    @property
    def data_type(self):
        return self._data_type

    @property
    def cpp_data_type(self):
        return self.__TYPE_TO_CPP__[self._data_type]

    @property
    def sql_attributes(self):
        return self._sql_attributes

    ##############################################

    def to_sql(self):

        sql = ' '.join((self._name, self._data_type))
        if self._sql_attributes:
            sql += ' ' + self._sql_attributes
        return sql

    ##############################################

    def to_variable(self):

        return Variable(self._name, self.cpp_data_type)

####################################################################################################

class Schema:

    ##############################################

    def __init__(self, name, json_data):

        self._name = name
        self._fields = []
        self._parse_json_data(json_data)

    ##############################################

    def _parse_json_data(self, json_data):

        # for name, d in json_data.items():
        for name in sorted(json_data):
            d = json_data[name]
            field = Field(name, d['type'], d.get('sql_attributes', ''))
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
            'QtDebug',
        ))
        return sorted(include_classes)

    ##############################################

    def generate_source(self, name, generator_settings):

        class_name = self._name.title()

        members = [field.to_variable() for field in self]
        member_types = set([member.type for member in members])
        private_members = [Variable('bits', 'QBitArray')]
        all_members = private_members + members

        generator_comment = "This document was automatically generated on {}".format(datetime.datetime.now())

        header = Header(name, generator_settings)
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
        header.render('json-class.h', class_name=self._name.title(), members=members)
        header.new_line()
        header.footer()

        source = Source(name, generator_settings)
        source.comment(generator_comment)
        source.header()
        source.include(name, local=True)
        source.new_line()
        source.rule()
        source.new_line()
        source.comment('QC_BEGIN_NAMESPACE')
        source.render('json-class.cpp',
                      class_name=self._name.title(),
                      members=members, all_members=all_members, member_types=member_types)
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
        # header.render('data-stream-operator.h', class_name=class_name);
        # header.new_line()
        # header.render('debug.h', class_name=class_name);

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
        # source.new_line()
        # source.render('data-stream-operator.cpp', class_name=class_name, members=members, member_types=member_types);
        # source.new_line()
        # source.render('debug.cpp', class_name=class_name, members=members);

        return str(header), str(source)

    ##############################################

    def generate_source_using_template(self, name):

        members = [field.to_variable() for field in self]

        template_generator = TemplateGenerator()

        class_definition = dict(
            date=datetime.datetime.now(),
            filename=name,
            class_name=self._name.title(),
            base_classes=('QObject',),
            members=members,
            include_classes=self.includes(),
        )

        header = template_generator.render('json-class-header.jinja', class_definition)
        source = template_generator.render('class-source.jinja', class_definition)

        return header, source

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
