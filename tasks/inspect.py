####################################################################################################
#
# $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
#
# Copyright (C) 2022 Fabrice Salvaire
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
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
# $ALPINE_TOOLKIT_END_LICENSE$
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
            'CMakeLists.txt',
            'android',
            'build-config',
            'cmake',
            'code-generator',
            'config.h.in',
            'map-tools',
            'mapviewer',
            'resources',
            # 'sqlite',
            'src',
            'tasks',
            # 'third-parties',
            'unit-tests',
    ):
        # with ctx.cd(path):
        command = f'grep --color=auto --exclude="*~" -r "{pattern}" {path}'
        # warn is set else it raises when nothing is found
        ctx.run(command, pty=True, warn=True)
