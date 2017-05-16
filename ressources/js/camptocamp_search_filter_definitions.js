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

/**************************************************************************************************
 *
 * See v6_ui/c2corg_ui/templates/route/filters.html
 *
 **************************************************************************************************/

var rc = Qt.include('qrc:/js/camptocamp_definitions.js');
if (rc.status != 0)
    console.error('include error in camptocamp_definitions.js')

/**************************************************************************************************/

var filter_definitions = {
    'elevation_max': {
	key: 'rmaxa',
	title: 'Max Altitude',
	activities: 'all',
	type: 'RangeSlider',
	max: 8850,
	step_size: 10,
	unit: 'm',
    },

    // Skitouring
    'ski_rating': {
	key: 'trat',
	title: 'Ski Rating',
	activities: ['skitouring'],
	type: 'GradeRangeSlider',
	values: ski_ratings,
    },
    'ski_exposition': {
	key: 'sexpo',
	title: 'Ski Exposition',
	activities: ['skitouring'],
	type: 'GradeRangeSlider',
	values: exposition_ratings,
    },
    'labande_global_rating': {
	key: 'lrat',
	title: 'Global Ski Rating',
	activities: ['skitouring'],
	type: 'GradeRangeSlider',
	values: global_ratings,
    },
    'labande_ski_rating': {
	key: 'srat',
	title: 'One-off Ski Rating',
	activities: ['skitouring'],
	type: 'GradeRangeSlider',
	values: labande_ski_ratings,
    },

    // Rock Climbing
    'climbing_outdoor_type': {
	key: 'crtyp',
	title: 'Climbing Outdoor Type',
	activities: ['rock_climbing'],
	type: 'CheckBoxFilter',
	values: climbing_outdoor_types,
    },

    // Rock and Alpine Climbing
    // 'rock_climbing_free_rating'
    'rock_free_rating': {
	key: 'frat',
	title: 'Rock Climbing Free Rating',
	activities: ['rock_climbing'],
	type: 'GradeRangeSlider', // Fixme: name ?
	values: climbing_ratings,
    },
    'rock_required_rating': {
	key: 'rrat',
	title: 'Rock Climbing Required Rating',
	activities: ['rock_climbing'],
	type: 'GradeRangeSlider',
	values: climbing_ratings,
    },
    'exposition_rock_rating': {
	key: 'rexpo',
	title: 'Rock Climbing Exposition Rating',
	activities: ['rock_climbing'],
	type: 'GradeRangeSlider',
	values: exposition_rock_ratings,
    },
    'aid_rating': {
	key: 'arat',
	title: 'Aid Rating',
	activities: ['rock_climbing'],
	type: 'GradeRangeSlider',
	values: aid_rating,
    },

    // Snow, Ice, Rock and Alpine Climbing
    'global_rating': {
	key: 'grat',
	title: 'Global Rating',
	activities: ['ice_climbing', 'mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	type: 'GradeRangeSlider',
	values: global_ratings,
    },
    'engagement_rating': {
	key: 'erat',
	title: 'Engagement Rating',
	activities: ['ice_climbing', 'mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	type: 'GradeRangeSlider',
	values: engagement_ratings,
    },
    'risk_rating': {
	key: 'orrat',
	title: 'Risk Rating',
	activities: ['ice_climbing', 'mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	type: 'GradeRangeSlider',
	values: risk_ratings,
    },
    'equipment_rating': {
	key: 'prat',
	title: 'Quality of In-place Protections',
	activities: ['ice_climbing', 'mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	type: 'GradeRangeSlider',
	values: equipment_ratings,
    },
    'difficulties_height': {
	key: 'ralt',
	title: 'Difficulties Start Altitude',
	activities: ['ice_climbing', 'mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	type: 'RangeSlider',
	max: 6000,
	step_size: 10,
	unit: 'm',
    },
    'height_diff_access': {
	key: 'rappr',
	title: 'Access Height Difference',
	activities: ['ice_climbing', 'mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	type: 'RangeSlider',
	max: 3000,
	step_size: 10,
	unit: 'm',
    },
    'height_diff_difficulties': {
	key: 'dhei',
	title: 'Difficulties Height Difference',
	activities: ['ice_climbing', 'mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	type: 'RangeSlider',
	max: 3000,
	step_size: 10,
	unit: 'm',
    },

    // Ice and Snow_ice_mixed
    'ice_rating': {
	key: 'irat',
	title: 'Ice Rating',
	activities: ['ice_climbing', 'snow_ice_mixed'],
	type: 'GradeRangeSlider',
	values: ice_ratings,
    },
    'mixed_rating': {
	key: 'mrat',
	title: 'Mixed Rating',
	activities: ['ice_climbing', 'snow_ice_mixed'],
	type: 'GradeRangeSlider',
	values: mixed_ratings,
    },

    // Via Ferrata
    'via_ferrata_rating': {
	key: 'krat',
	title: 'Via Ferrata Rating',
	activities: ['via_ferrata'],
	type: 'GradeRangeSlider',
	values: via_ferrata_ratings,
    },

    // Hiking
    'hiking_rating': {
	key: 'hrat',
	title: 'Hiking Rating',
	activities: ['hiking'],
	type: 'GradeRangeSlider',
	values: hiking_ratings,
    },

    // Snowshoeing
    'snowshoe_rating': {
	key: 'wrat',
	title: 'Snowshoe Rating',
	activities: ['snowshoeing'],
	type: 'GradeRangeSlider',
	values: snowshoe_ratings,
    },

    // Mountain Biking
    'mtb_up_rating': {
	key: 'mbur',
	title: 'Mountain Bike Rating Up',
	activities: ['mountain_biking'],
	type: 'GradeRangeSlider',
	values: mtb_up_ratings,
    },
    'mtb_down_rating': {
	key: 'mbdr',
	title: 'Mountain Bike Rating Down',
	activities: ['mountain_biking'],
	type: 'GradeRangeSlider',
	values: mtb_down_ratings,
    },
    'mtb_length_asphalt': {
	key: 'mbroad',
	title: 'Asphalt Length',
	activities: ['mountain_biking'],
	type: 'RangeSlider',
	max: 50000,
	step_size: 500,
	unit: 'm',
    },
    'mtb_length_trail': {
	key: 'mbtrack',
	title: 'Trail Length',
	activities: ['mountain_biking'],
	type: 'RangeSlider',
	max: 50000,
	step_size: 500,
	unit: 'm',
    },
    'mtb_height_diff_portages': {
	key: 'mbpush',
	title: 'Portages Height Difference',
	activities: ['mountain_biking'],
	type: 'RangeSlider',
	max: 5000,
	step_size: 100,
	unit: 'm',
    },

    // Hiking and Mountain Biking
    'hiking_mtb_exposition': {
	key: 'hexpo',
	title: 'Hiking/Mountain Biking Exposition',
	activities: ['hiking', 'mountain_biking'],
	type: 'GradeRangeSlider',
	values: exposition_ratings,
    },

    // All
    'elevation_min': {
	key: 'rmina',
	title: 'Min Altitude',
	activities: 'all',
	type:'RangeSlider',
	max: 6000,
	step_size: 10,
	unit: 'm',
    },
    'height_diff_up': {
	key: 'hdif',
	title: 'Elevation Gain',
	activities: 'all',
	type: 'RangeSlider',
	max: 10000,
	step_size: 10,
	unit: 'm',
    },
    'height_diff_down': {
	key: 'ddif',
	title: 'Elevation Loss',
	activities: 'all',
	type: 'RangeSlider',
	max: 10000,
	step_size: 10,
	unit: 'm',
    },
    'orientations': {
    	key: 'fac',
	title: 'Orientations',
	activities: 'all',
	type: 'CompassRoseFilter',
    },
    'durations': {
	key: 'time',
	title: 'Durations',
	activities: 'all',
	unit: 'days',
	type: 'GradeRangeSlider',
	values: route_duration_types,
    },
    'route_types': {
	key: 'rtyp',
	title: 'Route Types',
	activities: 'all',
	type: 'CheckBoxFilter',
	values: route_types,
    },
    'configuration': {
	key: 'conf',
	title: 'Configuration',
	activities: 'all',
	type: 'CheckBoxFilter',
	values: route_configuration_types,
    },

    // All except Mountain Biking
    'glacier_gear': {
	key: 'glac',
	title: 'Glacier Gear',
	activities: ['hiking', 'ice_climbing', 'mountain_climbing', 'paragliding', 'rock_climbing',
		     'skitouring', 'snow_ice_mixed', 'snowshoeing', 'via_ferrata'],
	type: 'CheckBoxFilter',
	values: glacier_gear_types,
    },

    // Skitouring, Snowshoeing, Hiking, Mountain Biking
    'route_length': {
	key: 'rlen',
	title: 'Route Length',
	activities: ['hiking', 'mountain_biking', 'skitouring', 'snowshoeing'],
	type: 'RangeSlider',
	max: 100000,
	step_size: 500,
	unit: 'm',
    },

    // Snow_ice_mixed, Rock and Alpine Climbing
    'rock_types': {
	key: 'rock',
	title: 'Rock Types',
	activities: ['mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	type: 'CheckBoxFilter',
	values: rock_types,
    },

    // All
    'lang': {
	key: 'l',
	title: 'Language',
	activities: 'all',
	type: 'CheckBoxFilter',
	values: default_langs,
    },
    'quality': {
	key: 'qa',
	title: 'Quality',
	activities: 'all',
	type:'GradeRangeSlider',
	values: quality_types,
    },
};
