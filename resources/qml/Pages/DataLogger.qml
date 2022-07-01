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

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

// import QtSensors 5.1

import Constants 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: data_logger_pane

    // Component.onCompleted: {
    // }

    // QQmlExpression: Expression qrc:/qml/Pages/DataLogger.qml:16:18 depends on non-NOTIFYable properties:
    //   ServiceClient::replica
    // Connections {
    //     target : service.replica
    //     onPong: console.info('received pong')
    // }

    Column {
	anchors.fill: parent
	spacing: Style.spacing.base

        Button {
            id: start_button
            anchors.horizontalCenter: parent.horizontalCenter
            text: 'Start'
            onClicked: {
                // if (! service.started)
                service.start_service();
            }
        }

        Button {
            id: stop_button
            anchors.horizontalCenter: parent.horizontalCenter
            text: 'Stop'
            onClicked: {
                // if (service.started)
                service.stop_service();
            }
        }

        Button {
            id: ping_button
            anchors.horizontalCenter: parent.horizontalCenter
            text: 'Ping'
            onClicked: {
                console.info('service is started', service.started)
                if (service.started) {
                    service.foo();
                    service.replica.ping()
                }
            }
        }

        Button {
            id: start_timer_button
            anchors.horizontalCenter: parent.horizontalCenter
            text: 'Start Timer'
            onClicked: {
                if (service.started)
                    service.replica.start_timer();
            }
        }

        Button {
            id: stop_timer_button
            anchors.horizontalCenter: parent.horizontalCenter
            text: 'Stop Timer'
            onClicked:  {
                if (service.started)
                    service.replica.stop_timer()
            }
        }

    }
}
