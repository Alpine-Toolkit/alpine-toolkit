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

import QtPositioning 5.5

import Qt.labs.settings 1.0

import Constants 1.0
import Local 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: map_pane

    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0
    topPadding: 0

    Widgets.MapComponent {
        id: map
        anchors.fill: parent
        focus: true
    }
}

