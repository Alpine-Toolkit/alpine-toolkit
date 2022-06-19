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

def find(matcher, path='.'):
    to_delete = []
    for root, _, filenames in os.walk('.'):
        root = Path(root)
        for filename in filenames:
            filename = Path(filename)
            if matcher(filename):
                path = root.joinpath(filename)
                to_delete.append(path)
    if to_delete:
        rule = '='*100
        print(rule)
        for path in to_delete:
            print(path)
        print(rule)
        rc = input('remove ? [n]/y ')
        if rc == 'y':
            for path in to_delete:
                path.unlink(missing_ok=True)

####################################################################################################

@task
def flycheck(ctx):
    # Fixme: ctx.Package must be defined in invoke.yaml
    with ctx.cd(ctx.Package):
        # ctx.run('find . -name "flycheck*.py" -exec /usr/bin/rm {} \;')
        find(lambda filename: filename.suffix == '.py' and filename.stem.startswith('flycheck'))

@task
def emacs_backup(ctx):
    # ctx.run('find . -name "*~" -type f -exec /usr/bin/rm -f {} \;')
    find(lambda filename: str(filename).endswith('~'))

@task(flycheck, emacs_backup)
def clean(ctx):
    pass
