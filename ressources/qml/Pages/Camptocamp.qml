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

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.1

import Local 1.0

import "qrc:Widgets" as Widgets
import "qrc:/js/camptocamp_search_filter_definitions.js" as C2cDefinition

Widgets.Page {
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
        /* c2c_client.logged.connect(on_logged) */
        /* c2c_client.login_failed.connect(on_login_failed) */
    }

    Connections {
        target: c2c_client
        onReceivedDocument: {
            busy_indicator.running = false;
            console.info('Received document ' + document_id);
            // console.info('document ' + c2c_client.get_document(document_id))
            var properties = { 'route': c2c_client.get_document(document_id) };
            push_page('qrc:/Pages/CamptocampRoute.qml', properties);
        }
        onReceivedSearch: {
            busy_indicator.running = false;
            var routes = c2c_client.search_result.routes;
            route_model.clear();
            for (var i = 0; i < routes.length; i++) {
		var route = routes[i];
		var route_data = {
                    'id': route.id,
		    'title': route.title('fr'),
		    'activities': route.activities,
		};
                console.info(JSON.stringify(route_data));
                route_model.append(route_data);
            }
            console.info('onReceivedSearch ' + route_model);
            // route_list.model = c2c_client.search_result.routes
        }
        // onLogged: {
        //     console.log('Login ' + c2c_client.logged)
        // }
    }

    Column {
	anchors.fill: parent
	spacing: 10

	Column {
	    id: search_toolbar
	    width: parent.width

            Row {
		width: parent.width
		layoutDirection: Qt.RightToLeft

		ToolButton {
                    id: download_icon
                    contentItem: Image {
			fillMode: Image.Pad
			horizontalAlignment: Image.AlignHCenter
			verticalAlignment: Image.AlignVCenter
			source: 'qrc:/icons/cloud-download-black.png'
                    }
                    onClicked: push_page('qrc:/Pages/CamptocampCache.qml')
		}

		ToolButton {
                    id: login_icon
                    contentItem: Image {
			fillMode: Image.Pad
			horizontalAlignment: Image.AlignHCenter
			verticalAlignment: Image.AlignVCenter
			source: c2c_client.logged ? 'qrc:/icons/person-black.png' : 'qrc:/icons/person-outline-black.png'
                    }
                    onClicked: push_page('qrc:/Pages/CamptocampLogin.qml')
		}

                BusyIndicator {
                    id: busy_indicator
                    height: login_icon.height
                    running: false
                }
            }

            RowLayout {
		width: parent.width

		TextField {
                    id: search_textfield
                    Layout.fillWidth: true
                    placeholderText: qsTr('Search')
                    text: 'la sonia' // Fixme: remove
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
                        // c2c_client.route(570170);
                        busy_indicator.running = true;
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
			var item = push_page('qrc:/Pages/CamptocampSearchFilter.qml', properties)
			console.info('pushed ' + item)
		    }
		}
            }
	}

	Column {
	    width: parent.width
	    height: parent.height - search_toolbar.height
	    spacing: 10

	    Column {
		id: route_label
		width: parent.width
		spacing: 5

		Rectangle {
		    width: parent.width
		    height: 1
		    color: 'black'
		}

		Label {
		    width: parent.width
		    text: 'Routes'
		}
	    }

            Component {
                id: route_delegate

                // Fixme: has a text properties
                // cf. https://doc.qt.io/qt-5/qml-qtquick-controls2-itemdelegate.html
                ItemDelegate {
                    width: parent.width
                    padding: 5

                    // redefine content item
                    contentItem: Column {
                        width: parent.width

		        Label {
			    width: parent.width
			    text: title // Fixme: highlight search and show language
		        }

                        Row {
                            width: parent.width

                            Label {
                                padding: 3
                                font.family: activities_font.name
                                font.pointSize: 16
                                text: C2cDefinition.activity_dict[activities[0]].glyph
                            }

                            // Fixme: don't work ???
                            // Repeater {
                            //     // model: ['rock_climbing']
                            //     model: activities
                            //     Label {
                            //         font.family: activities_font.name
                            //         font.pointSize: 16
                            //         text: C2cDefinition.activity_dict[modelData].glyph
                            //     }
                            // }
                        }

                        // Fixme: show max altitude and elevation loss
		    }

                    onClicked: {
                        console.info("clicked on", title, id);
                        busy_indicator.running = true;
                        c2c_client.route(id);
                    }
                }
            }

            ListView {
		// ListView doesn't work with Layout.fillHeight
		id: route_list
		width: parent.width
		height: parent.height - route_label.height
                currentIndex: -1
                clip: true // why ?

		// model: null
		// model: c2c_client.search_result.routes
		model: route_model
		delegate: route_delegate
	    }
        }
    }

    function on_logged() {
        console.log('Logged')
    }

    function on_login_failed() {
        console.log('Login failed')
    }
}
