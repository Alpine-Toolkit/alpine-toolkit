####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2022 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
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
from . import indent
from . import inspect

modules = [obj for name, obj in globals().items() if isinstance(obj, ModuleType)]
ns = Collection()
for _ in modules:
    ns.add_collection(Collection.from_module(_))
