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

// import Qt.labs.controls.material 1.0

import QtPositioning 5.5

import Constants 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: ephemeride_pane

    property int font_size: Style.font_size.huge
    property string emergency_phone_number: '112' // Europe

    // Fixme: duplicated...
    function format_longitude(longitude) {
        return Number(longitude).toLocaleString(Qt.locale(), 'f', 4)
    }

    function format_latitude(latitude) {
        return Number(latitude).toLocaleString(Qt.locale(), 'f', 4)
    }

    PositionSource {
        id: position_source
        active: true

        onValidChanged: {
            var coordinate = position_source.position.coordinate;
            latitude_label.text = format_latitude(coordinate.latitude);
            longitude_label.text = format_longitude(coordinate.longitude);
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
                columnSpacing : 10
                rowSpacing : 5

                Label {
                    font.pointSize: font_size
                    text: qsTr('Latitude')
                }
                Label {
                    id: latitude_label
                    font.pointSize: font_size
                    text: 'unknown'
                }
                Label {
                    font.pointSize: font_size
                    text: qsTr('Longitude')
                }
                Label {
                    id: longitude_label
                    font.pointSize: font_size
                    text: 'unknown'
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
                spacing: 2*Style.spacing.large

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: font_size
                    text: qsTr('Phone Number')
                }

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: font_size
                    text: emergency_phone_number
                }

                Button {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr('Emergency Call')
                    onClicked: platform_abstraction.issue_dial(emergency_phone_number); // double confirmation ?
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
