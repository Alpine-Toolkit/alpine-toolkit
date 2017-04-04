import QtQuick 2.6

import QtQuick.Controls 2.0

Column {
    property string title: ''

    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width

    spacing: 10

    Rectangle {
	width: parent.width
	height: 1
	color: 'black'
    }

    Text {
	id: title_label
	anchors.horizontalCenter: parent.horizontalCenter
	text: title
    }
}
