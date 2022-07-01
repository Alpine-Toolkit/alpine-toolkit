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

import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

import QtCharts 2.0

import Constants 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: chart_pane

    ChartView {
        title: 'Accurate Historical Data'
        anchors.fill: parent
        legend.visible: false
        antialiasing: true

        LineSeries {
            axisX: DateTimeAxis {
                format: 'yyyy MMM'
                tickCount: 5
            }
            axisY: ValueAxis {
                min: 0
                max: 150
            }

            // Please note that month in JavaScript months are zero based, so 2 means March
            XYPoint { x: toMsecsSinceEpoch(new Date(1950, 2, 15)); y: 5 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1970, 0, 1)); y: 50 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1987, 12, 31)); y: 102 }
            XYPoint { x: toMsecsSinceEpoch(new Date(1998, 7, 1)); y: 100 }
            XYPoint { x: toMsecsSinceEpoch(new Date(2012, 8, 2)); y: 110 }
        }
    }

    // DateTimeAxis is based on QDateTimes so we must convert our JavaScript dates to
    // milliseconds since epoch to make them match the DateTimeAxis values
    function toMsecsSinceEpoch(date) {
        var msecs = date.getTime();
        return msecs;
    }
}
