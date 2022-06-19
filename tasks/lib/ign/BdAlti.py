####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2022 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

"""IGN MNT.

* `RGE ALTI <https://geoservices.ign.fr/rgealti>`_ Le modèle numérique de terrain (MNT) maillé qui
   décrit le relief du territoire français à grande échelle au pas de 1 m et 5 m.

* `BD ALTI >https://geoservices.ign.fr/bdalti>`_
  BD ALTI 25 m
  Le modèle numérique de terrain (MNT) maillé qui décrit le relief du territoire français à moyenne échelle
  Un fichier 7z par départment (104 en tout)
  Départment 1 à 95, sauf le 20 qui est scindé en 2A et 2B pour la Corse; et 971 à 978 pour l'outre-mer
  BDALTIV2_2-0_25M_ASC_LAMB93-IGN69_D001_2021-01-13.7z
  BDALTIV2_2-0_25M_ASC_LAMB93-IGN69_D00#_<DATE    >.7z

  BDALTIV2_2-0_25M_ASC_WGS84UTM20-GUAD88_D971_2014-01-15.7z
  BDALTIV2_2-0_25M_ASC_WGS84UTM20-MART87_D972_2015-10-21.7z
  BDALTIV2_2-0_25M_ASC_UTM22RGFG95-GUYA77_D973_2019-02-02.7z
  BDALTIV2_2-0_25M_ASC_RGR92UTM40S-REUN89_D974_2016-03-11.7z
  BDALTIV2_2-0_25M_ASC_RGSPM06U21-STPM50_D975_2017-03-27.7z
  BDALTIV2_2-0_25M_ASC_RGM04UTM38S-MAYO53_D976_2013-12-19.7z
  BDALTIV2_2-0_25M_ASC_WGS84UTM20-GUAD88SB_D977_2019-11-25.7z
  BDALTIV2_2-0_25M_ASC_WGS84UTM20-GUAD88SM_D978_2019-11-20.7z

* https://geoservices.ign.fr/sites/default/files/2021-07/DC_BDALTI_2-0.pdf
* https://geoservices.ign.fr/sites/default/files/2021-07/DC_RGEALTI_2-0.pdf

* https://www.geoportail.gouv.fr/donnees/carte-des-pentes
  https://www.geoportail.gouv.fr/actualites/montagne-mieux-prevenir-le-risque-davalanche-avec-la-carte-des-pentes
  https://www.ign.fr/reperes/risque-davalanche-des-outils-pour-preparer-vos-sorties-en-montagne
  Représentation des classes de pentes supérieures à 30°, 35°, 40°, et 45° obtenues par traitement
  automatique du modèle numérique de terrain RGE ALTI de l’IGN au pas de 1m.

**BDALTI Data**
* (xllcorner, yllcorner) is the coordinate in Lambert 93 projection of the south-west corner of the tile.

BD ALTI has 104 sets of 20 tiles.

"""

####################################################################################################

from ftplib import FTP
from io import StringIO
from pathlib import Path
from typing import Iterator
from urllib.parse import urlparse
import math
import os

from bs4 import BeautifulSoup
import requests

import numpy as np

import pyproj

####################################################################################################

def bdalti_url_iter(html_source: str) -> Iterator[str]:
    soup = BeautifulSoup(html_source, 'html.parser')
    for link in soup.find_all('a'):
        if 'href' in link.attrs:
            url = link['href']
            if url.startswith('ftp://'):
                yield url

####################################################################################################

