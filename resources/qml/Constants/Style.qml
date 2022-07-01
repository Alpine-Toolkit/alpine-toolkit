/***************************************************************************************************
 *
 * This file is part of the Alpine Toolkit software.
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 * SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

// cf. http://wiki.qt.io/Qml_Styling

pragma Singleton
import QtQuick 2.6

QtObject {

    property QtObject font_size: QtObject {
	property int tiny:   8
	property int small: 10
	property int base:  12
	property int large: 18
	property int huge:  20
        property int very_huge:  24
    }

    property QtObject spacing: QtObject {
	property int xs:     1
	property int small:  5
	property int base:  10
	property int large: 20
	property int huge:  30

	property int xs_horizontal:     1
	property int small_horizontal:  5
	property int base_horizontal:  10
	property int large_horizontal: 20

	property int xs_vertical:       1
	property int small_vertical:    5
	property int base_vertical:    10
	property int large_vertical:   20
    }

}
