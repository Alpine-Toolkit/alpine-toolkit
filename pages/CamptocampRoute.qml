import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

Pane {
    id: camptocamp_route_pane

    property var route: null

    Component.onCompleted: {
        console.info("camptocamp route pan " + route)
    }

    /* ColumnLayout { */
    /*     anchors.horizontalCenter: parent.horizontalCenter */
    /*     width: parent.width */

    ToolButton {
        id: download_icon
        anchors.top: parent.top
        anchors.right: parent.right
        contentItem: Image {
            fillMode: Image.Pad
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            source: c2c_client.is_document_cached(route.id) ? "qrc:/icons/cloud-done-black.png" : "qrc:/icons/cloud-download-black.png"
        }
        // Fixme: cached / update
        onClicked: c2c_client.save_document(route.id)
    }

    Label {
        id: title
        width: parent.width
        anchors.top: download_icon.top
        anchors.horizontalCenter: parent.horizontalCenter
        font.pointSize: 32
        font.bold: true
        text: route.title("fr")
        wrapMode: Text.WordWrap
    }

    Flickable {
        id: flickable
        anchors.top: title.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: parent.height - title.height

        TextArea.flickable: TextArea {
            id: description
            font.pointSize: 12
            readOnly: true
            text: route.description("fr")
            // textFormat: TextEdit.RichText
            wrapMode: Text.WordWrap
        }

        ScrollBar.vertical: ScrollBar { }
    }
}
