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
