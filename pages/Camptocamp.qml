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

    property var search_filters_state: {}

    ListModel {
        id: route_model
    }

    Component.onCompleted: {
        console.info('test console log')
        /* c2c_client.logged.connect(on_logged) */
        /* c2c_client.login_failed.connect(on_login_failed) */
    }

    Connections {
        target: c2c_client
        onReceivedDocument: {
            console.info('Received document ' + document_id)
            // console.info('document ' + c2c_client.get_document(document_id))
            var properties = {'route': c2c_client.get_document(document_id)}
            push_page('qrc:/pages/CamptocampRoute.qml', properties)
        }
        onReceivedSearch: {
            var routes = c2c_client.search_result.routes
            console.info('onReceivedSearch ' + routes);
            route_model.clear()
            var i
            for (i = 0; i < routes.length; i++) {
                route_model.append({'title': routes[i].title('fr')});
            }
            // route_list.model = c2c_client.search_result.routes
        }
        // onLogged: {
        //     console.log('Login ' + c2c_client.logged)
        // }
    }

    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width

        RowLayout {
            // spacing: 10
            // anchors.horizontalCenter: parent.horizontalCenter
            // width: parent.width
	    Layout.fillWidth: true
	    Layout.alignment: Qt.AlignRight | Qt.AlignBaseline

            ToolButton {
                id: login_icon
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: c2c_client.logged ? 'qrc:/icons/person-black.png' : 'qrc:/icons/person-outline-black.png'
                }
                onClicked: push_page('qrc:/pages/CamptocampLogin.qml')
            }
        }

        RowLayout {
            // spacing: 10
            // anchors.horizontalCenter: parent.horizontalCenter
            // width: parent.width
	    Layout.fillWidth: true
	    Layout.alignment: Qt.AlignHCenter | Qt.AlignBaseline

            TextField {
                id: search_textfield
                Layout.fillWidth: true
                placeholderText: qsTr('Search')
                text: 'la sonia'
            }

            ToolButton {
                id: search_icon
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: 'qrc:/icons/search-black.png'
                }
                onClicked: {
                    /* var search_settings = C2cSearchSettings() */
                    c2c_client.search(search_textfield.text, search_settings);
                }
            }

            ToolButton {
                id: filter_icon
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: 'qrc:/icons/filter-black.png'
                }
                onClicked: {
		    var properties = { 'search_filters_state': search_filters_state }
		    console.info('clicked ' + JSON.stringify(properties))
		    var item = push_page('qrc:/pages/CamptocampSearchFilter.qml', properties)
		    console.info('pushed ' + item)
		}
            }

            // Button {
            //     id: route_button
            //     text: qsTr('Route')
            //     onClicked: {
            //         c2c_client.route(570170)
            //     }
            // }
        }

        ListView {
            id: route_list
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width
            height: 600

            // model: null
            // model: c2c_client.search_result.routes
            model: route_model
            delegate: Text { text: model.index + ' ' + model.title }
        }
    }

    function on_logged() {
        console.log('Logged')
    }

    function on_login_failed() {
        console.log('Login failed')
    }
}
