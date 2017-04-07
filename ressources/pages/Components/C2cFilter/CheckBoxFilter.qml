import QtQuick 2.6

import QtQuick.Controls 2.0

import "qrc:/C2cFilter" as C2cFilter

C2cFilter.Filter {
    property var values: null

    function get_state() {
	var state = [];
	for (var i = 0; i < values.length; i++) {
	    if (repeater.itemAt(i).checked)
		state.push(values[i]);
	}
	return state.length ? state : null;
    }

    function set_state(state) {
	state.forEach(function (value) {
	    var index = values.indexOf(value);
	    repeater.itemAt(index).checked = true;
	});
    }

    Flow {
	anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width

	Repeater {
	    id: repeater
            model: values

	    CheckBox {
		text: modelData
	    }
	}
    }
}
