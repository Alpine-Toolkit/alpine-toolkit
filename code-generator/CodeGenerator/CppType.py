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

QT_BUILTIN_VARIANTS = (
    'QBitArray',
    'bool',
    'QByteArray',
    'QChar',
    'QDate',
    'QDateTime',
    'double',
    'QEasingCurve',
    'float',
    'QHash<QString, QVariant>',
    'int',
    'QJsonArray',
    'QJsonDocument',
    'QJsonObject',
    'QJsonValue',
    'QLine',
    'QLineF',
    'QList<QVariant>',
    'QLocale',
    'qlonglong',
    'QMap<QString, QVariant>',
    'QModelIndex',
    'QPersistentModelIndex',
    'QPoint',
    'QPointF',
    'qreal',
    'QRect',
    'QRectF',
    'QRegExp',
    'QRegularExpression',
    'QSize',
    'QSizeF',
    'QString',
    'QStringList',
    'QTime',
    'uint',
    'qulonglong',
    'QUrl',
    'QUuid',
)

####################################################################################################

class TypeConversion:

    ##############################################

    def __init__(self,
                 cast_from_json=None,
                 cast_to_json=None,
                 # cast_from_variant=None,
                 # cast_to_variant=None,
                 cast_from_sql=None,
                 cast_to_sql=None,
    ):

        self._cast_from_json = cast_from_json
        self._cast_to_json = cast_to_json
        self._cast_from_sql = cast_from_sql
        self._cast_to_sql = cast_to_sql

    ##############################################

    @property
    def cast_from_json(self):
        return self._cast_from_json

    @property
    def cast_to_json(self):
        return self._cast_to_json

    @property
    def cast_from_sql(self):
        return self._cast_from_sql

    @property
    def cast_to_sql(self):
        return self._cast_to_sql

####################################################################################################

class Type:

    __TYPE_TO_VARIANT__ = {
        'bool': 'toBool',
        'int': 'toInt',
        'unsigned int': 'toUInt',
        'double': 'toDouble',
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

    def __init__(self, data_type, const=False, ref=False, ptr=False, type_conversion=None):

        if ref and ptr:
            raise ValueError("Variable {} cannot be ref and ptr.format(name)")

        self._type = data_type
        self._const = const
        self._ref = ref
        self._ptr = ptr
        self._type_conversion = type_conversion

    ##############################################

    def args_tuple(self):

        return (self._type, self._const, self._ref, self._ptr, self._type_conversion)

    ##############################################

    def __repr__(self):

        return '{0.__class__.__name__} {0._name}'.format(self)

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

    @property
    def is_q_type(self):
        return self._type.startswith('Q')

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
                return self._type

    ##############################################

    @property
    def from_variant(self):

        # QVariant().toXxx()

        if self.cast_variant:
            return 'value<{0.type}>'.format(self)
        elif self.is_q_type:
            data_type = self._type[1:]
            location = data_type.find('<')
            if location != -1:
                data_type = data_type[:location]
            return 'to' + data_type
        else:
            return self.__TYPE_TO_VARIANT__[self._type]

    ##############################################

    @property
    def cast_variant(self):

        if self._type in QT_BUILTIN_VARIANTS:
            return False
        else:
            return True

    ##############################################

    @property
    def from_json(self):

        # QJsonValue).toXxx()

        if self._type in ('int', 'unsigned int'):
            return 'toInt'
        elif self._type in ('float', 'double', 'qreal'):
            return 'toDouble'
        elif self._type in ('QString', 'QUrl'):
            return 'toString'
        # elif self._type in ('QDateTime',):
        #     return 'toVariant().' + self.from_variant
        elif self._type in ('QDateTime', 'QGeoCoordinate', 'QStringList'):
            return None
        # toArray / toObject
        else:
            raise ValueError("Don't know how to convert {} from JSON".format(self._type))

    ##############################################

    @property
    def cast_from_json(self):

        # Cast for JSON value

        if self._type_conversion is not None:
            return self._type_conversion.cast_from_json
        elif self._type == 'QDateTime':
            return 'json_helper::load_datetime'
        elif self._type == 'QStringList':
            return 'json_helper::load_string_list'
        # elif self._type == 'QUrl':
        #     return 'json_helper::load_url'
        else:
            return None

    ##############################################

    @property
    def cast_to_json(self):

        # Cast to JSON value

        if self._type_conversion is not None:
            return self._type_conversion.cast_to_json
        elif self._type == 'QDateTime':
            return 'json_helper::dump_datetime'
        elif self._type == 'QStringList':
            return 'json_helper::dump_string_list'
        elif self._type == 'QUrl':
            return 'json_helper::dump_url'
        else:
            return None

    ##############################################

    # @property
    # def m_to_json(self):

    #     # Member to JSON value

    #     if self._type == 'QDateTime':
    #         return '{0.m_name}.toString(Qt::ISODate)'.format(self)
    #     elif self._type in ('QUrl'):
    #         return '{0.m_name}.toString()'.format(self)
    #     else:
    #         return self.m_name

    ##############################################

    def to_ref(self):

        return Type(self._type, ref=True, type_conversion=self._type_conversion)

    ##############################################

    def to_const_ref(self):

        return Type(self._type, const=True, ref=True, type_conversion=self._type_conversion)

    ##############################################

    @property
    def getter_type(self):

        if self.is_q_type:
            return self.to_const_ref()
        else:
            return Type(*Type.args_tuple(self)) # Fixme: to_type()

    ##############################################

    @property
    def setter_type(self):

        if self.is_q_type:
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

    def __init__(self, name, data_type, const=False, ref=False, ptr=False, type_conversion=None, value=None):

        Type.__init__(self, data_type, const, ref, ptr, type_conversion)

        self._name = name
        self._value = value

    ##############################################

    def args_tuple(self):

        return tuple([self._name] + list(Type.args_tuple(self)) + [self._value])

    ##############################################

    @property
    def name(self):
        return self._name

    @property
    def is_m_name(self):
        return self._name.startswith('m_')

    @property
    def m_name(self):
        if self.is_m_name:
            return self._name
        else:
            return 'm_' + self._name

    @property
    def value(self):
        return self._value

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

        if self.is_m_name:
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

    def __init__(self, name, data_type, const=False, ref=False, ptr=False, type_conversion=None, default=None):

        Variable.__init__(self, name, data_type, const, ref, ptr, type_conversion)

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
