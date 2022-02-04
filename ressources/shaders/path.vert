#version 440

/* *********************************************************************************************** */

layout(std140, binding = 0) uniform buf {
  highp mat4 qt_Matrix;
};

/* *********************************************************************************************** */

// highp vec2 a_vertex;
layout(location = 0) in highp vec4 a_vertex;
layout(location = 1) in highp vec2 a_tex_coord;
layout(location = 2) in highp float a_line_length;
layout(location = 3) in highp float a_line_width;
layout(location = 4) in lowp float a_cap;
layout(location = 5) in lowp vec4 a_colour;

/* *********************************************************************************************** */

layout(location = 0) out highp vec2 uv;
layout(location = 1) out highp float line_length;
layout(location = 2) out highp float line_width;
layout(location = 3) out lowp float cap;
layout(location = 4) out lowp vec4 colour;

/* *********************************************************************************************** */

void main() {
  uv = a_tex_coord;
  line_length = a_line_length;
  line_width = a_line_width;
  cap = a_cap;
  colour = a_colour;

  gl_Position = qt_Matrix * a_vertex;
  // gl_Position = qt_Matrix * vec4(a_vertex.xy, 0, 1);
}
