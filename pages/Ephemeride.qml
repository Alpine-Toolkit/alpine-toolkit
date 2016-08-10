import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
// import Qt.labs.controls.material 1.0

import QtPositioning 5.5

Pane {
    id: ephemeride_pane

    property int font_size: 20

    PositionSource {
        id: position_source
        active: true

        onValidChanged: {
            var date = new Date();
            var coordinate = position_source.position.coordinate;

            ephemeride.coordinate = coordinate;
            ephemeride.date = date;

            // console.log("Coordinate:", coordinate.longitude, coordinate.latitude);
            // console.log("Date:", date);
            // console.log("sunrise:", ephemeride.sunrise);
            // console.log("noon:", ephemeride.solar_noon);
            // console.log("sunset:", ephemeride.sunset);

            date_label.text = date.toLocaleString(Qt.locale(), "dd/MM/yyyy");
            coordinate_label.text = coordinate.longitude + "\n" + coordinate.latitude;
            sunrise_label.text = ephemeride.sunrise.toLocaleTimeString(Qt.locale(), "hh:mm");
            noon_label.text = ephemeride.solar_noon.toLocaleTimeString(Qt.locale(), "hh:mm");
            sunset_label.text = ephemeride.sunset.toLocaleTimeString(Qt.locale(), "hh:mm");

            position_source.active = false;
        }
    }

    // choose position : (latitude, longitude), address
    // choose date
    // warn user to enable gps

    Column {
        anchors.fill: parent
        anchors.topMargin: 10

        GridLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 2
            columnSpacing : 10
            rowSpacing : 5

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                font.pointSize: font_size
                text: qsTr("Date")
            }
            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                id: date_label
                font.pointSize: font_size
                text: "unknown"
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                font.pointSize: font_size
                text: qsTr("Coordinate")
            }
            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                id: coordinate_label
                font.pointSize: font_size
                text: "unknown"
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                font.pointSize: font_size
                text: qsTr("Sunrise")
            }
            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                id: sunrise_label
                font.pointSize: font_size
                text: "unknown"
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                font.pointSize: font_size
                text: qsTr("Noon")
            }
            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                id: noon_label
                font.pointSize: font_size
                text: "unknown"
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                font.pointSize: font_size
                text: qsTr("Sunset")
            }
            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                id: sunset_label
                font.pointSize: font_size
                text: "unknown"
            }
        }
    }
}
