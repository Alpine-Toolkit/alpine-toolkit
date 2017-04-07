import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

import QtSensors 5.1

Pane {
    id: illuminance_pane

    function format_lux(value) {
        return value + " lx";
    }

    LightSensor {
        id: light_sensor
        active: true

        onReadingChanged: {
            var illuminance = light_sensor.reading.illuminance;
            illuminance_label.text = format_lux(Number(illuminance).toLocaleString());
        }
    }

    Component.onCompleted: {
        console.info(light_sensor.identifier + "/" + light_sensor.description) // 5 // TMG399X RGB Sensor AMS, Inc. v1
        var data_rates = light_sensor.availableDataRates;
        for (var i = 0; i < data_rates.length; i += 1) {
            console.info("rate", data_rates[i]);
        }
    }

    // RBG level

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 10
        spacing: 10

        Label {
            id: illuminance_label
            Layout.alignment: Qt.AlignCenter
            font.pointSize: 32
            font.bold: true
            text: qsTr("No value")
        }

        Button {
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Help")
            onClicked: illuminance_help.open()
        }
    }

    Popup {
        id: illuminance_help
        modal: true
        focus: true
        // margins: 5 // must be centered
        x: (application_window.width - width) / 2
        y: application_window.height / 6
        width: application_window.width * .9
        contentHeight: about_column.height

        Column {
            id: about_column
            spacing: 5

            Label {
                font.pointSize: 20
                font.bold: true
                text: qsTr("Help")
            }

            Label {
                width: illuminance_help.availableWidth
                wrapMode: Label.Wrap
                font.pointSize: 18
                text: qsTr("Illuminance is a measure of the intensity of illumination on a surface.\n\nThe unit is lux and its symbol lx.\n\nOne lux is equal to one lumen (lm) per square metre.\n\nTypical illumination values are, 500 lx for an office lighting and above 10 000 lx for a full daylight.")
            }
        }
    }

}
