import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

Popup {
    id: about_dialog

    modal: true
    focus: true
    x: (parent.width - width) / 2
    y: parent.height / 6
    width: Math.min(parent.width, parent.height) / 3 * 2
    contentHeight: about_column.height
    // closePolicy: Popup.OnEscape | Popup.OnPressOutside

    Column {
        id: about_column
        spacing: 20

        Label {
            font.bold: true
            text: 'About'
        }

        Label {
            width: about_dialog.availableWidth
            wrapMode: Label.Wrap
            font.pixelSize: 12
            text: 'Lorem lipsum ...'
        }
    }
}
