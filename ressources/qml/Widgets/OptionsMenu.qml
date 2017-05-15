import QtQuick 2.6

import QtQuick.Controls 2.0

Menu {
    id: options_menu

    property var about_dialog;

    x: parent.width - width
    transformOrigin: Menu.TopRight

    MenuItem {
        text: 'Settings'
    }
    MenuItem {
        text: 'About'
        onTriggered: about_dialog.open()
    }
}
