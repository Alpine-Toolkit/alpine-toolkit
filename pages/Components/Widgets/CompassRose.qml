import QtQuick 2.6

import QtQuick.Controls 2.0

import "qrc:/js/compass_rose.js" as CompassRosePainter

Canvas {
    id: canvas

    property int radius: 100

    width: radius
    height: radius

    antialiasing: true
    onPaint: CompassRosePainter.paint_compass_rose(canvas)

    function set_state(state) {
	CompassRosePainter.set_state(state);
	requestPaint();
    }
}
