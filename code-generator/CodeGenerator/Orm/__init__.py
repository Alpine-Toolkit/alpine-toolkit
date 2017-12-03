####################################################################################################
#
# $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
#
# This file is part of the Alpine Toolkit software.
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

from enum import Enum
import inspect
import logging
import os

from .FieldType import FieldType
from .StandardType import Integer
from CodeGenerator.CppType import Variable
from CodeGenerator.Template import TemplateEnvironment, TemplateAggregator

####################################################################################################

_module_logger = logging.getLogger(__name__)

####################################################################################################

class ForeignKey:

    ##############################################

    def __init__(self, column):

        table, column = column.split('.')
        self._table = table
        self._column = column

    ##############################################

    @property
    def table(self):
        return self._table

    @property
    def column(self):
        return self._column

    @property
    def dot_syntax(self):
        # Fixme: name
        return self._table + '.' + self._column

####################################################################################################

class Field:

    _logger = _module_logger.getChild('Field')

    ##############################################

    def __init__(self, *args, **kwargs):

        self._type = None
        self._foreign_key = None
        for arg in args:
            if inspect.isclass(arg):
                if issubclass(arg, FieldType):
                    self._type = arg()
            else:
                if isinstance(arg, ForeignKey):
                    self._foreign_key = arg
        if self._type is None:
            raise ValueError()

        self._sql_name = kwargs.get('sql_name', None)
        self._autoincrement = kwargs.get('autoincrement', False)
        self._default = kwargs.get('default', None)
        self._is_primary_key = kwargs.get('primary_key', False)
        if self._is_primary_key:
            self._nullable = False;
        else:
            self._nullable = kwargs.get('nullable', True)
        self._unique = kwargs.get('unique', False)

        self._json_name = kwargs.get('json_name', None)
        self._on_json = kwargs.get('on_json', True)

        self._title = kwargs.get('title', '')
        self._description = kwargs.get('description', '')

        self._parent_schema = None
        self._position = None
        self._variable = None

    ##############################################

    def __repr__(self):

        return '{0.__class__.__name__} {0._name}'.format(self)

    ##############################################

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, name):
        # Name is set afterwards
        self._name = name
        self._variable = Variable(self._name, self.qt_type, type_conversion=self.type_conversion)
        if self._sql_name is None:
            self._sql_name = name
        if self._json_name is None:
            self._json_name = name

    ##############################################

    @property
    def parent_schema(self):
        return self._parent_schema

    @property
    def table_name(self):
        return self._parent_schema.table_name

    @parent_schema.setter
    def parent_schema(self, value):
        self._parent_schema = value

    ##############################################

    @property
    def position(self):
        return self._position

    @position.setter
    def position(self, value):
        self._position = value

    ##############################################

    @property
    def variable(self):
        return self._variable

    @property
    def qt_type(self):
        return self._type.qt_type

    @property
    def type_conversion(self):
        return self._type.type_conversion

    @property
    def shema_field_ctor(self):

        if self.is_primary_key:
            return 'QoSchemaPrimaryKey'
        elif self.is_foreign_key:
            return 'QoSchemaForeignKey'
        else:
            return 'QoSchemaField'

    @property
    def sql_column_ctor(self):
        return self._type.__sql_column_ctor__.format(self)

    @property
    def sql_value_ctor(self):
        return self._type.__sql_value_ctor__

    @property
    def sql_value_getter(self):
        return self._type.__sql_value_getter__.format(self)

    ##############################################

    @property
    def sql_name(self):
        return self._sql_name

    @property
    def sql_type(self):
        return self._type.sql_type

    @property
    def autoincrement(self):
        return self._autoincrement

    @property
    def is_rowid_primary_key(self):
        return self.is_primary_key and isinstance(self._type, Integer) and self._position == 0

    @property
    def default(self):
        return self._default

    @property
    def nullable(self):
        return self._nullable

    @property
    def is_primary_key(self):
        return self._is_primary_key

    @property
    def unique(self):
        return self._unique

    @property
    def is_foreign_key(self):
        return self._foreign_key is not None

    @property
    def foreign_key(self):
        return self._foreign_key

    ##############################################

    @property
    def json_name(self):
        return self._json_name

    @property
    def on_json(self):
        return self._on_json

    ##############################################

    @property
    def title(self):
        return self._title

    @property
    def description(self):
        return self._description

####################################################################################################

