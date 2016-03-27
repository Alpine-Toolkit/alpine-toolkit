import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import Qt.labs.controls 1.0

import QtMultimedia 5.5

Pane {
    id: torch_pane

    // Torch {
    //     power: torch_slider.value * 100
    //     enabled: torch_switch.checked
    //     onEnabledChanged: {
    //         console.info("Torch " + enabled + " " + power)
    //     }
    // }

    Column {
        width: parent.width
        anchors.top: parent.top
        anchors.topMargin: 50
        spacing: 30

        Switch {
            id: torch_switch
            anchors.horizontalCenter: parent.horizontalCenter
            // text: qsTr("Torch")
            onCheckedChanged : {
                if (on_android) {
                    android_activity.torch = checked
                }
            }
        }

        // Label {
        //     // anchors.topMargin: 50
        //     anchors.horizontalCenter: parent.horizontalCenter
        //     text: qsTr("Power")
        // }

        // Slider {
        //     id: torch_slider
        //     // anchors.topMargin: 10
        //     anchors.horizontalCenter: parent.horizontalCenter
        //     value: 1.
        // }
    }
}
