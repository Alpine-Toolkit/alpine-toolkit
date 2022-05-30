####################################################################################################
#
# Alpine Toolkit -
# Copyright (C) 2022 Fabrice Salvaire
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

from types import ModuleType

# http://www.pyinvoke.org
from invoke import Collection

####################################################################################################

from . import build
from . import clean
from . import ign
from . import inspect

modules = [obj for name, obj in globals().items() if isinstance(obj, ModuleType)]
ns = Collection()
for _ in modules:
    ns.add_collection(Collection.from_module(_))
