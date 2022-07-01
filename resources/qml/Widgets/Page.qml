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

import QtQuick.Controls 2.1

import Constants 1.0

Pane {
    // To enable a settings dialog define a Popup item with a "settings_dialog" id
    // Widgets.Popup {
    //     id: settings_dialog
    // }

    function has_settings_dialog() {
        return typeof settings_dialog !== 'undefined'
    }

    function open_settings_dialog() {
        if (has_settings_dialog())
            settings_dialog.open()
    }
}
