{# -*- mode: fundamental -*- -#}
#ifndef QT_NO_DEBUG_STREAM
QDebug
operator<<(QDebug debug, const {{class_name}} & obj)
{
  QDebugStateSaver saver(debug); // Fixme: ???

  debug.nospace() << QLatin1Literal("{{class_name}}(");
{%- for member in members %}
  debug << obj.{{member.name}}();
{%- if not loop.last %}
  debug << QLatin1Literal(", ");
{%- endif %}{% endfor %}
  debug << ')';

  return debug;
}
#endif
