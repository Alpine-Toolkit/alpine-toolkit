// console.info('Load camptocamp_search_filter.js');

// .import 'qrc:/js/set.js' as Set;
var rc = Qt.include('qrc:/js/set.js');
if (rc.status != 0)
    console.error('include error in set.js')

var rc = Qt.include('qrc:/js/camptocamp_search_filter_definitions.js');
if (rc.status != 0)
    console.error('include error in camptocamp_search_filter_definitions.js')

/**************************************************************************************************/

var filter_for_activity = {}
Object.keys(activity_dict).forEach(function(activity) {
    filter_for_activity[activity] = [];
});
Object.keys(filter_definitions).forEach(function(filter) {
    // console.info(filter);
    var filter_definition = filter_definitions[filter];
    if (filter_definition.title) {
	var activities = filter_definitions[filter].activities;
	if (activities === 'all')
	    activities = all_activities;
	activities.forEach(function(activity) {
	    filter_for_activity[activity].push(filter);
	});
    }
});
// console.info(JSON.stringify(filter_for_activity));

var checkable_button_component = Qt.createComponent('qrc:C2cFilter/ActivityFilter.qml');

function create_activity_buttons() {
    // console.info('create_activity_buttons');
    if (checkable_button_component.status == Component.Ready)
	finish_activity_buttons();
    else
	checkable_button_component.statusChanged.connect(finish_activity_buttons);
}

function finish_activity_buttons() {
    if (checkable_button_component.status == Component.Ready) {
	// console.info('finish_activity_buttons');
	Object.keys(activity_dict).forEach(function(activity) {
	    // console.info(activity);
	    var properties = {
		// text: activity_dict[activity].title
		text: activity_dict[activity].glyph //,
		// font: {family: 'c2c-activity_dict', pointSize: 18} // activities_font.name
	    }
	    var button = checkable_button_component.createObject(activity_container, properties);
	    button.font.pointSize = 24;
	    button.onCheckedChanged.connect(update_filters);
	    activity_dict[activity].button = button;
	})
    } else {
	// Fixme: 
    }
}

/**************************************************************************************************/

var range_slider_component = Qt.createComponent('qrc:/C2cFilter/RangeSliderFilter.qml');
var grade_range_slider_component = Qt.createComponent('qrc:/C2cFilter/GradeRangeSliderFilter.qml');
var check_box_component = Qt.createComponent('qrc:/C2cFilter/CheckBoxFilter.qml');
var compass_rose_component = Qt.createComponent('qrc:/C2cFilter/CompassRoseFilter.qml');

var components_are_ready = false;

function range_slider_done() {
    // console.info('range_slider_done')
    range_slider_component.statusChanged.disconnect(range_slider_done);
    update_filters();
}

function grade_range_slider_done() {
    // console.info('grade_range_slider_done')
    grade_range_slider_component.statusChanged.disconnect(grade_range_slider_done);
    update_filters();
}

function check_box_done() {
    // console.info('check_box_done')
    check_box_component.statusChanged.disconnect(check_box_done);
    update_filters();
}

function compass_rose_done() {
    // console.info('compass_rose_done')
    compass_rose_component.statusChanged.disconnect(compass_rose_done);
    update_filters();
}

function update_filters() {
    // console.info('update_filters ' + components_are_ready)
    if (components_are_ready)
	finish_update_filters();
    else {
	if (range_slider_component.status != Component.Ready) {
	    // console.info('range_slider not ready');
	    range_slider_component.statusChanged.connect(range_slider_done);
	} else if (grade_range_slider_component.status != Component.Ready) {
	    // console.info('grade_range_slider not ready');
	    grade_range_slider_component.statusChanged.connect(grade_range_slider_done);
	} else if (check_box_component.status != Component.Ready) {
	    // console.info('check_box not ready');
	    check_box_component.statusChanged.connect(check_box_done);
	} else if (compass_rose_component.status != Component.Ready) {
	    // console.info('compass_rose not ready');
	    compass_rose_component.statusChanged.connect(compass_rose_done);
	} else {
	    components_are_ready = true;
	    finish_update_filters();
	}
    }
}

var filter_objects = {};

