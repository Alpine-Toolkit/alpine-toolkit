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

import os

from jinja2 import Template, Environment, PackageLoader, FileSystemLoader

####################################################################################################

class GeneratorSettings:

    __LINE_WIDTH__ = 100
    __INDENT__ = 2

    ##############################################

    def __init__(self,
                 copyright_header=None,
                 footer=None,
                 line_width=__LINE_WIDTH__,
                 indent=__INDENT__):

        self._line_width = line_width
        self._copyright_header = copyright_header
        self._footer = footer
        self._indent = indent

        self._template_path = os.path.join(os.path.dirname(__file__), 'code-generator-templates')

        self._environment = Environment(
            # loader=PackageLoader('', 'templates'),
            loader=FileSystemLoader(self._template_path),

            # trim_blocks=True,
            # lstrip_blocks=True,
            # keep_trailing_newline
        )

    ##############################################

    @property
    def line_width(self):
        return self._line_width

    @property
    def rule(self):
        return  '/' + '*'*(self._line_width-2) + '/'

    @property
    def rule_begin(self):
        return '/' + '*'*(self._line_width-1)

    @property
    def rule_close(self):
        return ' ' + '*'*(self._line_width-2) + '/'

    @property
    def copyright_header(self):
        return self._copyright_header

    @property
    def footer(self):
        return self._footer

    @property
    def indent(self):
        return self._indent

    ##############################################

    def render(self, template, context):

        return self._environment.get_template(template).render(**context)

####################################################################################################

class CodeMixin:

    ##############################################

    def __init__(self, generator_settings=None):

        self._generator_settings = generator_settings if generator_settings is not None else GeneratorSettings()
        self._code = ''
        self._indent_level = 0

    ##############################################

    @property
    def generator_settings(self):
        return self._generator_settings

    ##############################################

    def __str__(self):
        return self._code

    ##############################################

    def indent(self):

        self._indent_level += 1

    ##############################################

    def unindent(self):

        self._indent_level -= 1

    ##############################################

    def append(self, text):

        self._code += str(text)

    ##############################################

    def append_c(self, text):

        self.append(text + ';')

    ##############################################

    def new_line(self):

        self.append('\n')

    ##############################################

    def line(self, line):

        self.append(line)
        self.new_line()

    ##############################################

    def indented_line(self, line):

        indent = ' '*(self._generator_settings.indent * self._indent_level)
        self.append(indent + str(line))
        self.new_line()

    ##############################################

    def indented_line_c(self, line):

        self.indented_line(str(line) + ';')

    ##############################################

    def format(self, template, *args, **kwargs):

        self.append(template.format(*args, **kwargs))

    ##############################################

    def format_c(self, template, *args, **kwargs):

        self.append_c(template.format(*args, **kwargs))

    ##############################################

    def format_indented_line(self, template, *args, **kwargs):

        self.indented_line(template.format(*args, **kwargs))

    ##############################################

    def format_indented_line_c(self, template, *args, **kwargs):

        self.format_indented_line(template + ';', *args, **kwargs)

    ##############################################

    def comment(self, text):

        self.line('// ' + text)

    ##############################################

    def comment_block(self, text):

        self.line(self._generator_settings.rule_begin)
        for line in text.split('\n'):
            if line:
                self.line(' * ' + line)
            else:
                self.line(' *')
        self.append(self._generator_settings.rule_close)
        self.new_line()

    ##############################################

    def cpp_mode(self):

        self.line('// -*- mode: c++ -*-')

    ##############################################

    def rule(self):

        self.line(self._generator_settings.rule)

    ##############################################

    def copyright_header(self):

        self.comment_block(self._generator_settings.copyright_header)

    ##############################################

    def footer(self):

        footer = self._generator_settings.footer
        if (footer):
            self.new_line()
            self.comment_block(footer)

    ##############################################

    def include(self, include, local=False):

        code = '#include '
        code += '"' if local else "<"
        code += include
        if local and not include.endswith('.h'):
            code += '.h'
        code += '"' if local else ">"
        self.line(code)

    ##############################################

    def render(self, template, **kwargs):

        self.append(self._generator_settings.render(template, kwargs))
        self.new_line() # Fixme: why \n is removed ???

####################################################################################################

