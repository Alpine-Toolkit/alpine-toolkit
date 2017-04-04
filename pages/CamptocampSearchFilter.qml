import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

// import "qrc:/js/camptocamp_search_filter_definitions.js" as JsScriptD
import "qrc:/js/camptocamp_search_filter.js" as JsScript

import "qrc:/C2cFilter" as C2cFilter

Pane {
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
	console.info('camptocamp_search_filter_pane nDestruction: ' + JSON.stringify(search_filters_state))
    }
}
