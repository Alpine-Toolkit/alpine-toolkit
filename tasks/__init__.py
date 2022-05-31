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

import sys
_version = sys.version_info
if not (_version.major == 3 and _version.minor >= 10):
    raise NameError("Require Python 3.10")

####################################################################################################

from types import ModuleType

# http://www.pyinvoke.org
from invoke import Collection

####################################################################################################

from . import build
from . import clean
from . import doc
from . import ign
from . import inspect

modules = [obj for name, obj in globals().items() if isinstance(obj, ModuleType)]
ns = Collection()
for _ in modules:
    ns.add_collection(Collection.from_module(_))
