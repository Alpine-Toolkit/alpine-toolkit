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

import "qrc:Widgets" as Widgets

Widgets.Page {
    id: lamp_signal_pane

    property int button_point_size: 30
    property int button_width: parent.width / 3

    SwipeView {
        id: swipe_view
        currentIndex: 0
        anchors.top: parent.top
        anchors.bottom: page_indicator.top
        width: parent.width

        Pane {
            id: send_message_pane
            width: swipe_view.width
            height: swipe_view.height

            Column {
                anchors.fill: parent
                anchors.topMargin: 10
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                spacing: 30

                Label {
                    id: help_message
                    width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 12
                    wrapMode:Text.WordWrap
                    text: qsTr("<h2><b>Use preferably number and latin alphabet without diacritic.</b></h2>")
                    // <br>Despite International Morse Code has a larger support."
                    // Fixme: show morse code table
                }

                TextArea {
                    id: message_textarea
                    width: parent.width
                    height: (parent.height - help_message.height - rate_box.height - send_button.height - 4 * parent.spacing) / 2
                    anchors.horizontalCenter: parent.horizontalCenter
                    placeholderText: qsTr("Enter message")
                }

                Label {
                    id: send_encoded_message
                    width: parent.width
                    height: message_textarea.height
                    anchors.horizontalCenter: parent.horizontalCenter
                    wrapMode:Text.WordWrap
                }

                Row {
                    id: rate_box
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 10
                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("rate")
                    }
                    SpinBox {
                        id: rate_ms_spinbox
                        from: 50
                        to: 1000
                        stepSize: 50
                        value: 250
                    }
                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        text: qsTr("ms")
                    }
                }

                Button {
                    id: send_button
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Send Message")
                    onClicked : {
                        if (on_android) {
                            var message = message_textarea.text;
                            if (message) {
                                // Fixme: why android_activity ?
                                send_encoded_message.text = android_activity.encode_morse(message);
                                var rate_ms = rate_ms_spinbox.value;
                                android_activity.perform_lamp_signal(message, rate_ms);
                            }
                        }
                    }
                }
            }
        }

        Pane {
            id: message_decoder_pane
            width: swipe_view.width
            height: swipe_view.height

            function decode_message() {
                if (on_android) {
                    var message = encoded_message.text;
                    if (message)
                        decoded_message.text = android_activity.decode_morse(message);
                } else
                    decoded_message.text = "Decoded message ..."
            }

            Column {
                anchors.fill: parent
                anchors.topMargin: 10
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                spacing: 10

                Label {
                    id: title
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 24
                    // wrapMode:Text.WordWrap
                    text: qsTr("Morse Code Decoder") // International
                }

                GridLayout {
                    id: button_layout
                    // width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    Layout.alignment: Qt.AlignCenter
                    columns: 2
                    columnSpacing : 10
                    rowSpacing : 10

                    Button {
                        width: button_width
                        font.pointSize: message_decoder_pane.button_point_size
                        text: qsTr("Dot")
                        onClicked: encoded_message.text += "."
                    }
                    Button {
                        width: button_width
                        font.pointSize: message_decoder_pane.button_point_size
                        text: qsTr("Dash")
                        onClicked: encoded_message.text += "-"
                    }
                    Button {
                        width: button_width
                        font.pointSize: message_decoder_pane.button_point_size
                        text: qsTr("Letter")
                        onClicked: {
                            encoded_message.text += "/";
                            message_decoder_pane.decode_message();
                        }
                    }
                    Button {
                        width: button_width
                        font.pointSize: message_decoder_pane.button_point_size
                        text: qsTr("Word")
                        onClicked: {
                            encoded_message.text += " ";
                            message_decoder_pane.decode_message();
                        }
                    }
                }

                Label {
                    id: encoded_message
                    width: parent.width
                    height: (parent.height - title.height - button_layout.height - delete_button.height - clear_button.height - 5 * parent.spacing) / 2
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 12
                }

                Label {
                    id: decoded_message
                    width: parent.width
                    height: encoded_message.height
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 12
                }

                Button {
                    id: delete_button
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Delete")
                    onClicked : {
                        var message = encoded_message.text;
                        if (message) {
                            encoded_message.text = message.slice(0, message.length -2)
                            // Fixme: cursor is not visible
                        }
                    }
                }

                Button {
                    id: clear_button
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Clear Message")
                    onClicked : {
                        encoded_message.text = ""
                        decoded_message.text = ""
                    }
                }
            }
        }
    }

    PageIndicator {
        id: page_indicator
        count: swipe_view.count
        currentIndex: swipe_view.currentIndex
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