class Type:

    __TYPE_TO_VARIANT__ = {
        'bool': 'toBool',
        'int': 'toInt',
        'double': 'toDouble',
        'QString': 'toString',
        # array object
        }

    ##############################################

    @staticmethod
    def from_string(code):

        parts = code.split(' ')
        const = parts[0] == 'const'
        if const:
            data_type = parts[1]
        else:
            data_type = parts[0]
        ref = parts[-1] == '&'
        ptr = parts[-1] == '*'

        return Type(data_type, const, ref, ptr)

    ##############################################

    def __init__(self, data_type, const=False, ref=False, ptr=False):

        if ref and ptr:
            raise ValueError("Variable {} cannot be ref and ptr.format(name)")

        self._type = data_type
        self._const = const
        self._ref = ref
        self._ptr = ptr

    ##############################################

    def args_tuple(self):

        return (self.type, self.is_const, self.is_ref, self.is_ptr)

    ##############################################

    @property
    def type(self):
        return self._type

    @property
    def is_const(self):
        return self._const

    @property
    def is_ref(self):
        return self._ref

    @property
    def is_ptr(self):
        return self._ptr

    ##############################################

    @property
    def const_type(self):
        return 'const {0._type}'.format(self)

    @property
    def ref_type(self):
        return '{0._type} &'.format(self)

    @property
    def ptr_type(self):
        return '{0._type} *'.format(self)

    @property
    def const_ref_type(self):
        return '{0.const_type} &'.format(self)

    @property
    def const_ptr_type(self):
        return '{0.const_type} *'.format(self)

    ##############################################

    def __str__(self):

        if self._const:
            if self._ref:
                return self.const_ref_type
            elif self._ptr:
                return self.const_ptr_type
            else:
                return self.const_type
        else:
            if self._ref:
                return self.ref_type
            elif self._ptr:
                return self.ptr_type
            else:
                return self.type

    ##############################################

    @property
    def from_variant(self):
        return self.__TYPE_TO_VARIANT__[self.type]

    ##############################################

    def to_ref(self):

        return Type(self._type, ref=True)

    ##############################################

    def to_const_ref(self):

        return Type(self._type, const=True, ref=True)

    ##############################################

    @property
    def getter_type(self):

        if self._type.startswith('Q'):
            return self.to_const_ref()
        else:
            return Type(*Type.args_tuple(self)) # Fixme: to_type()

    ##############################################

    @property
    def setter_type(self):

        if self._type.startswith('Q'):
            return self.to_const_ref()
        else:
            return Type(*Type.args_tuple(self)) # Fixme: to_type()

    ##############################################

    def to_getter_type(self, const_ref=False):

        if const_ref:
            return self.to_ref()
        else:
            return self.getter_type

    ##############################################

    def to_setter_type(self, const_ref=False):

        if const_ref:
            return self.to_const_ref()
        else:
            return self.setter_type

####################################################################################################

class Variable(Type):

    ##############################################

    @staticmethod
    def from_string(code):

        index = code.rfind(' ')
        if index == -1:
            raise ValueError()
        name = code[index:].strip()
        data_type = Type.from_string(code[:index].strip())

        return Variable(name, *data_type.args_tuple())

    ##############################################

    def __init__(self, name, data_type, const=False, ref=False, ptr=False):

        Type.__init__(self, data_type, const, ref, ptr)

        self._name = name

    ##############################################

    def args_tuple(self):

        return tuple([self._name] + list(Type.args_tuple(self)))

    ##############################################

    @property
    def name(self):
        return self._name

    @property
    def m_name(self):
        if self.name.startswith('m_'):
            return self._name
        else:
            return 'm_' + self._name

    ##############################################

    @property
    def definition(self):
        return '{0._type} {0._name}'.format(self)

    @property
    def const_definition(self):
        return '{0.const_type} {0._name}'.format(self)

    @property
    def ref_definition(self):
        return '{0.ref_type} {0._name}'.format(self)

    @property
    def ptr_definition(self):
        return '{0.ptr_type} {0._name}'.format(self)

    @property
    def const_ref_definition(self):
        return '{0.const_ref_type} {0._name}'.format(self)

    @property
    def const_ptr_definition(self):
        return '{0.const_ptr_type} {0._name}'.format(self)

    ##############################################

    def __str__(self):

        return Type.__str__(self) + ' '  + self._name

    ##############################################

    def to_member(self):

        if self._name.startswith('m_'):
            return self
        else:
            args = Type.args_tuple(self)
            return Variable(self.m_name, *args)

    ##############################################

    def to_argument(self):

        return Argument(*self.args_tuple())

