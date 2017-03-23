import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

Pane {
    id: camptocamp_pane

    Component.onCompleted: {
        console.info("test console log")
        /* c2c_client.logged.connect(on_logged) */
        /* c2c_client.login_failed.connect(on_login_failed) */

    }

    Connections {
        target: c2c_client
        onReceivedDocument: {
            console.info("Received document " + document_id)
            app_bar.state = "BACK"
            nav_icon.visible = false
            back_icon.visible = true
            // console.info("document " + c2c_client.get_document(document_id))
            var properties = {'route': c2c_client.get_document(document_id)}
            stack_view.push("qrc:/pages/CamptocampRoute.qml", properties, StackView.Transition)
        }
        // onLogged: {
        //     console.log("Login " + c2c_client.logged)
        // }
    }

    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width

        RowLayout {
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width

            ToolButton {
                id: login_icon
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: c2c_client.logged ? "qrc:/icons/person-black.png" : "qrc:/icons/person-outline-black.png"
                }
                onClicked: stack_view.push("qrc:/pages/CamptocampLogin.qml", StackView.Transition)
            }
        }

        RowLayout {
            spacing: 20
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width

            TextField {
                id: search_textfield
                Layout.fillWidth: true
                placeholderText: qsTr("Search")
            }

            ToolButton {
                id: search_icon
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/icons/search-black.png"
                }
                // onClicked:
            }

            Button {
                id: route_button
                text: qsTr("Route")
                onClicked: {
                    c2c_client.route(570170)
                }
            }
        }
    }

    function on_logged() {
        console.log("Logged")
    }

    function on_login_failed() {
        console.log("Login failed")
    }
}
