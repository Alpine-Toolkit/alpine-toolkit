{#  ################################################################################################
 #
 # This file is part of the Alpine Toolkit software.
 # Copyright (C) 2017 Fabrice Salvaire
 # Contact: http://www.fabrice-salvaire.fr
 # SPDX-License-Identifier: GPL-3.0-only
 #
 ############################################################################################### -#}

{% from 'includes/settings.jinja' import copyright -%}

// {{ generator_comment }}

{{ copyright() }}

/**************************************************************************************************/

#include "{{filename}}.h"
#include "alpine_toolkit.h"


#include "orm/database_query.h"
#include "orm/type_conversion.h"

#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

