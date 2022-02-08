####################################################################################################
#
# PySpice - A Spice package for Python
# Copyright (C) 2019 Fabrice Salvaire
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
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
####################################################################################################

####################################################################################################

from pathlib import Path
import os
import sys

from invoke import task

####################################################################################################

@task()
def search(ctx, pattern):
    for path in (
            'imports',
            'code-generator',
            'map-tools',
            'mapviewer',
            'service',
            'src',
            'unit-tests',
            'config.h.in',
    ):
        # with ctx.cd(path):
        command = f'grep --color=auto --exclude="*~" -r "{pattern}" {path}'
        ctx.run(command, pty=True)
