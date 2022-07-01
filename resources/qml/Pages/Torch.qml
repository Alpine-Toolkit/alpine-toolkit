/***************************************************************************************************
 *
 * This file is part of the Alpine Toolkit software.
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 * SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

import QtQml 2.2
import QtQuick 2.6

import QtGraphicalEffects 1.0
// import QtMultimedia 5.8
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

import Constants 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: torch_pane

    property int period: 100 // ms

    // Torch {
    //   id: torch
    //   power: 75
    //   enabled: true
    // }

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
