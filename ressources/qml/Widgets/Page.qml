import QtQml 2.2
import QtQuick 2.6

import QtQuick.Controls 2.1

Pane {
    // To enable a settings dialog define a Popup item with a settings_dialog id

    function open_settings_dialog() {
        if (typeof settings_dialog !== "undefined")
            settings_dialog.open()
    }
}
