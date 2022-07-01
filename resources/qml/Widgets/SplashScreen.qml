/***************************************************************************************************
 *
 * This file is part of the Alpine Toolkit software.
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 * SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

import QtQuick 2.6

import QtQuick.Controls 2.0

import Constants 1.0

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
