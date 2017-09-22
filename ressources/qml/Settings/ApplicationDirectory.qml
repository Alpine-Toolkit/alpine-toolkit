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
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

import Constants 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: settings_pane

    Column {
        id: content
        anchors.fill: parent
        spacing: Style.spacing.huge

        Column {
            width: parent.width
            spacing: Style.spacing.base
            Row {
                spacing: Style.spacing.base
                Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: 'qrc:/icons/folder-black.png'
                }
                Label {
                    text: qsTr('Current directory')
                    font.pixelSize: 18
                }
            }
            Label {
                width: parent.width
                text: '/foo/bar/foo/bar/foo/bar/foo/bar/foo/bar/foo/bar/foo/bar/foo/bar/foo/bar/foo/bar/foo/bar/foo/bar/foo/bar'
                wrapMode: Text.WrapAnywhere
            }
        }

        Column {
            width: parent.width
            spacing: Style.spacing.base
            Row {
                spacing: Style.spacing.base
                Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: 'qrc:/icons/sd-card-black.png'
                }
                Label {
                    text: qsTr('Directory is on internal storage')
                    font.pixelSize: 18
                }
            }
            Label {
                width: parent.width
                text: qsTr('You can move the directory to the external storage to save memory.')
                wrapMode: Text.WordWrap
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr('Move to external storage')
                font.pixelSize: 18
            }
        }

        Column {
            width: parent.width
            spacing: Style.spacing.base
            Row {
                spacing: Style.spacing.base
                Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: 'qrc:/icons/security-black.png'
                }
                Label {
                    text: qsTr('Directory is public')
                    font.pixelSize: 18
                }
            }
            Label {
                width: parent.width
                text: qsTr('Data will remain if you uninstall the application.')
                wrapMode: Text.WordWrap
            }
            Button {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr('Move to private storage')
                font.pixelSize: 18
            }
        }
    }
}
