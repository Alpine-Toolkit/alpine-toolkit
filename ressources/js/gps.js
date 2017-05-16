/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine ToolKit software.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

Qt.include('qrc:/js/math.js');

function paint_compass(canvas, compass, satellite_model) {
  // X axis point to right
  // Y axis point to bottom
  // Positive rotation is clockwise

  var ctx = canvas.getContext('2d');
  ctx.reset();
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  ctx.font = "15px sans-serif"; // roboto ?

  var canvas_radius = Math.min(canvas.width, canvas.height) / 2;
  var hemisphere_radius = canvas_radius - 2 * 15; // for NW

  // center frame
  ctx.translate(canvas.width / 2, canvas.height / 2);

  // var azimuth = 25;
  // var x_tilt = 10;
  // var y_tilt = 10;

  var reading = compass.reading;
  var azimuth = reading ? reading.azimuth : 0;
  reading = tilt_sensor.reading;
  var x_tilt, y_tilt;
  if (reading) {
    x_tilt = reading.xRotation;
    y_tilt = reading.yRotation;
  } else {
    x_tilt = 0;
    y_tilt = 0;
  }

  // var radius_60 = hemisphere_radius * Math.cos(Math.PI/3);
  // var radius_30 = hemisphere_radius * Math.cos(Math.PI/6);
  var radius_60 = hemisphere_radius / 3;
  var radius_30 = hemisphere_radius * 2/3;

  // Draw bubble
  ctx.fillStyle = '#c8c8c8';
  ctx.beginPath();
  var x_bubble = - y_tilt / 90 * hemisphere_radius;
  var y_bubble = - x_tilt / 90 * hemisphere_radius;
  var radius_bubble = radius_60 * (90 - Math.max(Math.abs(x_tilt), Math.abs(y_tilt))) / 90;
  ctx.arc(x_bubble, y_bubble, radius_bubble, 0, 2*Math.PI, true);
  ctx.fill();

  // Draw compass
  var azimuth_rad = degrees_to_radians(azimuth);
  ctx.rotate(-azimuth_rad);

  ctx.strokeStyle = 'black';
  ctx.fillStyle = 'black';
  ctx.lineWidth = 2;

  // Draw elevation circles
  for (var i = 0; i < 3; i++) {
    ctx.beginPath();
    // var radius = hemisphere_radius * Math.cos(Math.PI / 6 * i);
    var radius = hemisphere_radius * (i+1)/3;
    ctx.arc(0, 0, radius, 0, 2*Math.PI, true);
    ctx.stroke();
  }
  ctx.textAlign = 'left';
  var p_on_x = {x: radius_30, y: 0};
  var label_offset_x = 5;
  var label_offset_y = 15;
  ctx.fillText("30°", p_on_x.x + label_offset_x, p_on_x.y + label_offset_y);
  p_on_x = {x: radius_60, y: 0};
  ctx.fillText("60°", p_on_x.x + label_offset_x, p_on_x.y + label_offset_y);

  // Draw axes
  ctx.beginPath();
  ctx.moveTo(-hemisphere_radius, 0);
  ctx.lineTo(hemisphere_radius, 0);
  ctx.stroke();
  ctx.beginPath();
  ctx.moveTo(0, -hemisphere_radius);
  ctx.lineTo(0, hemisphere_radius);
  ctx.stroke();

  // Draw ticks
  var tick_angle_step = 90 / 4;
  var tick_length = hemisphere_radius / 10;
  var tick_p0 = {x: hemisphere_radius - tick_length, y: 0}
  var tick_p1 = {x: hemisphere_radius, y: 0}
  for (var quadrant = 0; quadrant < 4; quadrant += 1) {
    for (var i = 1; i <= 3; i += 1) {
      var tick_angle = quadrant * 90 + i * tick_angle_step;
      var p0 = rotate_vector(tick_p0, tick_angle);
      var p1 = rotate_vector(tick_p1, tick_angle);
      ctx.beginPath();
      ctx.moveTo(p0.x, p0.y);
      ctx.lineTo(p1.x, p1.y);
      ctx.stroke();
    }
  }

  // Draw north dot
  ctx.fillStyle = 'black';
  var p = rotate_vector(tick_p1, azimuth - 90);
  ctx.beginPath();
  ctx.arc(p.x, p.y, 6, 0, 2*Math.PI, true);
  ctx.fill();

  // Draw cardinal points
  ctx.textAlign = 'center';
  var p0 = {x: hemisphere_radius + tick_length, y: 0}
  var poles = [
    {angle: 0, text: 'N'},
    {angle: 45, text: 'NE'},
    {angle: -45, text: 'NW'},
    {angle: 90, text: 'E'},
    {angle: -90, text: 'W'},
    {angle: 135, text: 'SE'},
    {angle: -135, text: 'SW'},
    {angle: 180, text: 'S'},
  ];
  for (var i = 0; i < poles.length; i++) {
    var pole = poles[i];
    var p = rotate_vector(p0, pole.angle -90);
    ctx.fillText(pole.text, p.x, p.y);
  }

  for (var i = 0; i < satellite_model.rowCount(); i++) {
    var index = satellite_model.index(i, 0);
    var satellite_id = satellite_model.data(index, SatelliteModel.IdentifierRole);
    var in_use = satellite_model.data(index, SatelliteModel.InUseRole);
    var signal_stength = satellite_model.data(index, SatelliteModel.SignalStrengthRole);
    var satellite_elevation = satellite_model.data(index, SatelliteModel.ElevationRole);
    var satellite_azimuth = satellite_model.data(index, SatelliteModel.AzimuthRole);

    if (in_use) {
      ctx.fillStyle = 'green';
    } else {
      ctx.fillStyle = 'red';
    }

    // var radius = hemisphere_radius * Math.cos(degrees_to_radians(satellite_elevation));
    var radius = hemisphere_radius * (1 - satellite_elevation / 90);
    var p_on_x = {x: radius, y: 0}
    var p = rotate_vector(p_on_x, satellite_azimuth - 90);
    var dot_radius = 3;
    ctx.beginPath();
    ctx.arc(p.x, p.y, dot_radius, 0, 2*Math.PI, true);
    ctx.fill();
    ctx.fillText(satellite_id, p.x + 4*dot_radius, p.y + 4*dot_radius);
  }
}
