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

// réchaud: stove, caping stove, portable gaz cooker

Widgets.Page {
    id: fuel_gauge_pane

    // property int font_size: Style.font_size.base

    ListModel {
	id: fuel_model

	ListElement {
            name: qsTr('CV 470 Plus')
	    total_weight: 630 // measured
	    net_weight: 450 // specified
	    // package_weight: 180 // 630 - 450 = 180
	    url: 'https://www.campingaz.com/FR/p-27453-cartouche-cv-470-plus.aspx'
	    content: 'Butane 80 % / Propane 20 %'
	    min_temperature: -5 // °C
	    diameter: 110 // mm
	    cap_weight: 115 // g TO BE COMFIRMED
	}

	ListElement {
            name: qsTr('CV 300 Plus')
	    total_weight: 365 // to be verified (358 g ?)
	    net_weight: 240 // specified
	    // package_weight: 150 // 360 - 240 = 120
	    url: 'ttps://www.campingaz.com/FR/p-27452-cartouche-cv-300-plus.aspx'
	    content: 'Butane 80 % / Propane 20 %'
	    min_temperature: -5 // °C
	    diameter: 90 // mm
	    cap_weight: 50 // g TO BE COMFIRMED
	}

	ListElement {
            name: qsTr('MSR IsoPro (227g net)')
	    total_weight: 374 // specified
	    net_weight: 227 // specified
	    url: 'https://www.msrgear.com/fr/stoves/msr-isopro'
	    content: 'IsoButane 80 % / Propane 20 %'
	    min_temperature: -5 // °C // to be verified
	    diameter: 110 // mm
	    cap_weight: 125 // g TO BE COMFIRMED
	}
    }

    property var current_fuel: null

    function fuel_area(fuel) {
	return Math.PI * current_fuel.diameter * current_fuel.diameter / 4
    }

    function compute_capacity() {
	var package_weight = current_fuel.total_weight - current_fuel.net_weight
	var weight = 0
	if (immersion_depth_text_field.text) {
	    // 1L = 10 x 10 x 10 cm = 1e6 mm^3 = 1 Kg = 1000 g
	    // 1000 mm^3 = 1g
	    // fuel weight = displaced - cap  water weight
	    var depth = Number.fromLocaleString(immersion_depth_text_field.text)
	    weight = fuel_area(current_fuel) * depth * 1e-3 - current_fuel.cap_weight
	    // warning_message.visible = true
	} else if (weight_text_field.text) {
	    weight = Number.fromLocaleString(weight_text_field.text)
	    // warning_message.visible = false
	}
	weight = Math.min(weight, current_fuel.total_weight)
	var capacity = Math.max((weight - package_weight) / current_fuel.net_weight, 0)
	capacity_label.text = Number(Math.round(100 * capacity)).toLocaleString() + ' %'
    }

    function compute_immersion_depth(capacity) {
	var weight = current_fuel.total_weight - (100 - capacity) / 100 * current_fuel.net_weight
	return (weight + current_fuel.cap_weight) / (fuel_area(current_fuel) * 1e-3)
    }

    Column {
	anchors.fill: parent
	spacing: Style.spacing.base_horizontal // 15 ?

	ComboBox {
	    id: combo_box
	    width: parent.width
	    model: fuel_model
	    textRole: 'name'
	    onCurrentIndexChanged: {
		current_fuel = fuel_model.get(currentIndex)
		console.info('onCurrentIndexChanged ' + currentIndex + ' ' + current_fuel)
		total_weight_label.text = Number(current_fuel.total_weight).toLocaleString() + ' g'
		net_weight_label.text = Number(current_fuel.net_weight).toLocaleString() + ' g'
		content_label.text = current_fuel.content
		min_temperature_label.text = Number(current_fuel.min_temperature).toLocaleString() + ' °C'
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
                text: qsTr('Total weight')
            }
            Label {
		id: total_weight_label
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: ''
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: qsTr('Net weight')
            }
            Label {
		id: net_weight_label
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: ''
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: qsTr('Content')
            }
            Label {
		id: content_label
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: ''
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: qsTr('Temperature Min')
            }
            Label {
		id: min_temperature_label
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: ''
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: qsTr('Actual Weight')
            }
	    TextField {
                id: weight_text_field
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                placeholderText: 'enter weight [g]'
                inputMethodHints: Qt.ImhDigitsOnly
                validator: IntValidator {bottom: 0; top: 1000;}
		onTextEdited: {
		    capacity_label.text = ''
		    immersion_depth_text_field.text = ''
		}
		onAccepted: compute_capacity()
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: qsTr('Immersion Depth')
            }
	    TextField {
                id: immersion_depth_text_field
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                placeholderText: 'or enter depth [mm]' // immersion
                inputMethodHints: Qt.ImhDigitsOnly
                validator: IntValidator {bottom: 0; top: 1000;}
		onTextEdited: {
		    capacity_label.text = ''
		    weight_text_field.text = ''
		}
		onAccepted: compute_capacity()
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: qsTr('Capacity')
            }
            Label {
		id: capacity_label
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                // font.pointSize: font_size
                text: ''
            }
	}

        Label {
	    id: warning_message
	    anchors.horizontalCenter: parent.horizontalCenter
            text: 'Warning: immersion computation is not yet accurate'
	    visible: true // false
        }

	Item {
	    // Fixme: spacer
	    width: parent.width
	    height: 20
	}

	Label {
	    anchors.horizontalCenter: parent.horizontalCenter
	    text: 'Immersion Gauge'
	}
	Repeater {
	    model: [0, 20, 40, 60, 80, 100]
	    Row {
		anchors.horizontalCenter: parent.horizontalCenter
		width: parent.width / 2
		Label {
		    width: parent.width / 2
		    text: Number(modelData).toLocaleString() + ' %'
		}
		Label {
		    width: parent.width / 2
		    text: Number(Math.round(compute_immersion_depth(modelData))).toLocaleString() + ' mm'
		}
	    }
	}
    }
}
