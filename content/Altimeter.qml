import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1
import QtSensors 5.1
import QtCarto 1.0
import QtQml 2.2

Item {
    width: parent.width
    height: parent.height

    property real progress: 0

    SequentialAnimation on progress {
        loops: Animation.Infinite
        running: true
        NumberAnimation {
            from: 0
            to: 1
            duration: 3000
        }
        NumberAnimation {
            from: 1
            to: 0
            duration: 3000
        }
    }

    // PressureSensor
    BarimeterAltimeterSensor {
        id: pressure_sensor
        // id: barimeter_altimeter_sensor
        active: true // ???
        // altitude_offset: 40; // pressure_sensor.reading

        Component.onCompleted: {
            // pressure_sensor.altitude_offset = -40.;
            pressure_sensor.reading.altitude_offset = -40.;
        }

        onReadingChanged: {
            // Mean Filter
            var pressure = pressure_sensor.reading.pressure; // 82500 Pa
            var temperature = pressure_sensor.reading.temperature; // 0
            var altitude = pressure_sensor.reading.altitude;
            pressure_label.text = pressure + " Pa";
            altitude_label.text = altitude + " m";
            console.info(pressure, temperature, altitude);
        }
    }

    ColumnLayout {
        width: parent.width
        anchors.topMargin: 30
        spacing: 10

        TextField {
            id: altitude_text_field
            // anchors.top: parent.top
            // anchors.horizontalCenter: parent.horizontalCenter
            // anchors.topMargin: 30
            // anchors.bottomMargin: 30

            Layout.alignment: Qt.AlignCenter
            // Layout.preferredWidth: parent.width
            // Layout.preferredHeight: 40

            validator: IntValidator {bottom: 0; top: 11000;}
        }

        Button {
            id: calibrate_button
            style: touch_style

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
                pressure_sensor.reading.altitude = 1500.1; // altitude_text_field.text;w
                // pressure_sensor.altitude = 1500.1; // altitude_text_field.text;
            }
        }

        Component {
            id: touch_style
            ButtonStyle {
                panel: Item {
                    implicitHeight: 50
                    implicitWidth: 320
                    BorderImage {
                        anchors.fill: parent
                        antialiasing: true
                        border.bottom: 8
                        border.top: 8
                        border.left: 8
                        border.right: 8
                        anchors.margins: control.pressed ? -4 : 0
                        source: control.pressed ? "../images/button_pressed.png" : "../images/button_default.png"
                        Text {
                            text: control.text
                            anchors.centerIn: parent
                            color: "white"
                            font.pixelSize: 23
                            renderType: Text.NativeRendering
                        }
                    }
                }
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
                color: "white"
                text: "Pressure"
            }
            Text {
                color: "white"
                id: pressure_label
            }

            Text {
                color: "white"
                text: "Altitude"
            }
            Text {
                color: "white"
                id: altitude_label
            }
        }
    }
}
