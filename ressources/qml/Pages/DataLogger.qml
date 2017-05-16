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

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

// import QtSensors 5.1

Pane {
    id: data_logger_pane

    // Component.onCompleted: {
    // }

    // QQmlExpression: Expression qrc:/Pages/DataLogger.qml:16:18 depends on non-NOTIFYable properties:
    //   ServiceClient::replica
    // Connections {
    //     target : service.replica
    //     onPong: console.info("received pong")
    // }

    Column {
	anchors.fill: parent
	spacing: 10

        Button {
            id: start_button
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Start"
            onClicked: {
                // if (! service.started)
                service.start_service();
            }
        }

        Button {
            id: stop_button
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Stop"
            onClicked: {
                // if (service.started)
                service.stop_service();
            }
        }

        Button {
            id: ping_button
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Ping"
            onClicked: {
                console.info("service is started", service.started)
                if (service.started) {
                    service.foo();
                    service.replica.ping()
                }
            }
        }

        Button {
            id: start_timer_button
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Start Timer"
            onClicked: {
                if (service.started)
                    service.replica.start_timer();
            }
        }

        Button {
            id: stop_timer_button
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Stop Timer"
            onClicked:  {
                if (service.started)
                    service.replica.stop_timer()
            }
        }

    }
}