class BdAltiRepository:

    IGN_URL = 'https://geoservices.ign.fr'
    BD_ALTI_URL = f'{IGN_URL}/bdalti'
    RGE_ALTI_URL = f'{IGN_URL}/rgealti'
    FTP_URL = 'ftp3.ign.fr'

    ##############################################

    def __init__(self) -> None:

        # https://docs.python-requests.org/en/latest/user/advanced/#ssl-cert-verification
        print(f'Get {self.BD_ALTI_URL}')
        r = requests.get(self.BD_ALTI_URL, verify=False)
        if r.status_code != requests.codes.ok:
            raise NameError("")

        urls = [_ for _ in bdalti_url_iter(r.text)]
        # ftp://BD_ALTI_ext:PASSWORD@ftp3.ign.fr/BDALTIV2_2-0_25M_ASC_LAMB93-IGN69_D001_2021-01-13.7z

        # remove /
        self._urls = [urlparse(_).path[1:] for _ in urls]
        print(f"Number of files for BdAlti: {len(self._urls)}")
        # for _ in self._urls:
        #     print(_)

        url = urls[0]
        login_data, self._ftp_url = urlparse(url).netloc.split('@')
        self._user, self._password = login_data.split(':')

        self._ftp = FTP(self._ftp_url)
        self._ftp.login(user=self._user, passwd=self._password)
        # print(self._ftp.retrlines('list'))

    ##############################################

    def __len__(self) -> int:
        return len(self._urls)

    def __iter__(self) -> Iterator[str]:
        return iter(self._urls)

    def __getitem__(self, i) -> str:
        return self._urls[i]

    ##############################################

    def __del__(self) -> None:
        self._ftp.quit()

    ##############################################

    def get(self, path: str) -> None:
        print(f'Get {path} ...')
        with open(path, 'wb') as fh:
            self._ftp.retrbinary(f'retr {path}', fh.write)

####################################################################################################

