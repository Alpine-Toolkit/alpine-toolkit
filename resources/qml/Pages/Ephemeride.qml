/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

import QtQml 2.2
import QtQuick 2.6

import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

// import Qt.labs.controls.material 1.0

import QtPositioning 5.5

import Constants 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: ephemeride_pane

    property int font_size: Style.font_size.huge
    property bool has_acquired_position: false

    readonly property string help_text: qsTr('<p>The sunrise and sunset results are theoretically accurate to within a minute for locations between +/- 72° latitude, and within 10 minutes outside of those latitudes. <strong>However, due to variations in atmospheric composition, temperature, pressure and conditions, observed values may vary from calculations.</strong></p>')
    // <p>The calculations are based on equations from Astronomical Algorithms, by Jean Meeus.</p>
    // Sunrise/set are accurately derived from celestial mechanics and the local position, but this computation doesn't predict the twilight period which depend of the atmospheric conditions and other parameters.

    function format_longitude(longitude) {
        return Number(longitude).toLocaleString(Qt.locale(), 'f', 2)
    }

    function format_latitude(latitude) {
        return Number(latitude).toLocaleString(Qt.locale(), 'f', 2)
    }

    function format_coordinate(coordinate) {
        return format_longitude(coordinate.longitude) + '\n' + format_latitude(coordinate.latitude)
    }

    function format_date(date) {
        return date.toLocaleString(Qt.locale(), 'dd/MM/yyyy')
    }

    function format_time(time) {
        return time.toLocaleTimeString(Qt.locale(), 'hh:mm')
    }

    PositionSource {
        id: position_source
        active: true

        // nmeaSource: 'nmea-samples.txt'

        onValidChanged: {
            var date = new Date();
            var coordinate = position_source.position.coordinate;

            ephemeride.coordinate = coordinate;
            ephemeride.date = date;

            // console.log('Coordinate:', coordinate.longitude, coordinate.latitude);
            // console.log('Date:', date);
            // console.log('sunrise:', ephemeride.sunrise);
            // console.log('noon:', ephemeride.solar_noon);
            // console.log('sunset:', ephemeride.sunset);

	    has_acquired_position = coordinate.isValid

            date_label.text = format_date(date);
            coordinate_label.text = format_coordinate(coordinate);
            sunrise_label.text = format_time(ephemeride.sunrise);
            noon_label.text = format_time(ephemeride.solar_noon);
            sunset_label.text = format_time(ephemeride.sunset);

            position_source.active = false;
        }
    }

    // choose position : (latitude, longitude), address
    // choose date
    // warn user to enable gps

    Column {
        anchors.fill: parent
        anchors.topMargin: 10
	spacing: Style.spacing.large

	Label {
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: font_size
	    visible: has_acquired_position == false
	    text: qsTr('Position is unknown')
	}

        GridLayout {
            anchors.horizontalCenter: parent.horizontalCenter
            columns: 2
            columnSpacing : 10
            rowSpacing : 5

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                font.pointSize: font_size
                text: qsTr('Date')
            }
            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                id: date_label
                font.pointSize: font_size
                text: 'unknown'
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                font.pointSize: font_size
                text: qsTr('Coordinate')
            }
            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                id: coordinate_label
                font.pointSize: font_size
                text: 'unknown'
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                font.pointSize: font_size
                text: qsTr('Sunrise')
            }
            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                id: sunrise_label
                font.pointSize: font_size
                text: 'unknown'
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                font.pointSize: font_size
                text: qsTr('Noon')
            }
            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                id: noon_label
                font.pointSize: font_size
                text: 'unknown'
            }

            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                font.pointSize: font_size
                text: qsTr('Sunset')
            }
            Label {
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                id: sunset_label
                font.pointSize: font_size
                text: 'unknown'
            }
        }

	RowLayout {
	    width: parent.width
	    spacing: Style.spacing.base

            Image {
		id: warning_icon
		Layout.alignment: Qt.AlignVCenter
		fillMode: Image.Pad
		horizontalAlignment: Image.AlignHCenter
		verticalAlignment: Image.AlignVCenter
		source: 'qrc:/icons/warning-black.png'
            }
            TextArea {
		font.pointSize: Style.font_size.small
		Layout.fillWidth: true
		readOnly: true
		text: help_text
		textFormat: TextEdit.RichText
		wrapMode: Text.WordWrap
		background: null // suppress bottom line
            }
	}
    }
}
