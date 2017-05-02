{# -*- mode: fundamental -*- -#}
{{class_name}}Schema::{{class_name}}Schema()
: QcRowSchema<{{class_name}}>(QLatin1String("{{class_name}}"), QLatin1String("{{schema.table_name}}"))
{
{%- for field in schema %}
  {
    QcSchemaField field(QLatin1String("{{field.name}}"),
                        QLatin1String("{{field.qt_type}}"),
                        QLatin1String("{{field.sql_type}}"),
                        QLatin1String("{{field.sql_name}}"),
                        QLatin1String("{{field.json_name}}"),
                        QLatin1String("{{field.title}}"),
                        QLatin1String("{{field.description}}"));
    // Optional parameters
    {% if field.primary_key %}field.set_primary_key(true);{% endif %}
    {% if field.autoincrement %}field.set_autoincrement(true);{% endif %}
    {% if not field.nullable %}field.set_nullable(false);{% endif %}
    {% if field.unique %}field.set_unique(true);{% endif %}
    {% if field.default %}field.set_default_value({{field.default}});{% endif %}
    add_field(field);
  }{% endfor %}
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
// bit array ?
{% include "includes/copy-operator.cpp" %}
{%- endwith %}
// bit array ?
{% include "includes/equal-operator.cpp" %}
{% for member in members %}
{% include "includes/setter.cpp" %}
{% endfor %}
{% include "includes/json-serializer.cpp" %}

{% include "includes/variant-serializer.cpp" %}

{% include "includes/field-accessor.cpp" %}

{% include "includes/data-stream-operator.cpp" %}

{% include "includes/debug.cpp" %}
