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

import "qrc:/js/compass_rose.js" as CompassRosePainter

import "qrc:/C2cFilter" as C2cFilter

C2cFilter.Filter {
    function get_state() {
	return CompassRosePainter.get_state();
    }

    function set_state(state) {
	CompassRosePainter.set_state(state);
	canvas.requestPaint();
    }

    Canvas {
	id: canvas
	anchors.horizontalCenter: parent.horizontalCenter

	property int radius: 170

	width: radius
	height: radius

	antialiasing: true
	onPaint: CompassRosePainter.paint_compass_rose(canvas)

	MouseArea {
            anchors.fill: parent
            onClicked: {
		var quadrant = CompassRosePainter.get_quadrant(mouseX, mouseY);
		if (quadrant !== null) {
		    CompassRosePainter.update_quadrant(quadrant);
		    canvas.requestPaint();
		}
	    }
	}
    }
}
