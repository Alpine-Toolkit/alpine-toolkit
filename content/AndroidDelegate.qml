import QtQuick 2.2

Item {
    id: root
    width: parent.width
    height: 100
    // anchors.topMargin: 20
    // anchors.bottomMargin: 20

    property alias text: text_item.text
    signal clicked

    // Background
    Rectangle {
        anchors.fill: parent
        color: "#11ffffff"
        visible: mouse_area.pressed
    }

    Text {
        id: text_item
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 30
        color: "white"
        font.pointSize: 32
        text: modelData
    }

    // bottom line
    Rectangle {
        height: 1
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 15
        color: "#424246"
    }

    Image {
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        source: "../images/navigation_next_item.png"
    }

    MouseArea {
        id: mouse_area
        anchors.fill: parent
        onClicked: root.clicked()
    }
}
