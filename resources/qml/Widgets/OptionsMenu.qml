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

import Constants 1.0
import Widgets 1.0 as Widgets

Menu {
    id: options_menu

    // Define the about dialog
    property QtObject about_dialog;

    // private
    property var is_settings_menu_enabled: false;
    // Overwriting binding on About_QMLTYPE_9::about_text at qrc:Widgets/About.qml:80 that was initially bound at qrc:Widgets/About.qml:36:34
    property QtObject settings_item;

    // To be defined
    // function open_settings_dialog() {}

    x: parent.width - width
    transformOrigin: Menu.TopRight

    // Widgets.MenuItemIcon {
    // // MenuItem {
    //     // enabled: options_menu.is_settings_menu_enabled
    //     // visible: options_menu.is_settings_menu_enabled
    //     text: 'Settings'
    //      image: 'qrc:/icons/build-black.png'
    //     onTriggered: open_settings_dialog()
    // }

    Widgets.MenuItemIcon {
    // MenuItem {
        text: qsTr('Gloabl Settings')
        image: 'qrc:/icons/settings-sliders-black.png'
        onTriggered: {
            var page = {source: 'qrc:/qml/Pages/Settings.qml', title: qsTr('Settings')}
            push_page(page)
        }
    }

    Widgets.MenuItemIcon {
    // MenuItem {
        text: qsTr('About')
        image: 'qrc:/icons/help-black.png'
        onTriggered: about_dialog.open()
    }

    Component.onCompleted: {
       var component = Qt.createComponent('qrc:/qml/Widgets/MenuItemIcon.qml')
        settings_item = component.createObject(null, {
            text: 'Settings',
            image: 'qrc:/icons/build-black.png',
        })
        settings_item.triggered.connect(open_settings_dialog)
    }

    function enable_settings_menu(has_page_settings) {
        if (has_page_settings != is_settings_menu_enabled) {
            if (has_page_settings)
                options_menu.insertItem(0, settings_item)
            else
                options_menu.removeItem(0)
            is_settings_menu_enabled = has_page_settings
        }
    }
}
