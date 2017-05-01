{# -*- mode: fundamental -*- -#}
{{class_name}}Schema::{{class_name}}Schema()
: QcSchema(QLatin1String("{{class_name}}"), QLatin1String("{{schema.table_name}}"))
{
{%- for field in schema %}
  add_field(QcSchemaField(QLatin1String("{{field.name}}"),
                          QLatin1String("{{field.qt_type}}"),
                          QLatin1String("{{field.sql_type}}"),
                          QLatin1String("{{field.sql_qualifier}}"),
                          QLatin1String("{{field.sql_name}}"),
                          QLatin1String("{{field.json_name}}"),
                          QLatin1String("{{field.title}}"),
                          QLatin1String("{{field.description}}")));{% endfor %}
}

{{class_name}}Schema::~{{class_name}}Schema()
{}

/**************************************************************************************************/
{% with members = all_members %}
{% include "includes/ctor.cpp" %}

{% include "includes/copy-ctor.cpp" %}
{%- endwith %}

{% include "includes/json-ctor.cpp" %}

{% include "includes/sql-ctor.cpp" %}

{% include "includes/dtor.cpp" %}
{% with members = all_members %}
{% include "includes/copy-operator.cpp" %}
{%- endwith %}
{% include "includes/equal-operator.cpp" %}
{% for member in members %}
{% include "includes/setter.cpp" %}
{% endfor %}
{% include "includes/json-serializer.cpp" %}

{% include "includes/variant-serializer.cpp" %}

{% include "includes/field-accessor.cpp" %}

{% include "includes/data-stream-operator.cpp" %}

{% include "includes/debug.cpp" %}
