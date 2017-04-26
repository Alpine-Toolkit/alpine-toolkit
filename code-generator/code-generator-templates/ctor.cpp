{# -*- mode: fundamental -*- -#}
{{class_name}}::{{class_name}}()
{#-
{%- for base_class in base_classes %}
{% if loop.first %}  : {% else %}    {% endif %}{{ base_class }}(){% if not loop.last or members %},{% endif %}
{%- endfor %}
-#}
{%- for member in members %}
{% if loop.first %}  : {% else %}    {% endif %}{{member.m_name}}(){% if not loop.last %},{% endif %}
{%- endfor %}
{}
