function degrees_to_radians(degrees) {
  return Math.PI/180 * degrees;
}

function rotate_vector(v, angle) {
  var rad = degrees_to_radians(angle);
  var c = Math.cos(rad);
  var s = Math.sin(rad);
  return {x: c * v.x - s * v.y,
          y: s * v.x + c * v.y};
}

function paint_compass(canvas, compass) {
  // X axis point to right
  // Y axis point to bottom
  // Positive rotation is clockwise

  var ctx = canvas.getContext('2d');
  ctx.reset();
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  var canvas_radius = Math.min(canvas.width, canvas.height) / 2;
  var hemisphere_radius = canvas_radius * .8;

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

  ctx.fillStyle = 'black';

  // Draw bubble
  ctx.beginPath();
  var x_bubble = - y_tilt / 90 * hemisphere_radius;
  var y_bubble = - x_tilt / 90 * hemisphere_radius;
  var radius_bubble = hemisphere_radius / 3 * (90 - Math.max(Math.abs(x_tilt), Math.abs(y_tilt))) / 90;
  ctx.arc(x_bubble, y_bubble, radius_bubble, 0, 2*Math.PI, true);
  ctx.fill();

  var azimuth_rad = degrees_to_radians(azimuth);
  ctx.rotate(-azimuth_rad);

  ctx.strokeStyle = 'rgb(255, 0, 0)';
  ctx.lineWidth = 4;

  // Draw elevation circles
  for (var i = 1; i <= 3; i++) {
    ctx.beginPath();
    var radius = hemisphere_radius * i / 3;
    ctx.arc(0, 0, radius, 0, 2*Math.PI, true);
    ctx.stroke();
  }

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
  var p = rotate_vector(tick_p1, azimuth - 90);
  ctx.beginPath();
  ctx.arc(p.x, p.y, 6, 0, 2*Math.PI, true);
  ctx.fill();

  // Draw cardinal points
  ctx.font = "20px sans-serif";
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
}
