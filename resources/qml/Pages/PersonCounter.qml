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
    id: person_counter_pane

    property int count : 0
    property int last_count : 0

    function reset_count() {
        last_count = count;
        count = 0;
    }

    function update_count(value) {
        last_count = count;
        count += value;
    }

    function undo_count() {
        count = last_count;
    }

  Component {
      id: person_image

      Image {
          fillMode: Image.Pad
          horizontalAlignment: Image.AlignHCenter
          verticalAlignment: Image.AlignVCenter
          source: 'qrc:/icons/person-black.png'
      }
  }

    ToolButton {
        id: clear_button
        anchors.left: parent.left
        contentItem: Image {
	    fillMode: Image.Pad
	    horizontalAlignment: Image.AlignHCenter
	    verticalAlignment: Image.AlignVCenter
	    source: 'qrc:/icons/clear-black.png'
        }
        onClicked: reset_count()
    }

    ToolButton {
        id: reset_button
        anchors.right: parent.right
        contentItem: Image {
	    fillMode: Image.Pad
	    horizontalAlignment: Image.AlignHCenter
	    verticalAlignment: Image.AlignVCenter
	    source: 'qrc:/icons/undo-black.png'
        }
        onClicked: undo_count()
    }

    Text {
        id: counter_text
        anchors.top: reset_button.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        Layout.fillWidth: true
        font.pointSize: Style.font_size.huge
        text: Number(count).toLocaleString()
    }

    Column {
        anchors.top: counter_text.bottom
        anchors.topMargin: 50
        width: parent.width
        spacing: Style.spacing.huge

        // Hack to fix touch box
	ToolButton {
            anchors.horizontalCenter: parent.horizontalCenter
            contentItem: Loader {
                sourceComponent: person_image
            }
            onClicked: update_count(1)
        }

        Repeater {
            model: [2, 3, 4, 5]
	    ToolButton {
                anchors.horizontalCenter: parent.horizontalCenter
                property int value: modelData
                contentItem: Row {
                    spacing: Style.spacing.base
                    Repeater {
                        model: value
                        delegate: person_image
                    }
                }
                onClicked: update_count(value)
            }
        }
    }
}