class ComputedField:

    # Fixme: merge

    ##############################################

    def __init__(self, *args, **kwargs):

        self._type = None
        for arg in args:
            if inspect.isclass(arg):
                if issubclass(arg, FieldType):
                    self._type = arg()
        if self._type is None:
            raise ValueError()

        self._title = kwargs.get('title', '')
        self._description = kwargs.get('description', '')

        self._parent_schema = None
        self._variable = None

    ##############################################

    def __repr__(self):

        return '{0.__class__.__name__} {0._name}'.format(self)

    ##############################################

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, name):
        # Name is set afterwards
        self._name = name
        self._variable = Variable(self._name, self.qt_type, type_conversion=self.type_conversion)
        print(self._variable)

    ##############################################

    @property
    def parent_schema(self):
        return self._parent_schema

    @parent_schema.setter
    def parent_schema(self, value):
        self._parent_schema = value

    ##############################################

    @property
    def variable(self):
        return self._variable

    @property
    def qt_type(self):
        return self._type.qt_type

    @property
    def type_conversion(self):
        return self._type.type_conversion

    ##############################################

    @property
    def title(self):
        return self._title

    @property
    def description(self):
        return self._description

####################################################################################################

class RelationShipType(Enum):
    OneToOne = 1
    OneToMany = 2
    ManyToOne = 3
    ManyToMany = 4

####################################################################################################

class RelationShip:

    _logger = _module_logger.getChild('RelationShip')

    _relation_type_to_symbol = {
        RelationShipType.OneToOne: '1',
        RelationShipType.OneToMany: '1',
        RelationShipType.ManyToOne: '*',
        RelationShipType.ManyToMany: '*',
    }

    ##############################################

    def __init__(self, schema_class, **kwargs):

        self._schema_class = schema_class # name or cls
        self._back_populates = kwargs.get('back_populates', None)

        self._name = None
        self._parent_schema = None
        self._schema = None # instance
        self._foreign_key = None
        self._peer_relation = None
        self._relation_type = None

    ##############################################

    def _post_init(self):

        schema_repository = self._parent_schema.schema_repository
        self._schema = schema_repository.get_schema(self._schema_class)

        # Lookup the corresponding foreign key: same table
        for field in self._parent_schema.foreign_keys:
            if field.foreign_key.table == self._schema.table_name:
                self._foreign_key = field

        if self._foreign_key is not None: # else should be a peer
            related_table = self._foreign_key.foreign_key.table # Fixme: better ???
            related_schema = schema_repository.get_schema_by_table_name(related_table)
            # Lookup for other side
            for related_relation in related_schema.relations:
                if related_relation._back_populates == self._name:
                    self._peer_relation = related_relation
                    related_relation._peer_relation = self
                    self._relation_type = RelationShipType.ManyToOne
                    related_relation._relation_type = RelationShipType.OneToMany
                    message = "Relation: found peer {0._format_name} {0._relation_type_symbol} <-> {1._relation_type_symbol} {1._format_name}"
                    self._logger.info(message.format(self, related_relation))

        # self._logger.warning("Relation: any foreign key found for {0.parent_schema.cls_name}.{0.name}".format(self))

    ##############################################

    @property
    def _format_name(self):
        return "{0.parent_schema.cls_name}.{0.name}".format(self)

    @property
    def _relation_type_symbol(self):
        return self._relation_type_to_symbol[self._relation_type]

    ##############################################

    def __repr__(self):

        return '{0.__class__.__name__} {0._name}'.format(self)

    ##############################################

    @property
    def parent_schema(self):
        return self._parent_schema

    @parent_schema.setter
    def parent_schema(self, value):
        self._parent_schema = value

    ##############################################

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, value):
        self._name = value

    ##############################################

    @property
    def schema_class(self):
        return self._schema_class

    @property
    def schema(self):
        return self._schema

    @property
    def cls_name(self):
        return self._schema.cls_name

    @property
    def ptr_cls_name(self):
        return self._schema.ptr_cls_name

    @property
    def back_populates(self):
        return self._back_populates

    @property
    def foreign_key(self):
        return self._foreign_key

    @property
    def foreign_key_name(self):
        return self._foreign_key.name

    @property
    def foreign_key_related_column(self):
        return self._foreign_key.foreign_key.column

    @property
    def peer_relation(self):
        return self._peer_relation

    ##############################################

    @property
    def relation_type(self):
        return self._relation_type

    @property
    def is_one_to_one(self):
        return self._relation_type == RelationShipType.OneToOne

    @property
    def is_one_to_many(self):
        return self._relation_type == RelationShipType.OneToMany

    @property
    def is_many_to_one(self):
        return self._relation_type == RelationShipType.ManyToOne

    @property
    def is_many_to_many(self):
        return self._relation_type == RelationShipType.ManyToMany

