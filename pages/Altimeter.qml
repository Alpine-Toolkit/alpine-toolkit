import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
// import Qt.labs.controls.material 1.0

import Local 1.0
import QtPositioning 5.5
import QtSensors 5.1 // .8

Pane {
    id: altimeter_pane

    // Fixme: If not available ???
    // PressureSensor
    BarimeterAltimeterSensor {
        id: pressure_sensor
        active: true // ???
        // altitude_offset: 40; // pressure_sensor.reading

        Component.onCompleted: {
            // pressure_sensor.reading.altitude_offset = -40.;
        }

        onReadingChanged: {
            // Mean Filter
            var pressure = pressure_sensor.reading.pressure; // 82500 Pa
            // var temperature = pressure_sensor.reading.temperature; // 0
            var altitude = pressure_sensor.reading.altitude;
            var sea_level_pressure = pressure_sensor.reading.seaLevelPressure;
            pressure_label.text = Number(pressure).toLocaleString() + " Pa";
            // sea_level_pressure_label.text = Number(sea_level_pressure).toLocaleString() + " Pa";
            altitude_label.text = Number(altitude).toLocaleString() + " m";
            console.info(pressure, altitude, sea_level_pressure);
        }
    }

    PositionSource {
        id: position_source
        updateInterval: 10
        active: true

        onPositionChanged: {
            var position = position_source.position;
            var coordinate = position.coordinate;
            // position_label.text = coordinate.longitude + " " + coordinate.latitude + " +- " + position_source.position.horizontalAccuracy;
            if (coordinate.altitudeValid) {
                gps_altitude_label.text = coordinate.altitude; // + " +- " + position.verticalAccuracy;
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 30
        spacing: 30

        GridLayout {
            width: parent.width
            Layout.alignment: Qt.AlignCenter
            columns: 2
            columnSpacing : 2 * Screen.devicePixelRatio
            rowSpacing : 2 * Screen.devicePixelRatio

            Label {
                font.pointSize: 20
                text: qsTr("Altitude")
            }
            Label {
                font.pointSize: 20
                id: altitude_label
                text: "unknown"
            }

            Label {
                font.pointSize: 20
                text: "GPS"
            }
            Label {
                font.pointSize: 20
                id: gps_altitude_label
                text: "unknown"
            }

            Label {
                font.pointSize: 20
                text: qsTr("Pressure")
            }
            Label {
                font.pointSize: 20
                id: pressure_label
                text: "unknown"
            }
        }

        Button {
            id: calibrate_button
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Calibrate")
            onClicked: calibrate_popup.open()
        }
    }

    Popup {
        id: calibrate_popup
        modal: true
        focus: true
        // margins: 5 * Screen.devicePixelRatio // must be centered
        x: (application_window.width - width) / 2 // Fixme; not centered
        y: application_window.height / 6
        width: application_window.width * .9
        contentHeight: column.height
        // closePolicy: Popup.OnEscape | Popup.NoAutoClose

        Column {
            id: column
            width: parent.width
            spacing: 5 * Screen.devicePixelRatio

            Label {
                font.pointSize: 20
                font.bold: true
                text: qsTr("Calibrate")
            }

            TextField {
                id: altitude_text_field
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 32
                placeholderText: "enter altitude"
                inputMethodHints: Qt.ImhDigitsOnly
                validator: IntValidator {bottom: 0; top: 11000;}
            }

            Row {
                spacing: 5 * Screen.devicePixelRatio
                anchors.right: parent.right

                Button {
                    text: "Cancel"
                    onClicked: calibrate_popup.close()
                    // label.color: "#42a5f5ff"
                    background: null
                }
                Button {
                    text: "Ok"
                    onClicked: {
                        if (altitude_text_field.text) {
                            var altitude = Number.fromLocaleString(altitude_text_field.text);
                            console.info("clicked on calibrate", altitude_text_field.text);
                            pressure_sensor.reading.altitude = Number.fromLocaleString(altitude_text_field.text);
                            // save sea_level_pressure in application
                        }
                        calibrate_popup.close()
                    }
                    background: null
                }
            }
        }
    }
}

