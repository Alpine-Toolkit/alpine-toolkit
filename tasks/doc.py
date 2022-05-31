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

from invoke import task

####################################################################################################

@task
def set_source_path(ctx):
    source_path = Path(__file__).parents[1]
    ctx.doc_path = source_path.joinpath('doc')

####################################################################################################

@task(set_source_path)
def doxygen(ctx):
    doxyfile = ctx.doc_path.joinpath('doxygen', 'Doxyfile')
    ctx.run(f'doxygen {doxyfile}')

@task(set_source_path)
def open_doxygen(ctx):
    index = ctx.doc_path.joinpath('doxygen', 'build', 'html', 'index.html')
    ctx.run(f'xdg-open {index}')

@task(set_source_path)
def spinx(ctx):
    make = ctx.doc_path.joinpath('sphinx', 'make-html')
    ctx.run(make)
