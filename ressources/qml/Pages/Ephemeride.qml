/***************************************************************************************************
 *
 * $ALPINE_TOOLKIT_BEGIN_LICENSE:GPL3$
 *
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 *
 * This file is part of the Alpine ToolKit software.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $ALPINE_TOOLKIT_END_LICENSE$
 *
 **************************************************************************************************/

import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
// import Qt.labs.controls.material 1.0

import QtPositioning 5.5

import "qrc:Widgets" as Widgets

Widgets.Page {
    id: ephemeride_pane

    property int font_size: 20
    property bool has_acquired_position: false

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

	    has_acquired_position = coordinate.isValid

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
	spacing : 20

	Label {
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: font_size
	    visible: has_acquired_position == false
	    text: qsTr("Position is unknown")
	}

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

	RowLayout {
	    width: parent.width
	    spacing: 10

            Image {
		id: warning_icon
		Layout.alignment: Qt.AlignVCenter
		fillMode: Image.Pad
		horizontalAlignment: Image.AlignHCenter
		verticalAlignment: Image.AlignVCenter
		source: 'qrc:/icons/warning-black.png'
            }
            TextArea {
		font.pointSize: 10
		Layout.fillWidth: true
		readOnly: true
		text: qsTr("<p>The sunrise and sunset results are theoretically accurate to within a minute for locations between +/- 72° latitude, and within 10 minutes outside of those latitudes. <strong>However, due to variations in atmospheric composition, temperature, pressure and conditions, observed values may vary from calculations.</strong></p>")
                // <p>The calculations are based on equations from Astronomical Algorithms, by Jean Meeus.</p>
                // Sunrise/set are accurately derived from celestial mechanics and the local position, but this computation doesn't predict the twilight period which depend of the atmospheric conditions and other parameters.
		textFormat: TextEdit.RichText
		wrapMode: Text.WordWrap
		background: null // suppress bottom line
            }
	}
    }
}
