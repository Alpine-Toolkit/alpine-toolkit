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

__all__= [
    'git_clone',
    'download',
    'untar',
    'unzip',
    # 'set_executable',
]

####################################################################################################

from pathlib import Path
import os

import requests

####################################################################################################

def git_clone(ctx, url, path, branch=None):
    print(f"Clone repository {url}")
    with ctx.cd(path.parent):
        command = f"git clone --depth=1"
        if branch:
            command += f" --branch {branch}"
        command += f" {url} {path}"
        ctx.run(command, echo=True)

####################################################################################################

def set_executable(path):
    path = Path(path)
    st = path.stat()
    path.chmod(st.st_mode | os.stat.S_IEXEC)

####################################################################################################

def download(url, path, executable=False):
    print(f"Get {url} ...")
    req = requests.get(url)
    with open(path, 'wb') as fh:
        fh.write(req.content)
    if executable:
        set_executable(path)

####################################################################################################

def untar(tar_path, path):
    import tarfile
    tar = tarfile.open(tar_path)
    tar.extractall(path=path)
    tar.close()

####################################################################################################

def unzip(zip_path, path):
    import zipfile
    with zipfile.ZipFile(zip_path, 'r') as zip_ref:
        zip_ref.extractall(path)
