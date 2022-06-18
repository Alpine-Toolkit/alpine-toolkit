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

__all__ = ['sed']

####################################################################################################

from pathlib import Path

####################################################################################################

def get_backup_file(path: str | Path) -> None:
    i = 1
    while True:
        new_path = Path(path).parent.joinpath(path.name + f'~{i}')
        if not new_path.exists():
            return new_path
        i += 1

####################################################################################################

def sed(path: str | Path, *replacements, **kwargs) -> None:
    path = Path(path)
    new_content = ''
    with open(path) as fh:
        new_content = fh.read()
    for from_, to in replacements:
        new_content = new_content.replace(from_, to)
    if kwargs.get('backup', False):
        path.rename(get_backup_file(path))
    with open(path, 'w') as fh:
        fh.write(new_content)
