// path_fragment_shader.glsl

/* *********************************************************************************************** */

// #shader_type fragment

// error: cannot initialize uniform cap_type in GLSL 1.10 (GLSL 1.20 required)
// #version 120

/* *********************************************************************************************** */

const int cap_type = 1;
const int line_join = 1;
const lowp float antialias_diameter = 1.;

/* *********************************************************************************************** */

uniform lowp float qt_Opacity;

/* *********************************************************************************************** */

varying highp vec2 uv;
varying highp float line_length;
varying highp float line_width;
varying lowp float cap;
varying lowp vec4 colour;

/* *********************************************************************************************** */

// Compute distance to cap
highp float
distance_to_cap(highp int type, highp float dx, highp float dy, highp float t)
{
  return length(vec2(dx, dy));
}

// Compute distance to join
highp float
join(highp in vec2 uv, highp in float line_stop, highp in float line_width)
{
  float u = uv.x;
  float d = abs(uv.y);

  if (u < .0)
    d = max(d, length(uv));
  else if (u > line_stop)
    d = max(d, length(uv - vec2(line_stop, 0)));

  return d;
}

/* *********************************************************************************************** */

void main()
{
  // If colour is fully transparent we just discard the fragment
  if (colour.a <= .0)
    discard;

  highp vec4 frag_colour;

  highp float u = uv.x;
  highp float v = uv.y;
  highp float t = line_width/2. - antialias_diameter;

  highp float dy = abs(v);

  highp float line_start = .0;
  highp float line_stop = line_length;

  highp float d = .0;
  // start cap
  if (cap == -1.) { //  && u < .0
    d = distance_to_cap(cap_type, abs(u), dy, t);
  }
  // stop cap
  else if (cap == 1. && u > line_stop)
    d = distance_to_cap(cap_type, abs(u) - line_stop, dy, t);
  else
    d = join(uv, line_stop, line_width);

  // Anti-alias test, distance to border
  d -= t;
  if (d < .0) {
    frag_colour = colour;
    /* frag_colour = vec4(0, 1, 1, 1); */
  } else {
    d /= antialias_diameter;
    frag_colour = vec4(colour.xyz, exp(-d*d) * colour.a);
    // frag_colour = vec4(1, d, 0, 1);
  }

  // frag_colour = vec4(0, 0, 0, 1);
  gl_FragColor = frag_colour * qt_Opacity;
}
