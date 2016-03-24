import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0

import QtPositioning 5.5

Pane {
    id: ephemeride_pane

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
            coordinate_label.text = coordinate.longitude + " " + coordinate.latitude;
            sunrise_label.text = ephemeride.sunrise.toLocaleTimeString(Qt.locale(), "hh:mm");
            noon_label.text = ephemeride.solar_noon.toLocaleTimeString(Qt.locale(), "hh:mm");
            sunset_label.text = ephemeride.sunset.toLocaleTimeString(Qt.locale(), "hh:mm");

            position_source.active = false;
        }
    }

    // choose position : (latitude, longitude), address
    // choose date
    // warn user to enable gps

   ColumnLayout {
       id: column_layout
       width: parent.width
       anchors.top: parent.top
       anchors.topMargin: 30
       spacing: 30

       GridLayout {
           width: parent.width
           Layout.alignment: Qt.AlignCenter
           columns: 2
           columnSpacing : 2 * Screen.devicePixelRatio
           rowSpacing : 2 * Screen.devicePixelRatio

           Label {
               text: qsTr("Date")
           }
           Label {
               id: date_label
               text: "unknown"
           }

           Label {
               text: qsTr("Coordinate")
           }
           Label {
               id: coordinate_label
               text: "unknown"
           }

           Label {
               text: qsTr("Sunrise")
           }
           Label {
               id: sunrise_label
               text: "unknown"
           }

           Label {
               text: qsTr("Noon")
           }
           Label {
               id: noon_label
               text: "unknown"
           }

           Label {
               text: qsTr("Sunset")
           }
           Label {
               id: sunset_label
               text: "unknown"
           }
       }
   }
}