####################################################################################################

class Argument(Variable):

    ##############################################

    @staticmethod
    def from_string(code):

        index = code.find('=')
        if index:
            default = code[index+1:].strip()
            variable_part = code[:index].strip()
        else:
            default = None
            variable_part = code
        variable = Variable.from_string(variable_part)

        return Argument(*variable.args_tuple(), default=default)

    ##############################################

    def __init__(self, name, data_type, const=False, ref=False, ptr=False, default=None):

        Variable.__init__(self, name, data_type, const, ref, ptr)

        self._default = default

    ##############################################

    def args_tuple(self):

        return tuple(list(Variable.args_tuple(self) + [self._default]))

    ##############################################

    @property
    def default(self):
        return self._default

    ##############################################

    def __str__(self):

        code = Variable.__str__(self)
        if self._default is not None:
            code += ' = ' + self._default
        return code

####################################################################################################

class MethodMixin:

    ##############################################

    def __init__(self, class_definition, name, arguments=None, return_type='void', const=False):

        self._class_definition = class_definition
        self._name = name
        self._arguments = arguments if arguments is not None else []
        self._return_type = return_type
        self._const = const

    ##############################################

    @property
    def class_name(self):
        return self._class_definition.name

    @property
    def name(self):
        return self._name

    ##############################################

    def join_arguments(self, default=True):

        str_functor = str if default else Variable.__str__
        return ', '.join([str_functor(argument) for argument in self._arguments])

    ##############################################

    def prototype(self, implementation=False):

        code = ''
        if self._return_type is not None:
            code += str(self._return_type)
            if implementation:
                code += '\n'
            else:
                code += ' '
        if implementation:
            code += self.class_name + '::'
        code += self._name
        code += '(' + self.join_arguments(not implementation) + ')'
        if self._const:
            code += ' const'
        return code

####################################################################################################

class MethodDefinition(CodeMixin, MethodMixin):

    ##############################################

    def __init__(self, class_definition, name, arguments=None, return_type='void', const=False, generator_settings=None):

        CodeMixin.__init__(self, generator_settings)
        MethodMixin.__init__(self, class_definition, name, arguments, return_type, const)

    ##############################################

    def __str__(self):

        return self.prototype()

    ##############################################

    def args_tuple(self):

        return (self._class_definition, self._name,
                self._arguments, self._return_type, self._const,
                self._generator_settings)

    ##############################################

    def to_inline_implementation(self):

        return InlineMethodImplementation(self)

    ##############################################

    def to_implementation(self):

        return MethodImplementation(self)

    ##############################################

    def to_ctor_implementation(self):

        return CtorMethodImplementation(self)

####################################################################################################

class CtorDefinition(MethodDefinition):

    ##############################################

    def __init__(self, class_definition, arguments=None, generator_settings=None):

        MethodDefinition.__init__(self, class_definition, class_definition.name, arguments,
                                  return_type=None,
                                  generator_settings=generator_settings)

####################################################################################################

class CopyCtorDefinition(CtorDefinition):

    ##############################################

    def __init__(self, class_definition, generator_settings=None):

        CtorDefinition.__init__(self, class_definition,
                                [Argument('other', class_definition.name, const=True, ref=True)],
                                generator_settings=generator_settings)

####################################################################################################

class JsonCtorDefinition(CtorDefinition):

    ##############################################

    def __init__(self, class_definition, generator_settings=None):

        CtorDefinition.__init__(self, class_definition,
                                [Argument('json_object', 'QJsonObject', const=True, ref=True)],
                                generator_settings=generator_settings)

####################################################################################################

class JsonSerializerDefinition(MethodDefinition):

    ##############################################

    def __init__(self, class_definition, generator_settings=None):

        MethodDefinition.__init__(self, class_definition, 'to_json',
                                  [Argument('only_changed', 'bool', default='False')],
                                  return_type=Type('QJsonObject'), const=True,
                                  generator_settings=generator_settings)

####################################################################################################

