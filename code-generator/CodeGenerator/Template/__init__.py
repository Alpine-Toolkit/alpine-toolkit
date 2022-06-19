####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
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
