####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2022 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
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
