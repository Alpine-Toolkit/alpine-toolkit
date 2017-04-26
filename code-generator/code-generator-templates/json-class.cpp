{%- with members = all_members %}
{% include "ctor.cpp" %}

{% include "copy-ctor.cpp" %}
{%- endwith %}

{% include "json-ctor.cpp" %}

{% include "dtor.cpp" %}

{%- with members = all_members %}
{% include "copy-operator.cpp" %}
{%- endwith %}

{%- for member in members %}
{% include "setter.cpp" %}
{% endfor %}
{% include "json-serializer.cpp" %}

{% include "data-stream-operator.cpp" %}

{% include "debug.cpp" %}
