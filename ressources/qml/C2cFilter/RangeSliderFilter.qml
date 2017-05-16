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
    property string unit: 'm'
    property var min: 0
    property var max: 1
    property var step_size: 1

    function get_state() {
	var min = slider.first.value;
	var max = slider.second.value;
	if (min != slider.from || max != slider.to)
	    return { min: min, max: max };
	else
	    return null;
    }

    function set_state(state) {
	slider.first.value = state.min;
	slider.second.value = state.max;
    }

    function format_value(value) {
	return Number(value).toLocaleString(Qt.locale("fr_FR"), 'f', 0)
    }

    function format_min(value) {
	return format_value(value)
    }

    function format_max(value) {
	return format_value(value) + ' ' + unit
    }

    Row {
	anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width

	TextMetrics {
	    id: min_label_metrics
	    text: format_min(max)
	}

	TextMetrics {
	    id: max_label_metrics
	    text: format_max(max)
	}

	Text {
	    id: min_label
	    anchors.verticalCenter: parent.verticalCenter
	    text: format_min(slider.first.value)
	    width: min_label_metrics.width
	}

	RangeSlider {
	    id: slider
	    anchors.verticalCenter: parent.verticalCenter
	    width: parent.width - min_label.width - max_label.width
	    from: min
	    to: max
	    first.value: min
	    second.value: max
	    stepSize: step_size
	    snapMode: Slider.SnapAlways
	}

	Text {
	    id: max_label
	    anchors.verticalCenter: parent.verticalCenter
	    text: format_max(slider.second.value)
	    width: max_label_metrics.width
	}
    }
}
