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

import QtSensors 5.1

import "qrc:Widgets" as Widgets

Widgets.Page {
    id: refug_directory_pane

    property var model: null

    // Component.onCompleted: {
    //     console.info("Refuge Model:", model.name);
    // }

    Column {
        width: parent.width

        Label {
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            topPadding: 20
            bottomPadding: 30
            font.pointSize: 32
            font.bold: true
            text: model.name
            wrapMode: Text.WordWrap
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            topPadding: 20
            bottomPadding: 30
            font.pointSize: 16
            font.bold: true
            text: model.owner
            wrapMode: Text.WordWrap
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            bottomPadding: 10
            font.pointSize: 12
            font.bold: true
            text: model.altitude + " m"
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            bottomPadding: 10
            font.pointSize: 12
            font.bold: true
            text: model.region
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            bottomPadding: 10
            font.pointSize: 12
            font.bold: true
            text: model.guardian
        }

        RowLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            // bottomPadding: 10
            Label {
                Layout.alignment: Qt.AlignVCenter
                font.pointSize: 12
                font.bold: true
                text: model.phone
            }
            ToolButton {
                Layout.alignment: Qt.AlignVCenter
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/icons/call-black.png"
                }
                onClicked: {
                    if (on_android) {
                        android_activity.issue_dial(model.phone);
                    }
                }
            }
        }

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            bottomPadding: 10
            font.pointSize: 12
            font.bold: true
            text: Number(model.coordinate.latitude).toLocaleString(Qt.locale(), "f", 6) + "\n" +
                Number(model.coordinate.longitude).toLocaleString(Qt.locale(), "f", 6)
        }

        Label {
            bottomPadding: 10
            width: parent.width
            font.pointSize: 12
            wrapMode: Text.WordWrap
            text: model.description
        }
    }
}
