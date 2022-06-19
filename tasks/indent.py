####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2022 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
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
