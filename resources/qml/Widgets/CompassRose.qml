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

import 'qrc:/js/compass_rose.js' as CompassRosePainter
import Constants 1.0

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
