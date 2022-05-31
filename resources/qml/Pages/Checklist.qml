/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine ToolKit software.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
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
