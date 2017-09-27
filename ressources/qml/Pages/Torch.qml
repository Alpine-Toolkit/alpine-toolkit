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
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

import QtGraphicalEffects 1.0

import Constants 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: torch_pane

    property int period: 100 // ms

    Component.onCompleted: {
    }

    function update_toch() {
        if (dimmer_checkbox.checked) {
            if (torch_switch.checked)
                platform_abstraction.start_lamp_dimmer(period, dimmer_slider.value)
            else
                platform_abstraction.stop_lamp_dimmer()
        } else
            platform_abstraction.torch = torch_switch.checked
    }

    Column {
        id: content
        anchors.fill: parent
        anchors.topMargin: 50
        spacing: Style.spacing.huge

        ToolButton {
            id: torch_switch
            anchors.horizontalCenter: parent.horizontalCenter
            checkable: true
            width: content.width / 3
            height: width

            contentItem: Item {
		width: torch_switch.size
		height: torch_switch.width

		Image {
		    id: light_bulb_icon
		    source: 'qrc:/icons/light-bulb-white.svg'
		    sourceSize: Qt.size(parent.width, parent.height)
		    visible: false
		}

		// Fixme: don't work with black qtgraphicaleffects/src/effects/shaders/coloroverlay.frag
		ColorOverlay {
		    anchors.fill: light_bulb_icon
		    source: light_bulb_icon
		    color: torch_switch.checked ? Material.color(Material.Green) : 'black' // '#2bc82b'
		}
            }

            onCheckedChanged: update_toch()
        }

        GroupBox {
            id: dimmer_group_box
            width: content.width * .8
            anchors.horizontalCenter: parent.horizontalCenter
            // title: qsTr("Dimmer")

            ColumnLayout {
                width: parent.width

                CheckBox {
                    id: dimmer_checkbox
                    text: qsTr("Dimmer")
                    checked: false
                    onCheckedChanged: update_toch()
                }

	        Slider {
                    id: dimmer_slider
                    Layout.alignment: Qt.AlignCenter
                    Layout.fillWidth: true
                    enabled: dimmer_checkbox.checked

	            from: 0
	            to: 100
		    stepSize: 5
		    snapMode: Slider.SnapAlways
	            value: 100

                    onValueChanged: update_toch()
	        }
            }
        }
    }
}
