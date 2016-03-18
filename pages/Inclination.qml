import QtQuick 2.2

import QtQuick.Extras 1.4
import QtQuick.Extras.Private 1.0

import QtQuick.Layouts 1.1
import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0

import QtSensors 5.1

Pane {
    id: inclination_pane

   TiltSensor {
       id: tilt_sensor
       active: true
       // Calibrates the tilt sensor. Uses the current tilt angles as 0.
       onReadingChanged: {
           var x_rotation = tilt_sensor.reading.xRotation;
           var y_rotation = tilt_sensor.reading.yRotation;
           x_tilt_gauge.value = x_rotation;
           y_tilt_gauge.value = y_rotation;
           console.info(x_rotation, y_rotation);
       }
   }

   CircularGauge {
       id: x_tilt_gauge
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.top: parent.top
       anchors.topMargin: 30
       anchors.bottomMargin: 30
       minimumValue: 0
       maximumValue: 90

       // style: CircularGaugeStyle {
       //     id: style

       //     function degreesToRadians(degrees) {
       //         return degrees * (Math.PI / 180);
       //     }

       //     background: Canvas {
       //         onPaint: {
       //             var ctx = getContext("2d");
       //             ctx.reset();

       //             ctx.beginPath();
       //             ctx.strokeStyle = "#e34c22";
       //             ctx.lineWidth = outerRadius * 0.02;

       //             ctx.arc(outerRadius, outerRadius, outerRadius - ctx.lineWidth / 2,
       //             degreesToRadians(valueToAngle(80) - 90), degreesToRadians(valueToAngle(100) - 90));
       //             ctx.stroke();
       //         }
       //     }

       //     tickmark: Rectangle {
       //         visible: styleData.value < 80 || styleData.value % 10 == 0
       //         implicitWidth: outerRadius * 0.02
       //         antialiasing: true
       //         implicitHeight: outerRadius * 0.06
       //         color: styleData.value >= 80 ? "#e34c22" : "#e5e5e5"
       //     }

       //     minorTickmark: Rectangle {
       //         visible: styleData.value < 80
       //         implicitWidth: outerRadius * 0.01
       //         antialiasing: true
       //         implicitHeight: outerRadius * 0.03
       //         color: "#e5e5e5"
       //     }

       //     tickmarkLabel: Text {
       //         font.pixelSize: Math.max(6, outerRadius * 0.1)
       //         text: styleData.value
       //         color: styleData.value >= 80 ? "#e34c22" : "#e5e5e5"
       //         antialiasing: true
       //     }

       //     needle: Rectangle {
       //         y: outerRadius * 0.15
       //         implicitWidth: outerRadius * 0.03
       //         implicitHeight: outerRadius * 0.9
       //         antialiasing: true
       //         color: "#e5e5e5"
       //     }

       //     foreground: Item {
       //         Rectangle {
       //             width: outerRadius * 0.2
       //             height: width
       //             radius: width / 2
       //             color: "#e5e5e5"
       //             anchors.centerIn: parent
       //         }
       //     }
       // }

       Gauge {
           // Fixme: bar -> tick
           id: y_tilt_gauge
           anchors.horizontalCenter: parent.horizontalCenter
           anchors.top: x_tilt_gauge.bottom
           anchors.topMargin: 30
           anchors.bottomMargin: 30
           minimumValue: -90
           maximumValue: 90
           tickmarkStepSize: 45
           orientation: Qt.Horizontal
       }
   }
}
