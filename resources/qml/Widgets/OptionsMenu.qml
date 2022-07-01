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
