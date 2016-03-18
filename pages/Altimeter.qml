import QtQml 2.2
import QtQuick 2.6

import QtQuick.Layouts 1.1
import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0

import QtCarto 1.0
import QtPositioning 5.5
import QtSensors 5.1

Pane {
    id: altimeter_pane

    // PressureSensor
    BarimeterAltimeterSensor {
        id: pressure_sensor
        // id: barimeter_altimeter_sensor
        active: true // ???
        // altitude_offset: 40; // pressure_sensor.reading

        Component.onCompleted: {
            // pressure_sensor.reading.altitude_offset = -40.;
        }

        onReadingChanged: {
            // Mean Filter
            var pressure = pressure_sensor.reading.pressure; // 82500 Pa
            var temperature = pressure_sensor.reading.temperature; // 0
            var altitude = pressure_sensor.reading.altitude;
            pressure_label.text = Number(pressure).toLocaleString() + " Pa";
            altitude_label.text = Number(altitude).toLocaleString() + " m";
            console.info(pressure, temperature, altitude);
        }
    }

    PositionSource {
        id: position_source
        updateInterval: 10
        active: true

        onPositionChanged: {
            var coordinate = position_source.position.coordinate;
            position_label.text = coordinate.longitude + " " + coordinate.latitude + " +- " + position_source.position.horizontalAccuracy;
            gps_altitude_label.text = coordinate.altitude + " +- " + position_source.position.verticalAccuracy;
        }
    }

    ColumnLayout {
        width: parent.width
        anchors.topMargin: 30
        spacing: 30

        TextInput {
            id: altitude_text_field
            // anchors.top: parent.top
            // anchors.horizontalCenter: parent.horizontalCenter
            // anchors.topMargin: 30
            // anchors.bottomMargin: 30

            Layout.alignment: Qt.AlignCenter
            // Layout.preferredWidth: parent.width
            // Layout.preferredHeight: 40

            font.pointSize: 32
            text: "0"
            inputMethodHints: Qt.ImhDigitsOnly
            validator: IntValidator {bottom: 0; top: 11000;}
            onEditingFinished: {
                console.info("clicked on calibrate", altitude_text_field.text);
                pressure_sensor.reading.altitude = Number.fromLocaleString(altitude_text_field.text);
            }
        }

        Button {
            id: calibrate_button

            // anchors.horizontalCenter: parent.horizontalCenter
            // anchors.top: parent.top
            // anchors.topMargin: 30
            // anchors.bottomMargin: 30

            Layout.alignment: Qt.AlignCenter
            // Layout.preferredWidth: parent.width
            // Layout.preferredHeight: 40

            text: "Calibrate"
            // onClicked: stack_view.push(Qt.resolvedUrl("CalibrateAltimeter.qml"))
            onClicked: {
                console.info("clicked on calibrate", altitude_text_field.text);
                pressure_sensor.reading.altitude = Number.fromLocaleString(altitude_text_field.text);
            }
        }

        GridLayout {
            width: parent.width

            // anchors.horizontalCenter: parent.horizontalCenter
            // anchors.top: calibrate_button.top
            // anchors.topMargin: 30
            // anchors.bottomMargin: 30
            // anchors.leftMargin: 30

            Layout.alignment: Qt.AlignCenter
            // Layout.preferredWidth: parent.width
            // Layout.preferredHeight: 40

            columns: 2

            Text {
                text: "Pressure"
            }
            Text {
                id: pressure_label
            }

            Text {
                text: "Altitude"
            }
            Text {
                id: altitude_label
            }

            Text {
                text: "Position"
            }
            Text {
                id: position_label
            }

            Text {
                text: "GPS Altitude"
            }
            Text {
                id: gps_altitude_label
            }
        }
    }
}
