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
	title: '',
	activities: ['skitouring'],
	values: ski_ratings,
    },
    'ski_exposition': {
	key: 'sexpo',
	title: '',
	activities: ['skitouring'],
	values: exposition_ratings,
    },
    'labande_global_rating': {
	key: 'lrat',
	title: '',
	activities: ['skitouring'],
	values: global_ratings,
    },
    'labande_ski_rating': {
	key: 'srat',
	title: '',
	activities: ['skitouring'],
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
	type:'GradeRangeSlider', // Fixme: name ?
	values: climbing_ratings,
    },
    'rock_required_rating': {
	key: 'rrat',
	title: '',
	activities: ['rock_climbing'],
	type:'GradeRangeSlider',
	values: climbing_ratings,
    },
    'exposition_rock_rating': {
	key: 'rexpo',
	title: '',
	activities: ['rock_climbing'],
	values: exposition_rock_ratings,
    },
    'aid_rating': {
	key: 'arat',
	title: '',
	activities: ['rock_climbing'],
	values: aid_rating,
    },

    // Snow, Ice, Rock and Alpine Climbing
    'global_rating': {
	key: 'grat',
	title: '',
	activities: ['ice_climbing', 'mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	values: global_ratings,
    },
    'engagement_rating': {
	key: 'erat',
	title: '',
	activities: ['ice_climbing', 'mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	values: engagement_ratings,
    },
    'risk_rating': {
	key: 'orrat',
	title: '',
	activities: ['ice_climbing', 'mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	values: risk_ratings,
    },
    'equipment_rating': {
	key: 'prat',
	activities: ['ice_climbing', 'mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	title: '',
	values: equipment_ratings,
    },
    'difficulties_height': {
	key: 'ralt',
	title: '',
	activities: ['ice_climbing', 'mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	max: 6000,
    },
    'height_diff_access': {
	key: 'rappr',
	title: '',
	activities: ['ice_climbing', 'mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	max: 3000,
    },
    'height_diff_difficulties': {
	key: 'dhei',
	title: '',
	activities: ['ice_climbing', 'mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
	max: 3000,
    },

    // Ice and Snow_ice_mixed
    'ice_rating': {
	key: 'irat',
	title: '',
	activities: ['ice_climbing', 'snow_ice_mixed'],
	values: ice_ratings,
    },
    'mixed_rating': {
	key: 'mrat',
	title: '',
	activities: ['ice_climbing', 'snow_ice_mixed'],
	values: mixed_ratings,
    },

    // Via Ferrata
    'via_ferrata_rating': {
	key: 'krat',
	title: '',
	activities: ['via_ferrata'],
	values: via_ferrata_ratings,
    },

    // Hiking
    'hiking_rating': {
	key: 'hrat',
	title: '',
	activities: ['hiking'],
	values: hiking_ratings,
    },

    // Snowshoeing
    'snowshoe_rating': {
	key: 'wrat',
	title: '',
	activities: ['snowshoeing'],
	values: snowshoe_ratings,
    },

    // Mountain Biking
    'mtb_up_rating': {
	key: 'mbur',
	title: '',
	activities: ['mountain_biking'],
	values: mtb_up_ratings,
    },
    'mtb_down_rating': {
	key: 'mbdr',
	title: '',
	activities: ['mountain_biking'],
	values: mtb_down_ratings,
    },
    'mtb_length_asphalt': {
	key: 'mbroad',
	title: '',
	activities: ['mountain_biking'],
	max: 50000,
	step: 500,
	unit: 'm',
    },
    'mtb_length_trail': {
	key: 'mbtrack',
	title: '',
	activities: ['mountain_biking'],
	max: 50000,
	step: 500,
	unit: 'm',
    },
    'mtb_height_diff_portages': {
	key: 'mbpush',
	title: '',
	activities: ['mountain_biking'],
	max: 5000,
	step: 100,
	unit: 'm',
    },

    // Hiking and Mountain Biking
    'hiking_mtb_exposition': {
	key: 'hexpo',
	title: '',
	activities: ['hiking', 'mountain_biking'],
	values: exposition_ratings,
    },

    // All
    'elevation_min': {
	key: 'rmina',
	title: '',
	title: 'Altitude Min',
	activities: 'all',
	type:'RangeSlider',
	max: 6000,
	step_size: 10,
	unit: 'm',
    },
    'height_diff_up': {
	key: 'hdif',
	title: '',
	activities: 'all',
	max:10000,
    },
    'height_diff_down': {
	key: 'ddif',
	title: '',
	activities: 'all',
	max: 10000,
    },
    'orientations': {
    	key: 'fac',
	title: 'Orientations',
	activities: 'all',
	type: 'CompassRoseFilter',
    },
    'durations': {
	key: 'time',
	title: '',
	activities: 'all',
	unit: 'days',
	values: route_duration_types,
    },
    'route_types': {
	key: 'rtyp',
	title: '',
	activities: 'all',
	values: route_types,
    },
    'configuration': {
	key: 'conf',
	title: '',
	activities: 'all',
	values: route_configuration_types,
    },

    // All except Mountain Biking
    'glacier_gear': {
	key: 'glac',
	title: '',
	activities: ['hiking', 'ice_climbing', 'mountain_climbing', 'paragliding', 'rock_climbing',
		     'skitouring', 'snow_ice_mixed', 'snowshoeing', 'via_ferrata'],
	values: glacier_gear_types,
    },

    // Skitouring, Snowshoeing, Hiking, Mountain Biking
    'route_length': {
	key: 'rlen',
	title: '',
	activities: ['hiking', 'mountain_biking', 'skitouring', 'snowshoeing'],
	max: 100000,
	step: 500,
	unit: 'm',
    },

    // Snow_ice_mixed, Rock and Alpine Climbing
    'rock_types': {
	key: 'rock',
	title: '',
	activities: ['mountain_climbing', 'rock_climbing', 'snow_ice_mixed'],
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
