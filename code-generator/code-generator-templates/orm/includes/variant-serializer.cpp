{# -*- mode: fundamental -*- -#}

{#  ################################################################################################
 #
 # $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 #
 # Copyright (C) 2017 Fabrice Salvaire
 # Contact: http://www.fabrice-salvaire.fr
 #
 # This file is part of the QtCarto library.
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
 ###############################################################################################  #}

{% macro cast_to_variant(field) -%}
{% if field.variable.cast_variant -%}
QVariant::fromValue(m_{{field.name}})
{%- else -%}
m_{{field.name}}
{%- endif %}
{%- endmacro -%}

{% macro insert(field) -%}
variant_hash[QLatin1String("{{field.name}}")] = {{ field_value(field) }};
{%- endmacro -%}

{% macro to_variant_hash(prefix, fields) %}
QVariantHash
{{class_name}}::to_variant_hash{{prefix}}(bool only_changed) const
{
  QVariantHash variant_hash;

  if (only_changed) {
{% for field in fields %}
    if (is_{{field.name}}_modified())
      {{ insert(field) }}
{% endfor %}
  } else {
{% for field in fields %}
    {{ insert(field) }}
{% endfor %}
  }

  return variant_hash;
}
{% endmacro -%}

{% macro to_variant_list(prefix, fields) %}
QVariantList
{{class_name}}::to_variant_list{{prefix}}() const
{
  QVariantList variants;

{% for field in fields %}
  variants << {{ field_value(field) }};
{% endfor %}

  return variants;
}
{% endmacro -%}

{% macro to_variant_hash_sql(schema) %}
QVariantHash
{{class_name}}::to_variant_hash_sql(bool only_changed, bool duplicate) const
{
  QVariantHash variant_hash;

  if (only_changed) {
{% for field in schema %}
    if (is_{{field.name}}_modified())
      {{ insert(field) }}
{% endfor %}
  } else {
{% for field in schema %}
{% if schema.has_rowid_primary_key and field.is_rowid_primary_key %}
    if (duplicate)
      {{ insert(field) }}
{% else %}
    {{ insert(field) }}
{% endif %}
{% endfor %}
  }

  return variant_hash;
}
{% endmacro -%}

{% macro to_variant_list_sql(schema) %}
QVariantList
{{class_name}}::to_variant_list_sql(bool duplicate) const
{
  QVariantList variants;

{% for field in schema %}
{% if schema.has_rowid_primary_key and field.is_rowid_primary_key %}
  if (duplicate)
    variants << {{ field_value(field) }};
{% else %}
  variants << {{ field_value(field) }};
{% endif %}
{% endfor %}

  return variants;
}
{% endmacro -%}

{# ############################################################################################## -#}

{# Fixme: can use call #}
{% macro field_value(field) -%}
{{ cast_to_variant(field) }}
{%- endmacro -%}

{{ to_variant_hash('', schema) }}

{{ to_variant_list('', schema) }}

{% macro field_value(field) -%}
{% if field.type_conversion.cast_to_sql -%}
{{field.type_conversion.cast_to_sql}}(m_{{field.name}})
{%- else -%}
{{ cast_to_variant(field) }}
{%- endif %}
{%- endmacro -%}

{#
{{ to_variant_hash('_sql', schema) }}

{{ to_variant_list('_sql', schema) }}
-#}

{{ to_variant_hash_sql(schema) }}

{{ to_variant_list_sql(schema) }}
