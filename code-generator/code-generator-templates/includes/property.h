{# -*- mode: fundamental -*- -#}
{%- macro property(name, type) -%}
Q_PROPERTY({{type}} {{name}} READ {{name}} WRITE set_{{name}} NOTIFY {{name}}Changed)
{%- endmacro -%}
