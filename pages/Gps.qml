import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
// import Qt.labs.controls.material 1.0

import QtSensors 5.1

import Local 1.0

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

    SatelliteModel {
        id: satellite_model
        running: true
        onErrorFound: errorLabel.text = qsTr("Last Error: %1", "%1=error number").arg(code)
    }

    Timer {
        interval: 500;
        running: true;
        repeat: true
        onTriggered: {
            for (var i = 0; i < satellite_model.rowCount(); i++) {
                var index = satellite_model.index(i, 0);
                console.log("satellite", i,
                    satellite_model.data(index, SatelliteModel.IdentifierRole),
                    satellite_model.data(index, SatelliteModel.InUseRole),
                    satellite_model.data(index, SatelliteModel.SignalStrengthRole),
                    satellite_model.data(index, SatelliteModel.ElevationRole),
                    satellite_model.data(index, SatelliteModel.AzimuthRole)
                );
            }
        }
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
           columnSpacing : 2
           rowSpacing : 2

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
       width: parent.width - horizontal_margin
       height: parent.height - column_layout.height
       property real horizontal_margin: 10

       onPaint: GpsHelper.paint_compass(canvas, compass, satellite_model)
   }

   Rectangle {
       anchors.bottom: parent.bottom
       width: parent.width
       height: parent.height / 6
       // anchors.left: parent.left
       // anchors.right: parent.right
       // anchors.margins: rect.myMargin
       // border.width: 3
       // radius: 10
       // border.color: "black"

       Item {
           id: rect
           anchors.fill: parent
           anchors.margins: horizontal_margin
           property int horizontal_margin: 7

           Row {
               id: view
               property int rows: repeater.model.entryCount
               property int single_width: rect.width/rows - rect.horizontal_margin
               spacing: rect.horizontal_margin

               Repeater {
                   id: repeater
                   model: satellite_model
                   delegate: Rectangle {
                       height: rect.height
                       width: view.single_width
                       Rectangle {
                           anchors.bottom: parent.bottom
                           width: parent.width
                           height: parent.height * signalStrength / 100
                           color: isInUse ? "#4caf50" : "#f44336"
                       }
                       Text {
                           anchors.horizontalCenter: parent.horizontalCenter
                           anchors.bottom: parent.bottom
                           text: satelliteIdentifier
                       }
                   }
               }
           }
       }
   }
}
