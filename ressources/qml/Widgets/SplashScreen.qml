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

Pane {
    id: splash_screen_pane

    Image {
        anchors.centerIn: parent
        property int image_size: Math.min(parent.width, parent.height) * .9
        width: image_size
        height: image_size
        // source: 'asset:///application-icons/icon.svg'
        source: 'qrc:/application-icons/icon-transparent.svg'
        // property int image_size: Math.min(Math.min(parent.width, parent.height) * .9, 512)
        // source: 'qrc:/application-icons/icon-512.png'
    }
}
