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

import logging

from .CppCodeGenerator import Header, ClassDefinition, Source, ClassImplementation

####################################################################################################

_module_logger = logging.getLogger(__name__)

####################################################################################################

class ClassGenerator:

    _logger = _module_logger.getChild('ClassGenerator')

    ##############################################

    def __init__(self, class_name, parent_class, members, generator_settings):

        self._class_name = class_name
        self._parent_class = parent_class
        self._members = members
        self._generator_settings = generator_settings

        self._class_definition = ClassDefinition(self._class_name, # .title()
                                                 self._parent_class,
                                                 self._members,
                                                 generator_settings)

    ##############################################

    def generate_header(self, properties, inline_getter, inline_setter):

        header = Header(self._class_name, self._generator_settings)
        header.cpp_mode()
        header.header()
        header.include('QObject')
        header.include('...')
        header.include('...', local=True)
        header.new_line()
        header.rule()
        header.new_line()
        header.comment('QC_BEGIN_NAMESPACE')
        header.new_line()

        class_definition = self._class_definition
        class_definition.begin()
        if properties:
            for member in self._members:
                class_definition.property(member)
        class_definition.public()
        class_definition.ctor()
        class_definition.dtor()
        class_definition.new_line()
        class_definition.copy_operator()
        for member in self._members:
            class_definition.new_line()
            if inline_getter:
                class_definition.inline_getter(member)
            else:
                class_definition.getter(member)
            if inline_setter:
                class_definition.inline_setter(member)
            else:
                class_definition.setter(member)
        if properties:
            class_definition.signals()
            for member in self._members:
                class_definition.property_changed_signal(member)
        class_definition.private()
        # class_definition.append_self._members()
        for member in self._members:
            class_definition.member(member.to_member())
        class_definition.close()

        header.append(class_definition)
        header.new_line()
        header.comment('QC_END_NAMESPACE')
        header.footer()

        return header

    ##############################################

    def generate_source(self, class_file_name):

        source = Source(self._class_name, self._generator_settings)
        source.header()
        source.include(class_file_name, local=True)
        source.new_line()
        source.rule()
        source.new_line()
        source.comment('QC_BEGIN_NAMESPACE')
        source.new_line()

        class_implementation = self._class_definition.to_implementation()
        class_implementation.ctor()
        class_implementation.new_line()
        class_implementation.copy_ctor()
        class_implementation.new_line()
        class_implementation.dtor()
        class_implementation.new_line()
        class_implementation.copy_operator_ctor()

        for member in self._members:
            class_implementation.new_line()
            class_implementation.getter(member)
            class_implementation.new_line()
            class_implementation.setter(member)

        # self.format('\n\n')
        # for member in self._members:
        #     self.format('.set_{name}(json_object[QStringLiteral(\'{name}\')].toString());\n'.format(self._class_name=self._class_name, **member))

        source.append(class_implementation)
        source.new_line()
        source.comment('QC_END_NAMESPACE')
        source.footer()

        return source
