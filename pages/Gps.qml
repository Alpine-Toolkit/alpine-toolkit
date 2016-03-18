import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0

import QtSensors 5.1

Pane {
    id: gps_pane

    // property real azimuth;
    // property real x_tilt;
    // property real y_tilt;

   Compass {
       // calibration
       id: compass
       active: true
       onReadingChanged: {
           var azimuth = compass.reading.azimuth;
           // var calibration_level = compass.reading.calibrationLevel;
           // azimuth_label.text = azimuth; // Number.fromLocaleString(azimuth);
           console.info("Azimuth", azimuth)
           canvas.requestPaint();
       }
   }

   TiltSensor {
       id: tilt_sensor
       active: true
       // Calibrates the tilt sensor. Uses the current tilt angles as 0.
       onReadingChanged: {
           var x_rotation = tilt_sensor.reading.xRotation;
           var y_rotation = tilt_sensor.reading.yRotation;
           // x_tilt_label.text = x_rotation;
           // y_tilt_label.text = y_rotation;
           canvas.requestPaint();
       }
   }

   // GridLayout {
   //     width: parent.width

   //     // anchors.horizontalCenter: parent.horizontalCenter
   //     // anchors.top: calibrate_button.top
   //     // anchors.topMargin: 30
   //     // anchors.bottomMargin: 30
   //     // anchors.leftMargin: 30

   //     Layout.alignment: Qt.AlignCenter
   //     // Layout.preferredWidth: parent.width
   //     // Layout.preferredHeight: 40

   //     columns: 2

   //     Text {
   //         color: "white"
   //         text: "X Tilt"
   //     }
   //     Text {
   //         color: "white"
   //         id: x_tilt_label
   //     }

   //     Text {
   //         color: "white"
   //         text: "Y Tilt"
   //     }
   //     Text {
   //         color: "white"
   //         id: y_tilt_label
   //     }

   //     Text {
   //         color: "white"
   //         text: "Azimuth"
   //     }
   //     Text {
   //         color: "white"
   //         id: azimuth_label
   //     }
   // }

    Canvas {
        id: canvas
        anchors.centerIn: parent
        width: parent.width * .9 * Screen.devicePixelRatio
        height: parent.height * .9 * Screen.devicePixelRatio

        // canvasSize: Qt.size(width * 2, height * 2);
        antialiasing: true
        scale: 1. /  Screen.devicePixelRatio
        transformOrigin: Item.Center

        onPaint:{
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

            var ctx = canvas.getContext('2d');
            ctx.reset();
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            var canvas_radius = Math.min(canvas.width, canvas.height) / 2;
            var hemisphere_radius = canvas_radius * .8;

            ctx.translate(canvas.width / 2, canvas.height / 2);

            // var reading = compass.reading;
            // var azimuth = reading ? reading.azimuth : 0;
            // reading = tilt_sensor.reading;
            // var x_tilt, y_tilt;
            // if (reading) {
            //     x_tilt = reading.xRotation;
            //     y_tilt = reading.yRotation;
            // } else {
            //     x_tilt = 0;
            //     y_tilt = 0;
            // }

            var azimuth = 25;
            var x_tilt = 10;
            var y_tilt = 10;

            var azimuth_rad = degrees_to_radians(azimuth);
            ctx.rotate(azimuth_rad);

            ctx.fillStyle = 'black';

            ctx.beginPath();
            var x_bubble = - y_tilt / 90 * hemisphere_radius;
            var y_bubble = - x_tilt / 90 * hemisphere_radius;
            var radius_bubble = hemisphere_radius / 3 * (90 - Math.max(Math.abs(x_tilt), Math.abs(y_tilt))) / 90;
            ctx.arc(x_bubble, y_bubble, radius_bubble, 0, 2*Math.PI, true);
            ctx.fill();

            ctx.strokeStyle = 'rgb(255, 0, 0)';
            ctx.lineWidth = 4;

            for (var i = 1; i <= 3; i++) {
                ctx.beginPath();
                var radius = hemisphere_radius * i / 3;
                ctx.arc(0, 0, radius, 0, 2*Math.PI, true);
                ctx.stroke();
            }

           ctx.beginPath();
           ctx.moveTo(-hemisphere_radius, 0);
           ctx.lineTo(hemisphere_radius, 0);
           ctx.stroke();

           ctx.beginPath();
           ctx.moveTo(0, -hemisphere_radius);
           ctx.lineTo(0, hemisphere_radius);
           ctx.stroke();

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

           var p = rotate_vector(tick_p1, - (azimuth + 90));
           ctx.beginPath();
           ctx.arc(p.x, p.y, 6, 0, 2*Math.PI, true);
           ctx.fill();

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
    }
}
