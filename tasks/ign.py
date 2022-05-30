####################################################################################################
#
# PySpice - A Spice package for Python
# Copyright (C) 2019 Fabrice Salvaire
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
