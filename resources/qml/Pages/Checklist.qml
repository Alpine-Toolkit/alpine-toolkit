/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

import QtQml 2.2
import QtQuick 2.6

import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

import Constants 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: checklist_pane

    ListModel {
        id: checklist_model

        ListElement {
            name: 'Piolet'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Crampon'
        }
        ListElement {
            name: 'Fin'
        }
    }

    // Column {
    //     anchors.fill: parent
    //     spacing: Style.spacing.small

    ToolButton {
        id: add_item_button
        anchors.right: parent.right
        anchors.top: parent.top
        contentItem: Image {
            fillMode: Image.Pad
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            source: 'qrc:/icons/add-black.png'
        }
        onClicked: add_item_popup.open()
    }

    ListView {
        id: list_view
        anchors.top: add_item_button.bottom
        height: checklist_pane.height - add_item_button.height
        width: parent.width
        model: checklist_model
        spacing: Style.spacing.small
        delegate: Button {
            width: parent.width
            checkable: true
            background: Rectangle {
                color: checked ? 'green' : 'red';
            }
            font.pixelSize: 12
            text: name
            onClicked: {
                console.log('clicked on ' + name)
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
            spacing: Style.spacing.small

            Label {
                font.pointSize: Style.font_size.huge
                font.bold: true
                text: qsTr('Add Item')
            }

            TextField {
                id: item_name_text_field
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: Style.font_size.huge
                placeholderText: 'enter name'
            }

            Row {
                spacing: Style.spacing.small
                anchors.right: parent.right

                Button {
                    text: 'Cancel'
                    onClicked: calibrate_popup.close()
                    // label.color: '#42a5f5ff'
                    background: null
                }
                Button {
                    text: 'Ok'
                    onClicked: {
                        if (item_name_text_field.text) {
                            console.info('define item name', item_name_text_field.text);
                        }
                        add_item_popup.close()
                    }
                    background: null
                }
            }
        }
    }
}
