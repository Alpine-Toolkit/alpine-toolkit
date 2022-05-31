#version 440

/* *********************************************************************************************** */

layout(std140, binding = 0) uniform buf {
  highp mat4 qt_Matrix;
  lowp float qt_Opacity;
  lowp vec4 cone_colour;
  lowp vec4 accuracy_colour;
};

/* *********************************************************************************************** */

layout(location = 0) in highp vec4 a_vertex;
layout(location = 1) in highp vec2 a_tex_coord;
layout(location = 2) in highp vec3 a_radius;
layout(location = 3) in highp float a_angle;

/* *********************************************************************************************** */

layout(location = 0) out highp vec2 tex_coord;
layout(location = 1) out highp vec3 radius;
layout(location = 2) out highp float angle;

/* *********************************************************************************************** */

void main() {
  tex_coord = a_tex_coord;
  radius = a_radius;
  angle = a_angle;
  gl_Position = qt_Matrix * a_vertex;
}
