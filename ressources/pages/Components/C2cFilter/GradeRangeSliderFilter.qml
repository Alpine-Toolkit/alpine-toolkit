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