####################################################################################################

class Schema:

    _logger = _module_logger.getChild('Schema')

    # Fixme: name clash !

    __table_name__ = None # SQL table name

    __order__ = None

    __custom_code__ = {}

    # custom_SECTION_[decl|impl]
    __custom_code_sections__ = (
        'cls',
        'cls_ptr',
        'cls_cache',
        'cls_model',
    )

    __has_post_init__ = False

    ##############################################

    def __init__(self):

        self._name = self.__class__.__name__

        self._schema_repository = None

        columns = {}
        self._relations = []
        self._computed_fields = []
        d = self.__class__.__dict__
        for name in sorted(d.keys()):
            attribute = d[name]
            if isinstance(attribute, (Field, RelationShip, ComputedField)):
                attribute.name = name
                attribute.parent_schema = self
                if isinstance(attribute, Field):
                    columns[name] = attribute
                elif isinstance(attribute, RelationShip):
                    self._relations.append(attribute)
                elif isinstance(attribute, ComputedField):
                    self._computed_fields.append(attribute)

        order = sorted(columns.keys())
        if self.__order__ is not None:
            # if len(self.__order__) != len(order):
            #     raise NameError("__order__ don't have the right number of items")
            if sorted(self.__order__) != order:
                column_set = set(order)
                given_set = set(self.__order__)
                missing_set = column_set - given_set
                unknown_set = given_set - column_set
                raise NameError("__order__ mismatch: missed {} unknown {}".format(missing_set, unknown_set))
            order = self.__order__

        self._has_rowid_primary_key = False
        self._rowid_primary_key = None
        self._fields = [columns[name] for name in order]
        for i, field in enumerate(self._fields):
            field.position = i
            if field.is_rowid_primary_key:
                self._has_rowid_primary_key = True
                self._rowid_primary_key = field

    ##############################################

    def _post_init(self):

        for relation in self.relations:
            relation._post_init()

        self._members = [field.variable for field in self._fields]
        self._computed_members = [field.variable for field in self._computed_fields]
        self._member_types = sorted(set([member.type for member in self._members]))
        self._private_members = []
        self._all_members = self._private_members + self._members

    ##############################################

    def __repr__(self):

        return '{0.__class__.__name__} {0._name}'.format(self)

    ##############################################

    @property
    def schema_repository(self):
        return self._schema_repository

    @schema_repository.setter
    def schema_repository(self, value):
        self._schema_repository = value

    ##############################################

    @property
    def cls_name(self): # to don't clash with "name" field
        return self._name

    @property
    def schema_cls_name(self):
        return self._name + 'Schema'

    @property
    def ptr_cls_name(self):
        return self._name + 'Ptr'

    @property
    def cache_cls_name(self):
        return self._name + 'Cache'

    @property
    def model_cls_name(self):
        return self._name + 'Model'

    @property
    def table_name(self):
        return self.__table_name__

    ##############################################

    def __iter__(self):

        return iter(self._fields)

    ##############################################

    @property
    def primary_keys(self):
        for field in self:
            if field.is_primary_key:
                yield field

    @property
    def foreign_keys(self):
        for field in self:
            if field.is_foreign_key:
                yield field

    @property
    def has_foreign_keys(self):
        return bool(list(self.foreign_keys))

    @property
    def fields_without_rowid(self):
        for field in self:
            if not field.is_rowid_primary_key:
                yield field

    @property
    def json_fields(self):
        for field in self:
            if field.on_json:
                yield field

    @property
    def relations(self):
        return self._relations

    ##############################################

    @property
    def has_rowid_primary_key(self):
        return self._has_rowid_primary_key

    @property
    def rowid_primary_key(self):
        return self._rowid_primary_key

    @property
    def base_class(self):
        return 'QoRow'
        # return 'QoRowWithId' if self._has_rowid_primary_key else 'QoRow'

    ##############################################

    @property
    def members(self):
        return self._members

    @property
    def all_members(self):
        return self._all_members

    @property
    def member_types(self):
        return self._member_types

    ##############################################

    @property
    def computed_members(self):
        return self._computed_members

    @property
    def has_post_init(self):
        return self.__has_post_init__

    ##############################################

    @property
    def includes(self):

        include_classes = set([member.type for member in self._members if member.type.startswith('Q')])
        # include_classes |= set((...)) # Done in template
        return sorted(include_classes)

    ##############################################

    def _render_custom_code(self, aggregator, file_target):

        custom_code_kwargs = {}

        for section_target in self.__custom_code_sections__:
            target = '{}_{}'.format(section_target, file_target)
            if target in self.__custom_code__:
                template = self.__custom_code__[target]
                key = 'custom_' + target
                self._logger.info("Register custom code for {0.cls_name} {1}".format(self, key))
                custom_code_kwargs[key] = aggregator.render(template, schema=self)

        return custom_code_kwargs

    ##############################################

    def generate_header(self, header):

        custom_code_kwargs = self._render_custom_code(header, 'decl')
        header.append('orm/row-class.h',
                      schema=self,
                      **custom_code_kwargs)

    ##############################################

    def generate_source(self, source):

        custom_code_kwargs = self._render_custom_code(source, 'impl')
        source.append('orm/row-class.cpp',
                      schema=self,
                      **custom_code_kwargs)