function finish_update_filters() {
    // console.info('finish_update_filters')

    var old_filters = []
    Object.keys(filter_objects).forEach(function(filter) {
	old_filters.push(filter);
    });

    // Fixme: default filter
    var current_filters = Set();
    get_activities().forEach(function(activity) {
	filter_for_activity[activity].forEach(function(filter) {
	    // // console.info('  ' + filter);
	    set_add(current_filters, filter);
	});
    });

    // Fixme: Sort
    // var foo = current_filters.sort(function(a, b) {
    // 	return filter_definitions[a].title < filter_definitions[b].title;
    // });
    // console.info(current_filters, foo);

    var unused_filters = set_difference(old_filters, current_filters);
    unused_filters.forEach(function(filter) {
	filter_objects[filter].visible = false;
    });

    var visible_filters = set_intersection(old_filters, current_filters);
    visible_filters.forEach(function(filter) {
	filter_objects[filter].visible = true;
    });

    var new_filters = set_difference(current_filters, old_filters);
    new_filters.forEach(function(filter) {
	var filter_definition = filter_definitions[filter];
	var obj;
	if (filter_definition.type == 'RangeSlider')
	    obj = create_range_slider(filter);
	else if (filter_definition.type == 'GradeRangeSlider')
	    obj = create_grade_range_slider(filter);
	else if (filter_definition.type == 'CheckBoxFilter')
	    obj = create_check_box(filter);
	else if (filter_definition.type == 'CompassRoseFilter')
	    obj = create_compass_rose(filter);
	filter_objects[filter] = obj;
    });

    // var childrens = filter_container.children
    // console.info('items ' + childrens.length)
    // filter_container.children = childrens
}

function create_range_slider(filter) {
    // console.info('create_range_slider', filter)
    var filter_definition = filter_definitions[filter];
    var properties = {
	title: filter_definition.title,
	min: 0, // filter_definition.min,
	max: filter_definition.max,
	step_size: filter_definition.step_size,
	unit: filter_definition.unit
    }
    var range_slider = range_slider_component.createObject(filter_container, properties);
    return range_slider;
}

function create_grade_range_slider(filter) {
    // console.info('create_grade_range_slider', filter)
    var filter_definition = filter_definitions[filter];
    var properties = {
	title: filter_definition.title,
	values: filter_definition.values,
    }
    var grade_range_slider = grade_range_slider_component.createObject(filter_container, properties);
    return grade_range_slider;
}

function create_check_box(filter) {
    // console.info('create_check_box', filter)
    var filter_definition = filter_definitions[filter];
    var properties = {
	title: filter_definition.title,
	values: filter_definition.values,
    }
    var check_box = check_box_component.createObject(filter_container, properties);
    return check_box;
}

function create_compass_rose(filter) {
    // console.info('create_compass_rose', filter)
    var filter_definition = filter_definitions[filter];
    var properties = {
	title: filter_definition.title,
    }
    var compass_rose = compass_rose_component.createObject(filter_container, properties);
    return compass_rose;
}

/**************************************************************************************************/

function get_search_filters_state() {
    return {
	activities: get_activities(),
	filters: get_filters_state(),
    }
}

function get_activities() {
    // act=foo,bar
    var activities = [];
    Object.keys(activity_dict).forEach(function(activity) {
	if (activity_dict[activity].button.checked)
	    activities.push(activity);
    });
    return activities; // .join();
}

function get_filters_state() {
    var states = {};
    Object.keys(filter_objects).forEach(function(filter) {
	var filter_definition = filter_definitions[filter];
	var obj = filter_objects[filter];
	var state = obj.get_state();
	if (state !== null)
	    states[filter] = state;
    });
    return states;
}

function set_search_filters_state(search_filters_state) {
    // console.info('set_search_filters_state', JSON.stringify(search_filters_state));
    if (search_filters_state) {
	if ('activities' in search_filters_state)
	    set_activities();
	if ('filters' in search_filters_state)
	    set_filters_state();
    }
}

function set_activities() {
    search_filters_state.activities.forEach(function(activity) {
	activity_dict[activity].button.checked = true;
    });
}

function set_filters_state() {
    var filters = search_filters_state.filters;
    Object.keys(filters).forEach(function(filter) {
	// console.info('set_filters_state', filter);
	if (filter in filter_objects)
	    filter_objects[filter].set_state(filters[filter]);
    });
}
