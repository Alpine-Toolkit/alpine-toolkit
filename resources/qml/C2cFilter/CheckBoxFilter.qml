/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

import QtQuick 2.6

import QtQuick.Controls 2.0

import Constants 1.0
import C2cFilter 1.0 as C2cFilter

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
