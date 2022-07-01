/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

import QtQml 2.2
import QtQuick 2.6

import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import 'qrc:/js/camptocamp_search_filter_definitions.js' as C2cDefinition
import Constants 1.0
import Local 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: camptocamp_cache_pane

    Component.onCompleted: {
        c2c_client.load_document_on_cache();
    }

    Column {
        width: parent.width
	height: parent.height
	spacing: Style.spacing.base

	Column {
	    id: route_label
	    width: parent.width
	    spacing: Style.spacing.small

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
			text: title('fr') // Fixme: highlight search and show language
		    }

                    Row {
                        width: parent.width

                        Label {
                            padding: 3
                            font.family: activities_font.name
                            font.pointSize: Style.font_size.large
                            text: C2cDefinition.activity_dict[activities[0]].glyph
                        }

                        // Fixme: don't work ???
                        // Repeater {
                        //     // model: ['rock_climbing']
                        //     model: activities
                        //     Label {
                        //         font.family: activities_font.name
                        //         font.pointSize: Style.font_size.large
                        //         text: C2cDefinition.activity_dict[modelData].glyph
                        //     }
                        // }
                    }

                    // Fixme: show max altitude and elevation loss
		}

                onClicked: {
                    console.info('clicked on', title('fr'), id);
                    var page = {source: 'qrc:/qml/Pages/CamptocampRoute.qml'}
                    var properties = {route: c2c_client.get_document(id)};
                    push_page(page, properties);
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
