import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

import QtSensors 5.1

Pane {
    id: refug_directory_pane

    property var model: null

    Component.onCompleted: {
        console.info("Refuge Model:", model.name);
    }

    Column {
        width: parent.width

        Label {
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            topPadding: 20
            bottomPadding: 30
            font.pointSize: 32
            font.bold: true
            text: model.name
            wrapMode: Text.WordWrap
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            bottomPadding: 10
            font.pointSize: 12
            font.bold: true
            text: model.altitude + " m"
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            bottomPadding: 10
            font.pointSize: 12
            font.bold: true
            text: model.region
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            bottomPadding: 10
            font.pointSize: 12
            font.bold: true
            text: model.guardian
        }

        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            // bottomPadding: 10
            Label {
                Layout.alignment: Qt.AlignVCenter
                font.pointSize: 12
                font.bold: true
                text: model.phone
            }
            ToolButton {
                Layout.alignment: Qt.AlignVCenter
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/icons/call-black.png"
                }
                onClicked: {
                    if (on_android) {
                        android_activity.issue_dial(model.phone);
                    }
                }
            }
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            bottomPadding: 10
            font.pointSize: 12
            font.bold: true
            text: Number(model.coordinate.latitude).toLocaleString(Qt.locale(), "f", 6) + "\n" +
                Number(model.coordinate.longitude).toLocaleString(Qt.locale(), "f", 6)
        }

        Label {
            bottomPadding: 10
            width: parent.width
            font.pointSize: 12
            wrapMode: Text.WordWrap
            text: model.description
        }
    }
}
