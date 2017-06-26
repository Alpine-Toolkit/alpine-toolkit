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
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1

import QtSensors 5.1

import "qrc:Widgets" as Widgets

Widgets.Page {
    id: refuge_directory_pane

  Component {
        id: section_heading

        Rectangle {
            width: refuge_directory_pane.width
            height: childrenRect.height

            Label {
                font.bold: true
                font.pixelSize: 20
                text: section
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true

	    TextField {
                id: search_textfield
                Layout.fillWidth: true
                placeholderText: qsTr('Search')
                onTextChanged: search()
                onPressed: search()
	    }

	    ToolButton {
                id: clear_icon
                visible: search_textfield.text
                contentItem: Image {
		    fillMode: Image.Pad
		    horizontalAlignment: Image.AlignHCenter
		    verticalAlignment: Image.AlignVCenter
		    source: 'qrc:/icons/clear-black.png'
                }
                onClicked: search_textfield.clear()
	    }

	    ToolButton {
                id: gps_icon
                checkable: true
                contentItem: Image {
		    fillMode: Image.Pad
		    horizontalAlignment: Image.AlignHCenter
		    verticalAlignment: Image.AlignVCenter
		    source: gps_icon.checked ?
                        'qrc:/icons/gps-fixed-black.png' :
                        'qrc:/icons/gps-not-fixed-black.png'
                }
                // onClicked: {}
	    }
        }

        ListView {
            id: list_view
            Layout.fillHeight: true
            Layout.fillWidth: true

            model: refuge_schema_manager.refuges

            delegate: ItemDelegate {
                width: parent.width
                font.pixelSize: 12
                text: model.name
                onClicked: {
                    var properties = {'model': list_view.model[model.index]}
                    application_window.push_page('qrc:/Pages/Refuge.qml', properties)
                }
            }

            section.property: 'first_letter'
            // FirstLetter considers diacritic as different letters
            section.criteria: ViewSection.FullString
            section.delegate: section_heading
        }
    }

    // Widgets.Popup {
    //     id: settings_dialog
    // }

    function search() {
        refuge_schema_manager.filter_refuge_list(search_textfield.text)
    }
}
