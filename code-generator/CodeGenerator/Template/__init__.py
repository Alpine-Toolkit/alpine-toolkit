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

from jinja2 import Environment, FileSystemLoader # PackageLoader

from . import Filters

####################################################################################################

class CustomCode:

    """Wrapper to distinguish from template filename"""

    ##############################################

    def __init__(self, code):

        self._code = code

    ##############################################

    def __str__(self):

        return self._code

    ##############################################

    @property
    def code(self):
        return self._code

    @code.setter
    def code(self, value):
        self._code = value

####################################################################################################

class TemplateEnvironment:

    ##############################################

    def __init__(self, template_path):

        self._template_path = template_path

        self._environment = Environment(
            # loader=PackageLoader('', 'templates'),
            loader=FileSystemLoader(self._template_path),

            trim_blocks=True,
            lstrip_blocks=True,
            # keep_trailing_newline
        )

        self._environment.filters['unique'] = Filters.unique_filter

    ##############################################

    def render(self, template, **kwargs):

        if template is None:
            return ''

        if isinstance(template, str):
            jinja_template = self._environment.get_template(template)
        elif isinstance(template, CustomCode):
            jinja_template = self._environment.from_string(str(template))
        else:
            raise ValueError("Wrong template {}".format(template))

        return jinja_template.render(**kwargs)

####################################################################################################

class TemplateAggregator:

    ##############################################

    def __init__(self, template_environment):

        self._environment = template_environment
        self._output = ''

    ##############################################

    def __str__(self):

        return self._output

    ##############################################

    @staticmethod
    def _fix_output(output):

        output = output.replace(' \n', '\n')
        output = output.replace('\n\n\n', '\n\n')

        return output

    ##############################################

    def render(self, template, **kwargs):

        output = self._environment.render(template, **kwargs)
        output = self._fix_output(output)

        return output

    ##############################################

    def append(self, template, **kwargs):

        self._output += self.render(template, **kwargs)
