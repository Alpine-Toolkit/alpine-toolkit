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
