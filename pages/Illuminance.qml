import QtQml 2.2
import QtQuick 2.6

import QtQuick.Layouts 1.1
import Qt.labs.controls 1.0

import QtSensors 5.1

Pane {
    id: illuminance_pane

    LightSensor {
        id: light_sensor
        active: true

        onReadingChanged: {
            var illuminance = light_sensor.reading.illuminance;
            illuminance_label.text = Number(illuminance).toLocaleString() + " lux";
        }
    }

    ColumnLayout {
        spacing: 40
        anchors.fill: parent

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
                text: "Illuminance"
            }
            Text {
                id: illuminance_label
            }
        }
    }

}
