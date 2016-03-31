import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import Qt.labs.controls 1.0

Pane {
    id: ui_test_pane

    Rectangle {
        x: 100
        y: 100
        color: "black"
        width: 100
        height: 100
    }

    Label {
        x: 100
        y: 300
        font.pointSize: 20
        text: "Axm1"
    }

    Label {
        x: 100
        y: 450
        font.pixelSize: 40
        text: "Axm2"
    }
}
