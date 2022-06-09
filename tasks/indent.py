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
#
# // clang-format off
# // clang-format on
#
####################################################################################################

####################################################################################################

from invoke import task

####################################################################################################

@task()
def clang_format(ctx):
    # preview the changes done by the formatter"
    command = 'git clang-format --diff'
    ctx.run(command, pty=True)  # pty to get ANSI colors

    # format the changed parts
    # 'git clang-format --force'

    # clang-format -n src/main.cpp
    # clang-format src/main.cpp
    # clang-format -i src/main.cpp
