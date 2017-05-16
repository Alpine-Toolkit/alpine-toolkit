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

import QtQuick 2.6

import QtQuick.Controls 2.0

import "qrc:/C2cFilter" as C2cFilter

C2cFilter.Filter {
    property var values: null

    function longest_value() {
	var longest_string = '';
	values.forEach(function(string) {
	    if (string.length > longest_string.length)
		longest_string = string;
	});
	// console.info('longest_value ' + longest_string);
	return longest_string;
    }

    function get_value(index) {
	// console.info('get_value', index);
	return values[Math.round(index)];
    }

    function get_state() {
	var min = slider.first.value;
	var max = slider.second.value;
	if (min != slider.from || max != slider.to)
	    return { min_index: min, max_index: max, min: get_value(min), max: get_value(max) };
	else
	    return null;
    }

    function set_state(state) {
	slider.first.value = state.min_index;
	slider.second.value = state.max_index;
    }

    Row {
	anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width

	TextMetrics {
	    id: label_metrics
	    text: longest_value()
	}

	Text {
	    id: min_label
	    anchors.verticalCenter: parent.verticalCenter
	    text: get_value(slider.first.value)
	    width: label_metrics.width
	}

	RangeSlider {
	    id: slider
	    anchors.verticalCenter: parent.verticalCenter
	    width: parent.width - min_label.width - max_label.width
	    from: 0
	    to: values.length -1
	    first.value: 0
	    second.value: values.length -1
	    stepSize: 1
	    snapMode: Slider.SnapAlways
	}

	Text {
	    id: max_label
	    anchors.verticalCenter: parent.verticalCenter
	    text: get_value(slider.second.value)
	    width: label_metrics.width
	}
    }
}