class CopyOperatorDefinition(MethodDefinition):

    ##############################################

    def __init__(self, class_definition, generator_settings=None):

        MethodDefinition.__init__(self, class_definition, 'operator=',
                                  [Argument('other', class_definition.name, const=True, ref=True)],
                                  Type(class_definition.name, ref=True),
                                  generator_settings=generator_settings)

####################################################################################################

class DtorDefinition(MethodDefinition):

    ##############################################

    def __init__(self, class_definition, generator_settings=None):

        MethodDefinition.__init__(self, class_definition, '~' + class_definition.name,
                                  return_type=None,
                                  generator_settings=generator_settings)

####################################################################################################

class MethodImplementationMixin(CodeMixin):

    ##############################################

    def __init__(self, definition):

        CodeMixin.__init__(self, generator_settings=definition.generator_settings)
        self._definition = definition

    ##############################################

    def _code_block(self):

        if self._code:
            return '\n{\n' + self._code + '}\n'
        else:
            return '\n{}\n'

####################################################################################################

class InlineMethodImplementation(MethodImplementationMixin):

    ##############################################

    def __str__(self):

        return self._definition.prototype() + ' { ' + self._code + ' }'

####################################################################################################

class MethodImplementation(MethodImplementationMixin):

    ##############################################

    def __init__(self, definition):

        MethodImplementationMixin.__init__(self, definition)
        self.indent()

    ##############################################

    def __str__(self):

        return self._definition.prototype(implementation=True) + self._code_block()

####################################################################################################

class Initializer:

    ##############################################

    def __init__(self, member, value=None):

        self._member = member
        self._value = value

    ##############################################

    @property
    def member(self):
        return self._member

    @property
    def value(self):
        return self._value

    ##############################################

    def __str__(self):

        if self._value is not None:
            return '{0.member}({0.value})'.format(self)
        else:
            return '{0.member}()'.format(self)

####################################################################################################

class CtorMethodImplementation(MethodImplementation):

    ##############################################

    def __init__(self, definition):

        MethodImplementation.__init__(self, definition)
        self._initializers = []

    ##############################################

    @property
    def _class_definition(self):
        return self._definition._class_definition

    ##############################################

    def add_initializer(self, *args, **kwargs):

        self._initializers.append(Initializer(*args, **kwargs))

    ##############################################

    def __str__(self):

        code = self._definition.prototype(implementation=True)
        if self._initializers:
            code += '\n'
            last_i = len(self._initializers) -1
            for i, initializer in enumerate(self._initializers):
                if i:
                    code += '   '
                else:
                    code += ' : '
                code += str(initializer)
                if i < last_i:
                    code += ',\n'
        code += self._code_block()
        return code

####################################################################################################

class ClassMixin(CodeMixin):

    ##############################################

    def __init__(self, name, parent_class, members, generator_settings, private_members=[]):

        CodeMixin.__init__(self, generator_settings)
        self._name = name
        self._parent_class = parent_class
        self._members = members # Fixme: ???
        self._private_members = private_members
        self._methods = []

    ##############################################

    def args_tuple(self):

        return (self._name, self._parent_class, self._members, self._private_members, self._generator_settings)

    ##############################################

    @property
    def name(self):
        return self._name

    @property
    def parent_class(self):
        return self._parent_class

    @property
    def members(self):
        return self._members

    @property
    def private_members(self):
        return self._private_members

    @property
    def all_members(self):
        return self._private_members + self._members

####################################################################################################