class BdAlti:

    # ncols        1000
    # nrows        1000
    # xllcorner    824987.500000000000
    # yllcorner    6500012.500000000000
    # cellsize     25.000000000000
    # NODATA_value  -99999.00
    #  290.45

    LAMBERT93 = pyproj.Proj(init='epsg:2154')
    WSG84 = pyproj.Proj(init='epsg:4326')

    ##############################################

    @classmethod
    def number_of_bits_for(cls, delta: int) -> int:
        return int(math.ceil(math.log(delta + 1, 2)))

    @classmethod
    def number_of_bits_for_array(cls, data: np.ndarray) -> int:
        inf = np.min(data)
        sup = np.max(data)
        return cls.number_of_bits_for(sup - inf)

    ##############################################

    @classmethod
    def find(self, path: Path | str) -> Iterator[Path]:
        for root, _, filenames in os.walk(path):
            root = Path(root)
            for filename in filenames:
                path = root.joinpath(filename)
                if path.suffix == '.asc':
                    yield path

    ##############################################

    def __init__(self, path: Path | str) -> None:

        self._path = path

        with open(path, 'r') as fh:
            lines = fh.readlines()

        def split(line : str) -> str:
            return [_ for _ in line.split(' ') if _]

        i = 0
        def split_line() -> str:
            nonlocal i
            _ = split(lines[i])[1]
            i += 1
            return _

        self._number_of_columns = int(split_line())
        self._number_of_rows = int(split_line())
        self._x = float(split_line())
        self._y = float(split_line())
        self._step = float(split_line())
        nodata_value = float(split_line())
        print(f'{self._path.name} {self._number_of_rows}x{self._number_of_columns} {self._x} {self._y} {self._step}')
        # print(self.wsg84)

        def transform_z(z: str) -> str:
            return int(z.replace('.', ''))

        # z values have format 123.45 with 2 decimals
        dtype = np.uint16
        # uint8    255
        #     13  8191
        #     14 16383 <<< win 1000**2 *2 /8/1024 = 244kB per tile
        # uint16 65535
        self._data = np.zeros((self._number_of_rows, self._number_of_columns), dtype=dtype)
        for j in range(self._number_of_rows):
            row = lines[i]
            row = np.loadtxt(StringIO(row), dtype=np.float64)
            row *= 100
            # row = [transform_z(_) for _ in row.split(' ') if _]
            # row = np.array(row, dtype=dtype)
            self._data[j] = row
            i += 1
        # print(self._data)

        inf = np.min(self._data)
        sup = np.max(self._data)
        delta_cm = sup - inf
        delta_m = delta_cm // 100
        number_of_bits = self.number_of_bits_for(delta_m)
        print(f"z in [{inf}, {sup}] cm = {delta_m} m   {number_of_bits}-bit")

    ##############################################

    @property
    def size(self) -> int:
        return self._number_of_rows

    @property
    def step(self) -> float:
        return self._step

    @property
    def lambert93(self) -> tuple[float, float]:
        """Return (x, y) in Lambert93"""
        return self._x, self._y

    @property
    def wsg84(self) -> tuple[float, float]:
        """Return (longitude N, latitude E) in WGS84"""
        return pyproj.transform(self.LAMBERT93, self.WSG84, self._x, self._y)

    ##############################################

    def _to_binary_format(self, path : Path | str, data: np.ndarray) -> None:
        with open(path, 'wb') as fh:
            # fh.write(data.tobytes(order='C'))
            data.tofile(fh)

    ##############################################

    def to_binary_format(self, path : Path | str) -> None:
        self._to_binary_format(path, self._data)

    ##############################################

    @classmethod
    def _pack_array(cls, data: np.ndarray, packed_data: np.ndarray, func, number_of_bits: int) -> None:
        data_offset = 0
        pack_offset = 0
        while data_offset < data.size:
            next_data_offset = data_offset + 8
            next_pack_offset = pack_offset + number_of_bits
            # print(f"[{data_offset}:{next_data_offset}] [{pack_offset}:{next_pack_offset}]")
            func(
                data[data_offset:next_data_offset],
                packed_data[pack_offset:next_pack_offset],
                number_of_bits,
            )
            data_offset = next_data_offset
            pack_offset = next_pack_offset

    ##############################################

    def pack(self, path : Path | str) -> None:
        data = np.array(self._data)
        data //= 100   # convert to meter
        inf = np.min(data)
        data -= inf
        data = data.flatten()

        number_of_bits = self.number_of_bits_for_array(data)
        print(f'Pack to {number_of_bits}-bit with -{inf}')

        #! data = data[:8*2]
        # N-bit * 8 <=> 8-bit * N
        if data.size % 8 != 0:
            raise ValueError()
        packed_data_size = int(math.ceil(data.size / 8)) * number_of_bits
        packed_data = np.zeros(packed_data_size, dtype=np.uint8)

        self._pack_array(data, packed_data, self._pack_values, number_of_bits)

        self._to_binary_format(path, packed_data)
        print(data[:10])
        # print(packed_data[:10])

        unpacked_data = np.zeros(data.size, dtype=data.dtype)
        self._pack_array(unpacked_data, packed_data, self._unpack_values, number_of_bits)
        print(unpacked_data[:10])
        assert(np.array_equal(data, unpacked_data))
        # Packed format
        # [header: x, y, offset, n-bit] [packed data...]

    ##############################################

    @classmethod
    def _pack_values(self, values: np.ndarray, byte_array: np.ndarray, number_of_bits: int) -> None:
        # , number_of_bytes: int=8
        # byte_array = [0] * number_of_bits
        byte_index = 0
        byte_offset = 0
        # for i, value in enumerate(values):
        for i in range(8):
            value = values[i]
            # print('---')
            bit_count = 0
            while bit_count < number_of_bits:
                remaining_bit = number_of_bits - bit_count
                # number of free bits in the current byte
                free_bits = 8 - byte_offset
                bit_to_consume = min(free_bits, remaining_bit)
                mask = 2**bit_to_consume -1
                byte_shift = free_bits - bit_to_consume
                # print(f"v@{i:2}:{bit_count:2}/{remaining_bit:2}   b@{byte_index:2}+{byte_offset:2}/{free_bits:2} >>> #{bit_to_consume}")
                # print(f"B[{byte_index:2}] |= ((V[{i}] >> {bit_count:2}) & M({bit_to_consume})) << {byte_shift}")
                byte_array[byte_index] |= ((value >> bit_count) & mask) << byte_shift
                bit_count += bit_to_consume
                byte_offset += bit_to_consume
                if byte_offset >= 8:
                    byte_offset = byte_offset % 8
                    byte_index += 1

    ##############################################

    @classmethod
    def _unpack_values(self, values: np.ndarray, byte_array: np.ndarray, number_of_bits: int) -> None:
        byte_index = 0
        byte_offset = 0
        for i in range(8):
            value = 0
            bit_count = 0
            while bit_count < number_of_bits:
                byte = byte_array[byte_index]
                remaining_bit = number_of_bits - bit_count
                free_bits = 8 - byte_offset
                bit_to_consume = min(free_bits, remaining_bit)
                mask = 2**bit_to_consume -1
                shift_byte = free_bits - bit_to_consume
                shift_value = bit_count
                # print(f"V[{i:2}] |= ((B[{byte_index:2}] >> {shift_byte:2}) & M({bit_to_consume})) << {shift_value}")
                value |= ((byte >> shift_byte) & mask) << shift_value
                bit_count += bit_to_consume
                byte_offset += bit_to_consume
                if byte_offset >= 8:
                    byte_offset = byte_offset % 8
                    byte_index += 1
            values[i] = value
