import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import Qt.labs.controls 1.0

Pane {
    id: lamp_signal_pane

    SwipeView {
        id: swipe_view
        currentIndex: 0
        anchors.fill: parent

        Pane {
            id: send_message_pane
            width: swipe_view.width
            height: swipe_view.height

            Column {
                width: parent.width
                anchors.top: parent.top
                anchors.topMargin: 50
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                spacing: 30

                Label {
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
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: lamp_signal_pane.height / 3
                    placeholderText: qsTr("Enter message")
                }

                Row {
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
                                var rate_ms = rate_ms_spinbox.value;
                                android_activity.perform_lamp_signal(message, rate_ms);
                            }
                        }
                    }
                }

                // Fixme: send SOS ...
            }
        }

        Pane {
            id: message_decoder_pane
            width: swipe_view.width
            height: swipe_view.height

            function decode_message() {
                if (on_android) {
                    var message = encoded_message.text;
                    if (message) {
                        decoded_message.text = android_activity.decode_morse(message);
                    }
                } else {
                    decoded_message.text = "Decoded message ..."
                }
            }

            Column {
                width: parent.width
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.leftMargin: 10
                anchors.rightMargin: 10
                spacing: 10

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 24
                    // wrapMode:Text.WordWrap
                    text: qsTr("Morse Code Decoder") // International
                }

                GridLayout {
                    // width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    Layout.alignment: Qt.AlignCenter
                    columns: 2
                    columnSpacing : 2 * Screen.devicePixelRatio
                    rowSpacing : 2 * Screen.devicePixelRatio

                    property int button_point_size: 30

                    Button {
                        font.pointSize: button_point_size
                        text: qsTr("Dot")
                        onClicked: encoded_message.text += "."
                    }
                    Button {
                        font.pointSize: button_point_size
                        text: qsTr("Dash")
                        onClicked: encoded_message.text += "-"
                    }
                    Button {
                        font.pointSize: button_point_size
                        text: qsTr("Letter")
                        onClicked: {
                            encoded_message.text += "/";
                            message_decoder_pane.decode_message();
                        }
                    }
                    Button {
                        font.pointSize: button_point_size
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
                    height: 50 // lamp_signal_pane.height / 3
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 12
                }

                Label {
                    id: decoded_message
                    width: parent.width
                    height: 50
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 12
                }

                Button {
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
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Clear Message")
                    onClicked : {
                        encoded_message.text = ""
                        decoded_message.text = ""
                    }
                }

                // Fixme: send SOS ...
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