class ClassDefinition(ClassMixin):

    ##############################################

    def begin(self):

        if self._parent_class is not None:
            self.format_indented_line('class {0._name} : public {0._parent_class}', self)
        else:
            self.format_indented_line('class {0._name}', self)
        self.indented_line('{')
        self.indent()
        if self._parent_class == 'QObject':
            self.indented_line('Q_OBJECT')

    ##############################################

    def close(self):

        self.unindent()
        self.indented_line('};\n')

    ##############################################

    def public(self):
        self.new_line()
        self.line('public:')

    def private(self):
        self.new_line()
        self.line('private:')

    def protected(self):
        self.new_line()
        self.line('protected:')

    def signals(self):
        self.new_line()
        self.line('signals:')

    ##############################################

    @property
    def ctor_definition(self):
        arguments = []
        # if self._parent_class == 'QObject':
        #     arguments.append(Argument.from_string('QObject * parent = nullptr'))
        return CtorDefinition(self, arguments)

    @property
    def copy_ctor_definition(self):
        # parent ?
        return CopyCtorDefinition(self)

    @property
    def json_ctor_definition(self):
        return JsonCtorDefinition(self)

    @property
    def json_serializer_definition(self):
        return JsonSerializerDefinition(self)

    @property
    def dtor_definition(self):
        return DtorDefinition(self)

    @property
    def copy_operator_definition(self):
        return CopyOperatorDefinition(self)

    ##############################################

    def append_method(self, definition):

        self._methods.append(definition)
        self.indented_line_c(definition)

    ##############################################

    def ctor(self):

        self.indented_line_c(self.ctor_definition)
        self.indented_line_c(self.copy_ctor_definition)

    ##############################################

    def json_ctor(self):

        self.indented_line_c(self.json_ctor_definition)

    ##############################################

    def json_serializer(self):

        self.append_method(self.json_serializer_definition)

    ##############################################

    def dtor(self):

        self.indented_line_c(self.dtor_definition)

    ##############################################

    def copy_operator(self):

        self.indented_line_c(self.copy_operator_definition)

    ##############################################

    def property(self, member):

        self.format_indented_line('Q_PROPERTY({0.type} {0.name} READ {0.name} WRITE set_{0.name} NOTIFY {0.name}Changed)',
                                  member)

    ##############################################

    def getter_definition(self, member, const_ref=False):

        return MethodDefinition(self, member.name,
                                return_type=member.to_getter_type(const_ref),
                                const=True)

    ##############################################

    def setter_definition(self, member, const_ref=False):

        args = Type.args_tuple(member.to_setter_type(const_ref))
        value = Argument('value', *args)

        return MethodDefinition(self, 'set_' + member.name,
                                [value],
                                'void')

    ##############################################

    def getter(self, member, const_ref=False):

        self.append_method(self.getter_definition(member, const_ref))

    ##############################################

    def setter(self, member, const_ref=False):

        self.append_method(self.setter_definition(member, const_ref))

    ##############################################

    def inline_getter(self, member, const_ref=False):

        definition = self.getter_definition(member, const_ref)
        implementation = definition.to_inline_implementation()
        implementation.format_c('return {0.m_name}', member)
        self.indented_line(implementation)
        self._methods.append(definition) # implementation ?

    ##############################################

    def inline_setter(self, member, const_ref=False):

        definition = self.setter_definition(member, const_ref)
        implementation = definition.to_inline_implementation()
        implementation.format_c('{0.m_name} = value', member)
        self.indented_line(implementation)
        self._methods.append(definition) # implementation ?

    ##############################################

    def property_changed_signal(self, member):

        self.indented_line_c(MethodDefinition(self._name, member.name + 'Changed'))

    ##############################################

    def member(self, member):

        self.indented_line_c(member.to_member().definition)

    ##############################################

    def append_members(self):

        for member in self._members:
            self.member(member) # to_member()

    ##############################################

    def to_implementation(self):

        return ClassImplementation(self) # *self.args_tuple()

####################################################################################################

