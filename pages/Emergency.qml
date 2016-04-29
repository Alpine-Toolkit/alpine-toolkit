import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
// import Qt.labs.controls.material 1.0

import QtPositioning 5.5

Pane {
    id: ephemeride_pane

    PositionSource {
        id: position_source
        active: true

        onValidChanged: {
            var coordinate = position_source.position.coordinate;
            latitude_label.text = coordinate.latitude;
            longitude_label.text = coordinate.longitude;
        }
    }

    SwipeView {
        id: swipe_view
        currentIndex: 0
        anchors.fill: parent

        Pane {
            id: coordinate_pane
            width: swipe_view.width
            height: swipe_view.height

            GridLayout {
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                Layout.alignment: Qt.AlignCenter
                columns: 2
                columnSpacing : 2 * Screen.devicePixelRatio
                rowSpacing : 2 * Screen.devicePixelRatio

                Label {
                    text: qsTr("Latitude")
                }
                Label {
                    id: latitude_label
                    text: "unknown"
                }
                Label {
                    text: qsTr("Longitude")
                }
                Label {
                    id: longitude_label
                    text: "unknown"
                }
            }
        }

        Pane {
            id: call_pane
            width: swipe_view.width
            height: swipe_view.height

            Column {
                width: parent.width
                anchors.top: parent.top
                anchors.topMargin: 30
                spacing: 40

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Phone Number")
                }
                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Emergency Call")
                    onClicked: {
                        console.info("clicked on emergency call", on_android, android_activity)
                        if (on_android) {
                            android_activity.issue_dial("000000"); // double confirmation ?
                        }
                    }
                }
            }
        }
    }

    PageIndicator {
        count: swipe_view.count
        currentIndex: swipe_view.currentIndex
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
