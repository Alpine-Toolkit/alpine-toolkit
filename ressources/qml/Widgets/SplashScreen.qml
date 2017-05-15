import QtQuick 2.6

import QtQuick.Controls 2.0

Pane {
    id: splash_screen_pane

    Image {
        anchors.centerIn: parent
        property int image_size: Math.min(parent.width, parent.height) * .9
        width: image_size
        height: image_size
        // source: 'asset:///application-icons/icon.svg'
        source: 'qrc:/application-icons/icon-transparent.svg'
        // property int image_size: Math.min(Math.min(parent.width, parent.height) * .9, 512)
        // source: 'qrc:/application-icons/icon-512.png'
    }
}
