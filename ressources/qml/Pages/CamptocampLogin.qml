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

Pane {
    id: camptocamp_login_pane

    // Component.onCompleted: {
    // }

    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width

        RowLayout {
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width

            Label {
                text: c2c_client.logged ? qsTr("Logged") : qsTr("Not Logged")
            }
        }

        RowLayout {
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width

            Label {
                text: qsTr("User")
            }

            TextField {
                id: user_textfield
                Layout.fillWidth: true
                placeholderText: qsTr("User")
                text: c2c_client.username
            }
        }

        RowLayout {
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width

            Label {
                text: qsTr("Password")
            }

            TextField {
                id: password_textfield
                Layout.fillWidth: true
                placeholderText: qsTr("Password")
                text: c2c_client.password
                echoMode: TextInput.Password
            }
        }

        Button {
            id: login_button
            text: qsTr("Login")
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
            text: qsTr("Logout")
            onClicked: {
                c2c_client.logout() // Fixme:: do nothing
                stack_view.pop(StackView.Transition)
            }
        }
    }
}
