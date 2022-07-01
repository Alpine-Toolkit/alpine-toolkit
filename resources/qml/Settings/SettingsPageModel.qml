/***************************************************************************************************
 *
 * This file is part of the Alpine Toolkit software.
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 * SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

import QtQuick 2.6

ListModel {
    id: settings_page_model

    // Fixme: can we move attributes to page ?

    ListElement {
        group: 'main'
        title: qsTr('Application Directory')
        icon: 'qrc:/icons/sd-card-black.png'
        source: 'qrc:/qml/Settings/ApplicationDirectory.qml'
        // lock_orientation: false
    }
}
