/***************************************************************************************************
 *
 * This file is part of the Alpine Toolkit software.
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 * SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

import QtQml 2.2
import QtQuick 2.6

import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

// import Qt.labs.controls.material 1.0

import QtSensors 5.1 // .8

import Constants 1.0
import Local 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: altimeter_pane

    StepCounterSensor {
        id: step_counter_sensor
        active: true

        onReadingChanged: {
            var step_counter = step_counter_sensor.reading.stepCounter;
            step_counter_label.text = step_counter;
            console.info('Step counter', step_counter);
        }
    }

    // HeartRateSensor {
    //     id: heart_rate_sensor
    //     active: true

    //     onReadingChanged: {
    //         var heart_rate = heart_rate_sensor.reading.heartRate;
    //         heart_rate_label.text = heart_rate;
    //         console.info('Heart rate', heart_rate);
    //     }
    // }

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 30
        spacing: Style.spacing.huge

        GridLayout {
            width: parent.width
            Layout.alignment: Qt.AlignCenter
            columns: 2
            columnSpacing : 2
            rowSpacing : 2

            Label {
                font.pointSize: Style.font_size.huge
                text: qsTr('Step Counter')
            }
            Label {
                font.pointSize: Style.font_size.huge
                id: step_counter_label
                text: 'unknown'
            }

            // Label {
            //     font.pointSize: Style.font_size.huge
            //     text: qsTr('Heart Rate')
            // }
            // Label {
            //     font.pointSize: Style.font_size.huge
            //     id: heart_rate_label
            //     text: 'unknown'
            // }
        }
    }
}