class ClassImplementation(CodeMixin):

    ##############################################

    def __init__(self, class_definition):

        CodeMixin.__init__(self, class_definition.generator_settings)
        self._class_definition = class_definition

    ##############################################

    def ctor(self):

        # definition = self._class_definition.ctor_definition
        # implementation = definition.to_ctor_implementation()
        # if self._class_definition.parent_class == 'QObject':
        #     implementation.add_initializer('QObject', 'parent')
        # for member in self._class_definition.members:
        #     implementation.add_initializer(member.m_name)
        # self.append(implementation)

        cdef = self._class_definition
        self.render('ctor.cpp', class_name=self._class_definition.name, members=self._class_definition.all_members)

    ##############################################

    def copy_ctor(self):

        # definition = self._class_definition.copy_ctor_definition
        # implementation = definition.to_ctor_implementation()
        # # if self._class_definition.parent_class == 'QObject':
        # #     implementation.add_initializer('QObject', 'parent')
        # for member in self._class_definition.members:
        #     name = member.m_name
        #     implementation.add_initializer(name, 'other.' + name)
        # self.append(implementation)

        cdef = self._class_definition
        self.render('copy-ctor.cpp', class_name=cdef.name, members=cdef.all_members)

    ##############################################

    def json_ctor(self):

        # definition = self._class_definition.json_ctor_definition
        # implementation = definition.to_ctor_implementation()
        # implementation.add_initializer(definition.name)
        # for member in self._class_definition.members:
        #     template = '{0.m_name} = json_object[QLatin1String("{0.name}")].{0.from_variant}()'
        #     implementation.format_indented_line_c(template, member)
        #     # QStringLiteral QLatin1String
        # self.append(implementation)

        cdef = self._class_definition
        self.render('json-ctor.cpp', class_name=cdef.name, members=cdef.members)

    ##############################################

    def json_serializer(self):

        # definition = self._class_definition.json_serializer_definition
        # implementation = definition.to_implementation()
        # implementation.indented_line_c('QJsonObject json_object')
        # implementation.new_line()
        # for member in self._class_definition.members:
        #     implementation.format_indented_line_c('json_object.insert(QLatin1String("{0.name}"), QJsonValue({0.m_name}))', member)
        # implementation.new_line()
        # implementation.indented_line_c('return json_object')
        # self.append(implementation)

        cdef = self._class_definition
        self.render('json-serializer.cpp', class_name=cdef.name, members=cdef.members)

    ##############################################

    def dtor(self):

        # definition = self._class_definition.dtor_definition
        # implementation = definition.to_ctor_implementation()
        # self.append(implementation)

        cdef = self._class_definition
        self.render('dtor.cpp', class_name=cdef.name)

    ##############################################

    def copy_operator_ctor(self):

        # definition = self._class_definition.copy_operator_definition
        # implementation = definition.to_ctor_implementation()
        # implementation.indented_line('if (this != &other) {')
        # implementation.indent();
        # for member in self._class_definition.members:
        #     name = member.m_name
        #     implementation.format_indented_line_c('{0} = other.{0}', name)
        # implementation.unindent();
        # implementation.indented_line('}')
        # implementation.new_line()
        # implementation.indented_line_c('return *this')
        # self.append(implementation)

        cdef = self._class_definition
        self.render('copy-operator.cpp', class_name=cdef.name, members=cdef.all_members)

    ##############################################

    def getter(self, member, const_ref=False):

        # definition = self._class_definition.getter_definition(member, const_ref)
        # implementation = definition.to_implementation()
        # implementation.format_indented_line_c('return {0.m_name}', member)
        # self.append(implementation)

        cdef = self._class_definition
        self.render('getter.cpp', class_name=cdef.name, member=member)

    ##############################################

    def setter(self, member, const_ref=False):

        # definition = self._class_definition.setter_definition(member, const_ref)
        # implementation = definition.to_implementation()
        # implementation.format_indented_line('if ({0.m_name} != value) {{', member)
        # implementation.indent();
        # implementation.format_indented_line_c('{0.m_name} = value', member)
        # implementation.format_indented_line_c('emit {0.name}Changed()', member)
        # implementation.unindent();
        # implementation.indented_line('}')
        # self.append(implementation)

        cdef = self._class_definition
        self.render('setter.cpp', class_name=cdef.name, member=member)

####################################################################################################

class Header(CodeMixin):

    ##############################################

    def __init__(self, name, generator_settings):

        CodeMixin.__init__(self, generator_settings)
        self._name = name

    ##############################################

    def header(self):

        # self.cpp_mode()
        self.copyright_header()
        self.new_line()
        self.rule()
        template = '''
#ifndef __{name}_H__
#define __{name}_H__
'''
        self.format(template, name=self._name.upper())
        self.new_line()
        self.rule()
        self.new_line()

    ##############################################

    def footer(self):

        self.format('#endif /* __{name}_H__ */', name=self._name.upper())
        self.new_line()
        super(Header, self).footer()

####################################################################################################

class Source(CodeMixin):

    ##############################################

    def __init__(self, name, generator_settings):

        CodeMixin.__init__(self, generator_settings)
        self._name = name

    ##############################################

    def header(self):

        self.copyright_header()
        self.new_line()
        self.rule()
        self.new_line()
        # self.include(self._name, local=True)
        # self.new_line()
        # self.rule()
        # self.new_line()
