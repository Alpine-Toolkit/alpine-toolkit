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

import QtQml 2.2
import QtQuick 2.6

import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

import QtGraphicalEffects 1.0

import Constants 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: torch_pane

    Column {
        id: content
        anchors.fill: parent
        anchors.topMargin: 50
        spacing: Style.spacing.huge

        ToolButton {
            id: torch_switch
            anchors.horizontalCenter: parent.horizontalCenter
            checkable: true
            width: content.width / 3
            height: width

            contentItem: Item {
		width: torch_switch.size
		height: torch_switch.width

		Image {
		    id: light_bulb_icon
		    source: 'qrc:/icons/light-bulb-white.svg'
		    sourceSize: Qt.size(parent.width, parent.height)
		    visible: false
		}

		// Fixme: don't work with black qtgraphicaleffects/src/effects/shaders/coloroverlay.frag
		ColorOverlay {
		    anchors.fill: light_bulb_icon
		    source: light_bulb_icon
		    color: torch_switch.checked ? Material.color(Material.Green) : 'black' // '#2bc82b'
		}
            }

            onCheckedChanged : platform_abstraction.torch = checked
        }
    }
}
