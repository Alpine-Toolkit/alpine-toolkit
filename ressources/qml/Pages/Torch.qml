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
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

import QtMultimedia 5.5

Pane {
    id: torch_pane

    Column {
        anchors.fill: parent
        anchors.topMargin: 50
        spacing: 30

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 20
            text: qsTr("Torch Switch")
        }

        Switch {
            id: torch_switch
            anchors.horizontalCenter: parent.horizontalCenter
            // text: qsTr("Torch")
            onCheckedChanged : {
                if (on_android) {
                    android_activity.torch = checked
                }
            }
        }
    }
}
