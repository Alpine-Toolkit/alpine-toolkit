import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

Pane {
    id: checklist_pane

    ListModel {
        id: checklist_model

        ListElement {
            name: "Piolet"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Crampon"
        }
        ListElement {
            name: "Fin"
        }
    }

    // Column {
    //     anchors.fill: parent
    //     spacing: 5

    ToolButton {
        id: add_item_button
        anchors.right: parent.right
        anchors.top: parent.top
        contentItem: Image {
            fillMode: Image.Pad
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            source: "qrc:/icons/add-black.png"
        }
        onClicked: add_item_popup.open()
    }

    ListView {
        id: list_view
        anchors.top: add_item_button.bottom
        height: checklist_pane.height - add_item_button.height
        width: parent.width
        model: checklist_model
        spacing: 5
        delegate: Button {
            width: parent.width
            checkable: true
            background: Rectangle {
                color: checked ? "green" : "red";
            }
            font.pixelSize: 12
            text: name
            onClicked: {
                console.log("clicked on " + name)
            }
        }
    }

    // }

    Popup {
        id: add_item_popup
        modal: true
        focus: true
        // Fixme: not centered
        x: (application_window.width - width) / 2
        y: application_window.height / 6
        width: application_window.width * .9
        contentHeight: column.height

        Column {
            id: column
            width: parent.width
            spacing: 5

            Label {
                font.pointSize: 20
                font.bold: true
                text: qsTr("Add Item")
            }

            TextField {
                id: item_name_text_field
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 32
                placeholderText: "enter name"
            }

            Row {
                spacing: 5
                anchors.right: parent.right

                Button {
                    text: "Cancel"
                    onClicked: calibrate_popup.close()
                    // label.color: "#42a5f5ff"
                    background: null
                }
                Button {
                    text: "Ok"
                    onClicked: {
                        if (item_name_text_field.text) {
                            console.info("define item name", item_name_text_field.text);
                        }
                        add_item_popup.close()
                    }
                    background: null
                }
            }
        }
    }
}
