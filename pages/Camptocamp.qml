import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

import Local 1.0

Pane {
    id: camptocamp_pane

    C2cSearchSettings {
        id: search_settings
        route: true
    }

    ListModel {
        id: route_model
    }

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
        onReceivedSearch: {
            var search_result = c2c_client.search_result
            var routes = search_result.routes
            // route_model.clear()
            // var i
            // console.info("onReceivedSearch " + routes);
            // for (i = 0; i < routes.length; i++) {
            //     /* console.info("Route " + i + " " + routes[i].title); */
            //     route_model.append({"title": routes[i].title});
            // }
            route_list.model = routes
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
                text: "la sonia"
            }

            ToolButton {
                id: search_icon
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/icons/search-black.png"
                }
                onClicked: {
                    /* var search_settings = C2cSearchSettings() */
                    c2c_client.search(search_textfield.text, search_settings);
                }
            }

            Button {
                id: route_button
                text: qsTr("Route")
                onClicked: {
                    c2c_client.route(570170)
                }
            }
        }

        ListView {
            id: route_list
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: 600

            model: null
            // model: c2c_client.search_result.routes
            // model: route_model
            delegate: Text { text: model.index + " " + model.title }
        }
    }

    function on_logged() {
        console.log("Logged")
    }

    function on_login_failed() {
        console.log("Login failed")
    }
}
