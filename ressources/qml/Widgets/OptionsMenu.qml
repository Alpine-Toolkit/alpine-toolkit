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

// import Widgets 1.0 // Fixme: don't work
import "qrc:Widgets" as Widgets

Menu {
    id: options_menu

    property var about_dialog;

    // private
    property var has_settings: false;
    property var settings_item: null;

    // To be defined
    // function open_settings_dialog() {}

    x: parent.width - width
    transformOrigin: Menu.TopRight

    // Widgets.MenuItemIcon {
    // // MenuItem {
    //     // enabled: options_menu.has_settings
    //     // visible: options_menu.has_settings
    //     text: 'Settings'
    //      image: 'qrc:/icons/build-black.png'
    //     onTriggered: open_settings_dialog()
    // }

    Widgets.MenuItemIcon {
    // MenuItem {
        text: 'About'
        image: 'qrc:/icons/help-black.png'
        onTriggered: about_dialog.open()
    }

    Component.onCompleted: {
       var component = Qt.createComponent("qrc:Widgets/MenuItemIcon.qml")
        settings_item = component.createObject(null, {
            text: 'Settings',
            image: 'qrc:/icons/build-black.png',
        })
        settings_item.triggered.connect(open_settings_dialog)
    }

    function enable_settings(status) {
        console.info("enable_settings " + status)
        if (status != has_settings) {
            if (!status) {
                console.info("Remove settings")
                options_menu.removeItem(0)
            } else {
                console.info("Insert settings")
                options_menu.insertItem(0, settings_item)
            }
            has_settings = status
        }
    }
}
