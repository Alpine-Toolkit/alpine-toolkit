import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import Qt.labs.controls 1.0

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
            anchors.horizontalCenter: parent.horizontalCenter
            topPadding: 20
            bottomPadding: 30
            font.pointSize: 32
            font.bold: true
            text: model.name
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
        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            bottomPadding: 10
            font.pointSize: 12
            font.bold: true
            text: model.phone
        }
        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            bottomPadding: 10
            font.pointSize: 12
            font.bold: true
            text: model.coordinate.latitude + " " + model.coordinate.longitude
        }
        Label {
            bottomPadding: 10
            width: parent.width
            font.pointSize: 12
            wrapMode:Text.WordWrap
            text: model.description
        }
    }
}
