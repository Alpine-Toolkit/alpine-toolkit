#version 440

/**************************************************************************************************/

const lowp float antialias = 1.0;
const lowp float linewidth = 1.5;
const lowp float M_PI = 3.14159265358979323846;
const lowp float SQRT_2 = 1.4142135623730951;

/**************************************************************************************************/

layout(std140, binding = 0) uniform buf {
  lowp float qt_Opacity;
  lowp vec4 cone_colour;
  lowp vec4 accuracy_colour;
};

/**************************************************************************************************/

layout(location = 0) in highp vec2 tex_coord;
layout(location = 1) in highp vec3 radius;
layout(location = 2) in highp float angle;

layout(location = 0) out highp vec4 fragColor;

/**************************************************************************************************/

lowp float
planar_rotation(highp vec2 P, lowp float angle)
{
  angle *= M_PI / 180.;
  highp vec2 cos_sin = vec2(cos(angle), sin(angle));
  return dot(cos_sin, P);
}

highp vec4
stroke(lowp float distance, lowp float linewidth, lowp float antialias, lowp vec4 stroke)
{
  highp vec4 frag_colour;
  highp float t = linewidth/2.0 - antialias;
  highp float signed_distance = distance;
  highp float border_distance = abs(signed_distance) - t;
  highp float alpha = border_distance/antialias;
  alpha = exp(-alpha*alpha);

  if (border_distance > (linewidth/2.0 + antialias))
    discard;
  else if (border_distance < 0.0)
    frag_colour = stroke;
  else
    frag_colour = vec4(stroke.rgb*alpha, 1.);

  return frag_colour;
}

highp vec4
filled(lowp float distance, lowp float linewidth, lowp float antialias, lowp vec4 fill)
{
  highp vec4 frag_colour;
  highp float t = linewidth/2.0 - antialias;
  highp float signed_distance = distance;
  highp float border_distance = abs(signed_distance) - t;
  highp float alpha = border_distance/antialias;
  alpha = exp(-alpha*alpha);

  // if (alpha == .0) discard;
  // Within linestroke
  if (border_distance < 0.0)
    frag_colour = fill;
  // Within shape
  else if (signed_distance < 0.0)
    frag_colour = fill;
  else
    // Outside shape
    if (border_distance > (linewidth/2.0 + antialias))
      discard;
      // frag_colour = vec4(0, 0, 0, 0);
    else { // Line stroke exterior border
      if (alpha == .0)
        discard;
      else
        // frag_colour = vec4(fill.rgb*alpha, 1.);
        frag_colour = vec4(fill.rgb*alpha, alpha);
    }

  return frag_colour;
}

highp vec4
outline(lowp float distance, lowp float linewidth, lowp float antialias, lowp vec4 stroke, lowp vec4 fill)
{
  highp vec4 frag_colour;
  highp float t = linewidth/2.0 - antialias;
  highp float signed_distance = distance;
  highp float border_distance = abs(signed_distance) - t;
  highp float alpha = border_distance/antialias;
  alpha = exp(-alpha*alpha);

  // Within linestroke
  if (border_distance < 0.0)
    frag_colour = stroke;
  else if (signed_distance < 0.0)
    // Inside shape
    if (border_distance > (linewidth/2.0 + antialias))
      frag_colour = fill;
    else // Line stroke interior border
      frag_colour = mix(fill, stroke, alpha);
  else
    // Outside shape
    if (border_distance > (linewidth/2.0 + antialias))
      discard;
    else // Line stroke exterior border
      frag_colour = vec4(stroke.rgb*alpha, 1.0);

  return frag_colour;
}

/**************************************************************************************************/

lowp float
marker_ring(highp vec2 P, lowp float radius)
{
  return length(P) - radius;
}

lowp float
location_marker(highp vec2 P, lowp vec3 radius, lowp float angle)
{
  highp float p1 = planar_rotation(P,  30. + angle);
  highp float p2 = planar_rotation(P, -30. + angle);
  highp float r_cone = marker_ring(P, radius.x);
  highp float r_dot = marker_ring(P, radius.y);
  highp float cone = max(p1, p2);
  return min(max(cone, r_cone), r_dot);
}

/**************************************************************************************************/

void
main() {
  // float d = marker_ring(tex_coord, radius);
  highp float d_accuray = marker_ring(tex_coord, radius.z);
  highp float d_location = location_marker(tex_coord, radius, angle);
  highp vec4 colour;
  if (d_accuray < linewidth)
    colour = accuracy_colour;
  else
    colour = cone_colour;
  highp vec4 frag_colour = filled(d_location, linewidth, antialias, colour);
  fragColor = frag_colour * qt_Opacity;
}
