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
