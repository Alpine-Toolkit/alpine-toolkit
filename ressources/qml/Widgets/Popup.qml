import QtQml 2.2
import QtQuick 2.6

import QtQuick.Controls 2.1

Popup {
    modal: true
    focus: true

    property real factor: .9
    width: parent.width * factor
    height: parent.height * factor
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    // closePolicy: Popup.OnEscape | Popup.OnPressOutside
}
