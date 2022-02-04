#version 440

/* *********************************************************************************************** */

layout(std140, binding = 0) uniform buf {
  uniform highp mat4 qt_Matrix;
};

/* *********************************************************************************************** */

layout(location = 0) in  highp vec4 a_vertex;
layout(location = 1) in  highp vec2 a_tex_coord;
layout(location = 2) in  highp vec3 a_radius;
layout(location = 3) in  highp float a_angle;

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

/* *********************************************************************************************** */

/*
attribute highp float _qt_order;

uniform highp float _qt_zRange;

void main() {
  gl_Position.z = (gl_Position.z * _qt_zRange + _qt_order) * gl_Position.w;
}
*/
