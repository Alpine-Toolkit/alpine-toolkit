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

// réchaud: stove, caping stove, portable gaz cooker

Widgets.Page {
    id: fuel_gauge_pane

    // property int font_size: 12

    ListModel {
	id: fuel_model

	ListElement {
            name: qsTr('CV 470 Plus')
	    total_weight: 630 // measured
	    net_weight: 450 // specified
	    // package_weight: 180 // 630 - 450 = 180
	    url: "https://www.campingaz.com/FR/p-27453-cartouche-cv-470-plus.aspx"
	    content: "Butane 80 % / Propane 20 %"
	    min_temperature: -5 // °C
	}

	ListElement {
            name: qsTr('CV 300 Plus')
	    total_weight: 365 // to be verified (358 g ?)
	    net_weight: 240 // specified
	    // package_weight: 150 // 360 - 240 = 120
	    url: "ttps://www.campingaz.com/FR/p-27452-cartouche-cv-300-plus.aspx"
	    content: "Butane 80 % / Propane 20 %"
	    min_temperature: -5 // °C
	}

	ListElement {
            name: qsTr('MSR IsoPro (227g net)')
	    total_weight: 374 // specified
	    net_weight: 227 // specified
	    url: "https://www.msrgear.com/fr/stoves/msr-isopro"
	    content: "IsoButane 80 % / Propane 20 %"
	    min_temperature: -5 // °C // to be verified
	}
    }

    property var current_fuel: null

    function compute_capacity() {
	if (weight_text_field.text) {
	    var weight = Number.fromLocaleString(weight_text_field.text)
	    var package_weight = current_fuel.total_weight - current_fuel.net_weight
	    var capacity = Math.max((weight - package_weight) / current_fuel.net_weight, 0)
	    capacity_label.text = Number(Math.round(100 * capacity)).toLocaleString() + " %"
	}
    }

    Column {
	anchors.fill: parent
	spacing: 15

	ComboBox {
	    id: combo_box
	    width: parent.width
	    model: fuel_model
	    textRole: "name"
	    onCurrentIndexChanged: {
		current_fuel = fuel_model.get(currentIndex)
		console.info("onCurrentIndexChanged " + currentIndex + " " + current_fuel)
		total_weight_label.text = Number(current_fuel.total_weight).toLocaleString() + " g"
		net_weight_label.text = Number(current_fuel.net_weight).toLocaleString() + " g"
		content_label.text = current_fuel.content
		min_temperature_label.text = Number(current_fuel.min_temperature).toLocaleString() + " °C"
		compute_capacity()
	    }
	}

	GridLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 2
            columnSpacing : 10
            rowSpacing : 5

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: qsTr("Total weight")
            }
            Label {
		id: total_weight_label
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: ""
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: qsTr("Net weight")
            }
            Label {
		id: net_weight_label
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: ""
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: qsTr("Content")
            }
            Label {
		id: content_label
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: ""
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: qsTr("Temperature Min")
            }
            Label {
		id: min_temperature_label
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: ""
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: qsTr("Actual Weight")
            }
	    TextField {
                id: weight_text_field
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                placeholderText: "enter weight [g]"
                inputMethodHints: Qt.ImhDigitsOnly
                validator: IntValidator {bottom: 0; top: 1000;}
		onTextEdited: capacity_label.text = ""
		onAccepted: compute_capacity()
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: qsTr("Immersion Depth")
            }
	    TextField {
                id: immersion_depth_text_field
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                placeholderText: "or enter depth [mm]" // immersion
                inputMethodHints: Qt.ImhDigitsOnly
                validator: IntValidator {bottom: 0; top: 1000;}
		onAccepted: {
		    capacity_label.text = "not implemented"
		}
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: qsTr("Capacity")
            }
            Label {
		id: capacity_label
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: ""
            }
        }
    }
}
