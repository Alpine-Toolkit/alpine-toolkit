import QtQml 2.2
import QtQuick 2.6

import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

// import QtQuick.Controls 1.2
// import QtQuick.Controls.Styles 1.1
import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0

Item {
    width: parent.width
    height: parent.height

    property real progress: 0

    SequentialAnimation on progress {
        loops: Animation.Infinite
        running: true
        NumberAnimation {
            from: 0
            to: 1
            duration: 3000
        }
        NumberAnimation {
            from: 1
            to: 0
            duration: 3000
        }
    }

    ColumnLayout {
        width: parent.width
        anchors.topMargin: 30
        spacing: 10

        Rectangle {
            width: parent.width
            height: 200
            Layout.alignment: Qt.AlignCenter
            color: "#000000"

            TextInput {
                anchors.fill: parent
                verticalAlignment : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
                color: "#ffffff"
                font.pointSize: 30
                text: "1234"
            }
        }

        Rectangle {
            width: parent.width
            height: 200
            Layout.alignment: Qt.AlignCenter
            color: "#ffffff"

            TextInput {
                anchors.fill: parent
                verticalAlignment : Text.AlignVCenter
                horizontalAlignment : Text.AlignHCenter
                color: "#000000"
                font.pointSize: 30
                text: "1234"
            }
        }

        Dialog {
            id: dialog
            visible: false
            // title: "Dialog"

            // contentItem: Rectangle {
            //     color: "white"
            //     implicitWidth: 400
            //     implicitHeight: 100

            //     Text {
            //         text: "Hello!"
            //         color: "black"
            //         anchors.centerIn: parent
            //     }
            // }

            // Style
            standardButtons: StandardButton.Save | StandardButton.Cancel

            // onAccepted: console.log("Saving the date " + calendar.selectedDate.toLocaleDateString())

            // Calendar {
            //     id: calendar
            //     anchors.centerIn: parent // still overfit
            //     onDoubleClicked: dialog.click(StandardButton.Save)
            // }
        }

        Button {
            id: button
            // style: touch_style

            Layout.alignment: Qt.AlignCenter
            // Layout.preferredWidth: parent.width
            // Layout.preferredHeight: 50

            // font.pointSize: 30
            text: "Press"
            onClicked: {
                dialog.visible = true
            }
        }

        // Component {
        //     id: touch_style
        //     ButtonStyle {
        //         panel: Item {
        //             implicitHeight: 80
        //             implicitWidth: 320
        //             BorderImage {
        //                 anchors.fill: parent
        //                 antialiasing: true
        //                 border.bottom: 8
        //                 border.top: 8
        //                 border.left: 8
        //                 border.right: 8
        //                 anchors.margins: control.pressed ? -4 : 0
        //                 source: control.pressed ? "../images/button_pressed.png" : "../images/button_default.png"
        //                 Text {
        //                     text: control.text
        //                     anchors.centerIn: parent
        //                     color: "white"
        //                     font.pixelSize: 23
        //                     renderType: Text.NativeRendering
        //                 }
        //             }
        //         }
        //     }
        // }
    }
}