####################################################################################################

class SchemaRepository:

    _logger = _module_logger.getChild('SchemaRepository')

    __schemas__= ()

    # Global custom code [pre|post]_[header|source]
    __custom_code__ = {}

    ##############################################

    def __init__(self):

        name = self.__class__.__name__
        schemas = self.__schemas__

        self._name = name

        self._schemas = [cls() for cls in schemas]
        self._schema_class_map = {cls:self._schemas[i] for i, cls in enumerate(schemas)}
        self._schema_class_map.update({cls.__name__:self._schemas[i] for i, cls in enumerate(schemas)})
        self._table_map = {schema.table_name:schema for schema in self._schemas}

        self._post_init_schemas()

    ##############################################

    def _post_init_schemas(self):

        for schema in self:
            schema.schema_repository = self
            schema._post_init()

    ##############################################

    @property
    def name(self):
        return self._name

    ##############################################

    def __iter__(self):
        return iter(self._schemas)

    def get_schema(self, key):
        # key is class or class name
        return self._schema_class_map[key]

    def get_schema_by_table_name(self, name):
        # key is class or class name
        return self._table_map[name]

    ##############################################

    @property
    def includes(self):

        headers = set()
        for schema in self:
            headers |= set(schema.includes)
        return sorted(headers)

    ##############################################

    def _render_custom_code(self, aggregator, target):

        if target in self.__custom_code__:
            custom_code = self.__custom_code__[target]
            aggregator.append(custom_code, shema_repository=self)

    ##############################################

    def generate_source(self, filename, template_environment):

        generator_comment = "This file was automatically generated by SqlOrm" # on {}".format(datetime.datetime.now())

        header = TemplateAggregator(template_environment)
        header.append('orm/schema_header.h',
                      filename=filename,
                      generator_comment=generator_comment,
                      global_includes=self.includes,
        )
        self._render_custom_code(header, 'pre_header')
        for schema in self:
            schema.generate_header(header)
        header.append('orm/schema.h',
                      database_schema=self)
        self._render_custom_code(header, 'post_header')
        header.append('orm/schema_footer.h', filename=filename)

        source = TemplateAggregator(template_environment)
        source.append('orm/schema_header.cpp',
                      filename=filename,
                      generator_comment=generator_comment,
        )
        self._render_custom_code(source, 'pre_source')
        for schema in self:
            schema.generate_source(source)
        source.append('orm/schema.cpp',
                      database_schema=self)
        self._render_custom_code(source, 'post_source')
        source.append('orm/schema_footer.cpp')

        return str(header), str(source)

    ##############################################

    def write_source(self, path, *args, **kwargs):

        filename = os.path.basename(path)

        directory = os.path.dirname(path)
        if not os.path.exists(directory):
            raise NameError("Directory {} don't exists".format(directory))

        header, source = self.generate_source(filename, *args, **kwargs)

        with open(path + '.h', 'w') as f:
            f.write(str(header))
        with open(path + '.cpp', 'w') as f:
            f.write(str(source))

