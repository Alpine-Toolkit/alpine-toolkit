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

import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

import QtPositioning 5.5
import QtSensors 5.1 // .8
import Qt.labs.settings 1.0

import Constants 1.0
import Local 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: altimeter_pane

    // Fixme: could use sqlite settings as well
    Settings {
        id: settings
        category: 'Altimeter'
        property real sea_level_pressure: 0
    }

    Component.onCompleted: {
        if (pressure_sensor.reading) {
            console.log('Restore sea level pressure', settings.sea_level_pressure)
            pressure_sensor.reading.sea_level_pressure = settings.sea_level_pressure
        }
    }

    Component.onDestruction: {
        if (pressure_sensor.reading) {
            var sea_level_pressure = pressure_sensor.reading.sea_level_pressure
            console.log('Save sea level pressure', sea_level_pressure)
            settings.sea_level_pressure = sea_level_pressure
        }
    }

    // Fixme: If not available ???
    // PressureSensor
    BarometerAltimeterSensor {
        id: pressure_sensor
        active: true // ???

        onReadingChanged: {
            // Fixme: Mean Filter
            var pressure = pressure_sensor.reading.pressure // 82500 Pa
            var altitude = pressure_sensor.reading.altitude
            pressure_label.text = Number(pressure).toLocaleString() + ' Pa'
            altitude_label.text = Number(altitude).toLocaleString(Qt.locale(), 'f', 2) + ' m'
        }
    }

    PositionSource {
        id: position_source
        active: true
        updateInterval: 10 // ???
        // D QtPositioning: Regular updates using GPS 1000
        // D QtPositioning: Looper Thread startup time in ms: 1
        // D QtPositioning: Regular updates using network 1000

        onPositionChanged: {
            var position = position_source.position
            var coordinate = position.coordinate
            gps_altitude_label.text = isNaN(coordinate.altitude) ? 'unknown' : coordinate.altitude; // + ' +- ' + position.verticalAccuracy;
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 30
        spacing: Style.spacing.huge

        GridLayout {
            width: parent.width
            Layout.alignment: Qt.AlignCenter
            columns: 2
            columnSpacing : 5
            rowSpacing : 5

            Label {
                font.pointSize: Style.font_size.huge
                text: qsTr('Altitude')
            }
            Label {
                id: altitude_label
                font.pointSize: Style.font_size.huge
                text: 'unknown'
            }

            Label {
                font.pointSize: Style.font_size.huge
                text: 'GPS'
            }
            Label {
                id: gps_altitude_label
                font.pointSize: Style.font_size.huge
                text: 'unknown'
            }

            Label {
                font.pointSize: Style.font_size.huge
                text: qsTr('Pressure')
            }
            Label {
                id: pressure_label
                font.pointSize: Style.font_size.huge
                text: 'unknown'
            }
        }

        Button {
            id: calibrate_button
            Layout.alignment: Qt.AlignCenter
            text: qsTr('Calibrate')
            onClicked: calibrate_popup.open()
        }
    }

    Popup {
        id: calibrate_popup
        modal: true
        focus: true
        // Fixme: not centered
        x: (application_window.width - width) / 2
        y: application_window.height / 6
        width: application_window.width * .9
        contentHeight: column.height

        Column {
            id: column
            width: parent.width
            spacing: Style.spacing.small

            Label {
                font.pointSize: Style.font_size.huge
                font.bold: true
                text: qsTr('Calibrate')
            }

            TextField {
                id: altitude_text_field
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: Style.font_size.huge
                placeholderText: 'enter altitude'
                inputMethodHints: Qt.ImhDigitsOnly
                validator: IntValidator {bottom: 0; top: 11000;}
            }

            Row {
                spacing: Style.spacing.small
                anchors.right: parent.right

                Button {
                    text: 'Cancel'
                    onClicked: calibrate_popup.close()
                    // label.color: '#42a5f5ff'
                    background: null
                }
                Button {
                    text: 'Ok'
                    onClicked: {
                        if (altitude_text_field.text) {
                            var altitude = Number.fromLocaleString(altitude_text_field.text);
                            console.info('clicked on calibrate', altitude_text_field.text);
                            pressure_sensor.reading.altitude = Number.fromLocaleString(altitude_text_field.text);
                        }
                        calibrate_popup.close()
                    }
                    background: null
                }
            }
        }
    }
}

