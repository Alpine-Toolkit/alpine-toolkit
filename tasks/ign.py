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

@task()
def bdalti(ctx):

    from .lib.ign.BdAlti import BdAltiRepository, BdAlti

    # repo = BdAltiRepository()

    # path = repo[0]
    # repo.get(path)
    # print(f'unzip {path} ...')
    # ctx.run(f'7z x {path}')
    # os.unlink(path)

    paths = sorted(BdAlti.find(os.getcwd()))
    print(f"Number of tiles: {len(paths)}")
    for path in sorted(paths):
        tile = BdAlti(path)
        tile.to_binary_format('mnt-tile.data')
        tile.pack('mnt-tile-packed.data')

    # number_of_bits = 14
    # BdAlti.pack(list(range(8)), number_of_bits)
