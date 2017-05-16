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

import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2 // Fixme

MenuItem {
    id: control

    property string image

    contentItem: Row {
        spacing: 10

        leftPadding: control.checkable && !control.mirrored ? control.indicator.width + control.spacing : 0
        rightPadding: control.checkable && control.mirrored ? control.indicator.width + control.spacing : 0

        Image {
            height: text_item.height
            width: height
            fillMode: Image.Stretch
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            source: control.image
        }

        Text {
            id: text_item
            text: control.text
            font: control.font
            color: control.enabled ? Material.foreground : Material.hintTextColor
            // color: control.enabled ? control.Material.foreground : control.Material.hintTextColor
            elide: Text.ElideRight
            visible: control.text
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }
}
