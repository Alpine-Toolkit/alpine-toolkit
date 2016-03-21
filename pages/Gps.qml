import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0

import QtSensors 5.1

import "qrc:/js/gps.js" as GpsHelper

Pane {
    id: gps_pane

    transform: Scale {
        origin.x: gps_pane.width/2
        origin.y: gps_pane.height/2
        xScale: 1 // -1 for screen facing bottom
        yScale: 1 // -1 for screen facing top
    }

   Compass {
       id: compass
       active: true
       // onReadingChanged: {
       //     var azimuth = compass.reading.azimuth;
       //     // var calibration_level = compass.reading.calibrationLevel;
       //     azimuth_label.text = azimuth.toFixed(0);
       //     console.info("Azimuth", azimuth)
       //     canvas.requestPaint();
       // }
   }

   TiltSensor {
       id: tilt_sensor
       active: true
       // Calibrates the tilt sensor. Uses the current tilt angles as 0.
       // onReadingChanged: {
       //     var x_rotation = tilt_sensor.reading.xRotation;
       //     var y_rotation = tilt_sensor.reading.yRotation;
       //     // x_tilt_label.text = x_rotation;
       //     // y_tilt_label.text = y_rotation;
       //     canvas.requestPaint();
       // }
   }

   Timer {
       interval: 100; // ms
       running: true;
       repeat: true
       onTriggered: {
           var azimuth = compass.reading.azimuth;
           azimuth_label.text = azimuth.toFixed(0);
           canvas.requestPaint();
       }
   }

   ColumnLayout {
       id: column_layout
       width: parent.width
       anchors.top: parent.top
       anchors.topMargin: 30
       spacing: 30

       GridLayout {
           width: parent.width
           Layout.alignment: Qt.AlignCenter
           columns: 2
           columnSpacing : 2 * Screen.devicePixelRatio
           rowSpacing : 2 * Screen.devicePixelRatio

           Label {
               text: "Azimuth"
           }
           Label {
               id: azimuth_label
               text: "unknown"
           }

           // Label {
           //     color: "white"
           //     text: "X Tilt"
           // }
           // Label {
           //     color: "white"
           //     id: x_tilt_label
           // }

           // Label {
           //     color: "white"
           //     text: "Y Tilt"
           // }
           // Label {
           //     color: "white"
           //     id: y_tilt_label
           // }
       }
   }

   Canvas {
       id: canvas
       anchors.centerIn: parent // due to scaled size
       // anchors.top: parent.top // column_layout.bottom
       // anchors.horizontalCenter: parent.horizontalCenter

       antialiasing: true
       // width: parent.width * .9
       // height: (parent.height - column_layout.height) * .9
       width: parent.width * .9 * Screen.devicePixelRatio
       height: (parent.height - column_layout.height) * .9 * Screen.devicePixelRatio
       scale: 1. / Screen.devicePixelRatio
       transformOrigin: Item.Center

       onPaint: GpsHelper.paint_compass(canvas, compass)
   }
}
