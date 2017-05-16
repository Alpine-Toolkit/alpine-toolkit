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
