####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2022 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

from pathlib import Path
import os
import sys

from invoke import task

####################################################################################################
#
# dnf install fd-find the_silver_searcher ripgrep
# fd — find entries in the filesystem
# ag — The Silver Searcher
# rg — recursively search the current directory for lines matching a pattern
#
####################################################################################################

source_path = Path(__file__).parents[1]

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
        path = source_path.joinpath(path)
        # with ctx.cd(path):
        command = f'grep --color=auto --exclude="*~" -r "{pattern}" {path}'
        # warn is set else it raises when nothing is found
        ctx.run(command, pty=True, warn=True)

####################################################################################################

@task()
def rg_search(ctx, pattern):
    gitignore = source_path.joinpath('.gitignore')
    command = f'rg "{pattern}" --ignore-file {gitignore} {source_path}'
    ctx.run(command, pty=True, warn=True)
