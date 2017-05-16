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

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0
// import Qt.labs.controls.material 1.0

import QtSensors 5.1 // .8

import Local 1.0

Pane {
    id: altimeter_pane

    StepCounterSensor {
        id: step_counter_sensor
        active: true

        onReadingChanged: {
            var step_counter = step_counter_sensor.reading.stepCounter;
            step_counter_label.text = step_counter;
            console.info("Step counter", step_counter);
        }
    }

    // HeartRateSensor {
    //     id: heart_rate_sensor
    //     active: true

    //     onReadingChanged: {
    //         var heart_rate = heart_rate_sensor.reading.heartRate;
    //         heart_rate_label.text = heart_rate;
    //         console.info("Heart rate", heart_rate);
    //     }
    // }

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 30
        spacing: 30

        GridLayout {
            width: parent.width
            Layout.alignment: Qt.AlignCenter
            columns: 2
            columnSpacing : 2
            rowSpacing : 2

            Label {
                font.pointSize: 20
                text: qsTr("Step Counter")
            }
            Label {
                font.pointSize: 20
                id: step_counter_label
                text: "unknown"
            }

            // Label {
            //     font.pointSize: 20
            //     text: qsTr("Heart Rate")
            // }
            // Label {
            //     font.pointSize: 20
            //     id: heart_rate_label
            //     text: "unknown"
            // }
        }
    }
}

