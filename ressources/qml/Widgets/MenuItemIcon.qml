import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2 // Fixme

MenuItem {
    id: control

    property string image

    contentItem: Row {
        spacing: 10

        leftPadding: control.checkable && !control.mirrored ? control.indicator.width + control.spacing : 0
        rightPadding: control.checkable && control.mirrored ? control.indicator.width + control.spacing : 0

        Image {
            height: text_item.height
            width: height
            fillMode: Image.Stretch
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            source: control.image
        }

        Text {
            id: text_item
            text: control.text
            font: control.font
            color: control.enabled ? Material.foreground : Material.hintTextColor
            // color: control.enabled ? control.Material.foreground : control.Material.hintTextColor
            elide: Text.ElideRight
            visible: control.text
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }
    }
}
