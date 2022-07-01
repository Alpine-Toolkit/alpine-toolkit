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

import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

import QtSensors 5.1

import Constants 1.0
import Widgets 1.0 as Widgets

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
                    var page = {source: 'qrc:/qml/Pages/Refuge.qml'}
                    var properties = {'model': list_view.model[model.index]}
                    push_page(page, properties)
                }
            }

            section.property: 'first_letter'
            // FirstLetter considers diacritic as different letters
            section.criteria: ViewSection.FullString
            section.delegate: section_heading
        }
    }

    function search() {
        refuge_schema_manager.filter_refuge_list(search_textfield.text)
    }
}
