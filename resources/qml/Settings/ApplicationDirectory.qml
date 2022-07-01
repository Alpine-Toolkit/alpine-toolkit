/***************************************************************************************************
 *
 * This file is part of the Alpine Toolkit software.
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 * SPDX-License-Identifier: GPL-3.0-only
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
