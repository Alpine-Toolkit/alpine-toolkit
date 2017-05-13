{% from 'includes/settings.jinja' import copyright -%}

// {{ generator_comment }}

{{ copyright() }}

/**************************************************************************************************/

#include "{{filename}}.h"

#include "orm/type_conversion.h"

#include <QtDebug>

/**************************************************************************************************/

// QC_BEGIN_NAMESPACE

