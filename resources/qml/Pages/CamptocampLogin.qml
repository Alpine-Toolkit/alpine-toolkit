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

import Constants 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: camptocamp_login_pane

    // Component.onCompleted: {
    // }

    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width

        RowLayout {
            spacing: Style.spacing.large
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width

            Label {
                text: c2c_client.logged ? qsTr('Logged') : qsTr('Not Logged')
            }
        }

        RowLayout {
            spacing: Style.spacing.large
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width

            Label {
                text: qsTr('User')
            }

            TextField {
                id: user_textfield
                Layout.fillWidth: true
                placeholderText: qsTr('User')
                text: c2c_client.username
            }
        }

        RowLayout {
            spacing: Style.spacing.large
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width

            Label {
                text: qsTr('Password')
            }

            TextField {
                id: password_textfield
                Layout.fillWidth: true
                placeholderText: qsTr('Password')
                text: c2c_client.password
                echoMode: TextInput.Password
            }
        }

        Button {
            id: login_button
            text: qsTr('Login')
            onClicked: {
                c2c_client.username = user_textfield.text
                c2c_client.password = password_textfield.text
                c2c_client.save_login() // Fixme: not here !
                c2c_client.login()
                stack_view.pop(StackView.Transition)
            }
        }

        Button {
            id: logout_button
            text: qsTr('Logout')
            onClicked: {
                c2c_client.logout() // Fixme:: do nothing
                stack_view.pop(StackView.Transition)
            }
        }
    }
}
