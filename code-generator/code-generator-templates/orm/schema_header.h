{#  ################################################################################################
 #
 # $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 #
 # Copyright (C) 2017 Fabrice Salvaire
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
 # along with this program.  If not, see <http://www.gnu.org/licenses/>.
 #
 # $ALPINE_TOOLKIT_END_LICENSE$
 #
 ############################################################################################### -#}

{% from 'includes/settings.jinja' import copyright %}
{% from 'includes/header.jinja' import header_name -%}

// -*- mode: c++ -*-
// {{ generator_comment }}

{{ copyright() }}

/**************************************************************************************************/

#ifndef __{{ header_name(filename) }}_H__
#define __{{ header_name(filename) }}_H__

/**************************************************************************************************/

#define QT_SHAREDPOINTER_TRACK_POINTERS // For dubug purpose

#include "alpine_toolkit.h"
#include "orm/database_row.h"
#include "orm/database_row_list.h"
#include "orm/database_schema.h"
#include "orm/schema.h"
{% for include in local_includes|unique|sort %}
#include "{{include}}"
{% endfor %}

{% set _global_includes =
    [
     'QAbstractListModel',
     'QDataStream',
     'QJsonObject',
     'QMap',
     'QSharedPointer',
     'QSqlQuery',
     'QSqlRecord',
     'QVariant',
     'QVariantList',
     'QtDebug',
     ]
    + global_includes
    %}
{% for include in _global_includes|unique|sort %}
#include <{{include}}>
{% endfor %}

/**************************************************************************************************/

