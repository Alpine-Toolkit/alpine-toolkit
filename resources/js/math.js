/***************************************************************************************************
 *
 * This file is part of the Alpine Toolkit software.
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 * SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

function degrees_to_radians(degrees) {
  return Math.PI/180 * degrees;
}

function radians_to_degrees(radians) {
  return 180/Math.PI * radians;
}

function rotate_vector(v, angle) {
  var rad = degrees_to_radians(angle);
  var c = Math.cos(rad);
  var s = Math.sin(rad);
  return {x: c * v.x - s * v.y,
          y: s * v.x + c * v.y};
}
