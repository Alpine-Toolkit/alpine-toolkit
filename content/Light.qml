import QtQml 2.2
import QtQuick 2.6

import QtSensors 5.1

// import QtQuick.Controls 1.2
// import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1

import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0

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

    LightSensor {
        id: light_sensor
        active: true

        onReadingChanged: {
            var illuminance = light_sensor.reading.illuminance;
            illuminance_label.text = Number(illuminance).toLocaleString() + " lux";
        }
    }

    ColumnLayout {
        width: parent.width
        anchors.topMargin: 30
        spacing: 30

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
                text: "Illuminance"
            }
            Text {
                color: "white"
                id: illuminance_label
            }
        }
    }
}
