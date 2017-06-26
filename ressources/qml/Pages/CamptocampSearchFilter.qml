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

import "qrc:/C2cFilter" as C2cFilter
import "qrc:/Widgets" as Widgets
import "qrc:/js/camptocamp_search_filter.js" as JsScript

Widgets.Page {
    id: camptocamp_search_filter_pane

    property var search_filters_state: null

    Grid {
	id: activity_container
	anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
	columns: 5
        spacing: 10

	Component.onCompleted: {
	    console.info('camptocamp_search_filter_paner completed');
	    JsScript.create_activity_buttons();
	    JsScript.set_search_filters_state(search_filters_state); // Fixme: qml: set_search_filters_state undefined
	}
    }

    Flickable {
	anchors.top: activity_container.bottom
	anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
	width: parent.width
	height: parent.height - activity_container.height
	contentHeight: filter_container.height
	flickableDirection: Flickable.VerticalFlick
	clip: true

	Column {
	    id: filter_container
            anchors.horizontalCenter: parent.horizontalCenter
	    /* anchors.leftMargin: 10 */
	    /* anchors.rightMargin: 10 */
	    width: parent.width - 40 // Fixme
            spacing: 10

	    // Keep for test purpose
	    // C2cFilter.CompassRoseFilter {}
	    // C2cFilter.RangeSliderFilter { title: 'foo' }
	    // C2cFilter.GradeRangeSliderFilter { title: 'foo'; values: ['a', 'b', 'c'] }
	    // C2cFilter.CheckBoxFilter { title: 'foo'; values: ['aaa', 'bbb', 'ccc'] }
	}

	ScrollBar.vertical: ScrollBar { }
    }

    Component.onDestruction: {
	search_filters_state = JsScript.get_search_filters_state()
	// camptocamp_pane.search_filters_state = state // not defined
	stack_view.get(stack_view.depth -1).search_filters_state = search_filters_state
	console.info('camptocamp_search_filter_pane onDestruction: ' + JSON.stringify(search_filters_state))
    }
}
