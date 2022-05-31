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