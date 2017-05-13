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

