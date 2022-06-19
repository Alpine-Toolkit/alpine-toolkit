####################################################################################################
#
# This file is part of the Alpine Toolkit software.
# Copyright (C) 2017 Fabrice Salvaire
# Contact: http://www.fabrice-salvaire.fr
# SPDX-License-Identifier: GPL-3.0-only
#
####################################################################################################

####################################################################################################

from .CppCodeGenerator import GeneratorSettings

####################################################################################################

copyright_header = """
This file is part of the Alpine Toolkit software.
Copyright (C) 2017 Fabrice Salvaire
Contact: http://www.fabrice-salvaire.fr
SPDX-License-Identifier: GPL-3.0-only
"""

footer = """
End
"""

generator_settings = GeneratorSettings(copyright_header, footer)
