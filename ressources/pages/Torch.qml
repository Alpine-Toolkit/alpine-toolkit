import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

import QtMultimedia 5.5

Pane {
    id: torch_pane

    Column {
        anchors.fill: parent
        anchors.topMargin: 50
        spacing: 30

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 20
            text: qsTr("Torch Switch")
        }

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
    }
}
