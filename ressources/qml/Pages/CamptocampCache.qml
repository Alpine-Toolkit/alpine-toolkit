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
    id: camptocamp_cache_pane

    Component.onCompleted: {
        c2c_client.load_document_on_cache();
    }

    Column {
        width: parent.width
	height: parent.height
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
			text: title("fr") // Fixme: highlight search and show language
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
                    console.info("clicked on", title("fr"), id);
                    var properties = { 'route': c2c_client.get_document(id) };
                    push_page('qrc:/Pages/CamptocampRoute.qml', properties);
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

	    model: c2c_client.document_on_cache
	    delegate: route_delegate
	}
    }
}
