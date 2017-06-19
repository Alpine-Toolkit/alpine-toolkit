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
        font.pointSize: 20
        text: Number(count).toLocaleString()
    }

    Column {
        anchors.top: counter_text.bottom
        anchors.topMargin: 50
        width: parent.width
        spacing: 30

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
                    spacing: 10
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
