import QtQuick 2.6

// import QtQuick.Controls 1.2
import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0

import "content"

ApplicationWindow {
    visible: true
    width: 800 // Fixme: mobile ?
    height: 1280

    // Background
    Rectangle {
        // color: "#212126"
        color: "#555555"
        anchors.fill: parent
    }

    // toolBar: BorderImage {
    header: BorderImage {
        width: parent.width
        height: 150
        border.bottom: 8
        source: "images/toolbar.png" // blue line at bottom

        Rectangle {
            id: back_button
            opacity: stack_view.depth > 1 ? 1 : 0
            width: opacity ? 60 : 0
            height: 60
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            radius: 4
            color: back_button_mouse_area.pressed ? "#222" : "transparent"
            antialiasing: true
            Behavior on opacity { NumberAnimation{} }
            Image {
                anchors.verticalCenter: parent.verticalCenter
                source: "images/navigation_previous_item.png"
            }
            MouseArea {
                id: back_button_mouse_area
                anchors.fill: parent
                anchors.margins: -10
                onClicked: stack_view.pop()
            }
        }

        Text {
            font.pointSize: 32
            Behavior on x { NumberAnimation{ easing.type: Easing.OutCubic} }
            x: back_button.x + back_button.width + 20
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            text: "QtCarto"
        }
    }

    // Pages
    ListModel {
        id: page_model
        ListElement {
            title: "Altimeter"
            page: "content/Altimeter.qml"
        }
        ListElement {
            title: "Inclination"
            page: "content/Inclination.qml"
        }
        ListElement {
            title: "Light"
            page: "content/Light.qml"
        }
        ListElement {
            title: "GPS"
            page: "content/Gps.qml"
        }
        ListElement {
            title: "Test"
            page: "content/Test.qml"
        }
    }

    StackView {
        id: stack_view
        anchors.fill: parent
        // Implements back key navigation
        focus: true
        Keys.onReleased: if (event.key === Qt.Key_Back && stack_view.depth > 1) {
                             stack_view.pop();
                             event.accepted = true;
                         }

        initialItem: Item {
            width: parent.width
            height: parent.height
            ListView {
                model: page_model
                anchors.fill: parent
                delegate: AndroidDelegate {
                    text: title
                    // Fixme: page title
                    onClicked: stack_view.push(Qt.resolvedUrl(page))
                }
            }
        }
    }
}
