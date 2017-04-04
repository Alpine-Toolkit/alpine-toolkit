/**************************************************************************************************
 *
 * See v6_common/c2corg_common/attributes.py
 *
 **************************************************************************************************/

var activity_dict = {
    // \u1abcd don't work ???
    'hiking':            { glyph:'\ue900', title:'hiking' },
    'ice_climbing':      { glyph:'\ue901', title:'ice climbing' },
    'mountain_biking':   { glyph:'\ue902', title:'mountain biking' },
    'mountain_climbing': { glyph:'\ue905', title:'mountain climbing' }, // font: inverted mountain and rock
    'paragliding':       { glyph:'\ue904', title:'paragliding' },
    'rock_climbing':     { glyph:'\ue903', title:'rock climbing' },
    'skitouring':        { glyph:'\ue906', title:'skitouring' },
    'snow_ice_mixed':    { glyph:'\ue907', title:'snow ice mixed' },
    'snowshoeing':       { glyph:'\ue908', title:'snowshoeing' },
    'via_ferrata':       { glyph:'\ue909', title:'via ferrata' }
};

// activities: ['hiking', 'ice_climbing', 'mountain_biking', 'mountain_climbing', 'paragliding', 'rock_climbing',
//              'skitouring', 'snow_ice_mixed', 'snowshoeing', 'via_ferrata'],
var all_activities = Object.keys(activity_dict);

/**************************************************************************************************/

var aid_rating = [
    'A0',
    'A0+',
    'A1',
    'A1+',
    'A2',
    'A2+',
    'A3',
    'A3+',
    'A4',
    'A4+',
    'A5',
    'A5+'
];

var climbing_outdoor_types = [
    'single',
    'multi',
    'bloc',
    'psicobloc' // 'Deep-water soloing'
];

var climbing_ratings = [
    '2',
    '3a', '3b', '3c',
    '4a', '4b', '4c',
    '5a', '5a+', '5b', '5b+', '5c', '5c+',
    '6a', '6a+', '6b', '6b+', '6c', '6c+',
    '7a', '7a+', '7b', '7b+', '7c', '7c+',
    '8a', '8a+', '8b', '8b+', '8c', '8c+',
    '9a', '9a+', '9b', '9b+', '9c', '9c+'
];

var default_langs = ['fr', 'it', 'de', 'en', 'es', 'ca', 'eu'];

var engagement_ratings = [
    'I',
    'II',
    'III',
    'IV',
    'V',
    'VI'
];

var equipment_ratings = [
    'P1',
    'P1+',
    'P2',
    'P2+',
    'P3',
    'P3+',
    'P4',
    'P4+'
];

var exposition_ratings = [
    'E1',
    'E2',
    'E3',
    'E4'
];

var exposition_rock_ratings = [
    'E1',
    'E2',
    'E3',
    'E4',
    'E5',
    'E6'
];

var glacier_gear_types = [
    'no',
    'glacier_safety_gear',  // materiel de securite sur glacier
    'crampons_spring',      // crampons en debut de saison
    'crampons_req',         // crampons indispensable
    'glacier_crampons'      // crampons + materiel de securite sur glacier
];

var global_ratings = [
    'F',
    'F+',
    'PD-',
    'PD',
    'PD+',
    'AD-',
    'AD',
    'AD+',
    'D-',
    'D',
    'D+',
    'TD-',
    'TD',
    'TD+',
    'ED-',
    'ED',
    'ED+',
    'ED4',
    'ED5',
    'ED6',
    'ED7'
];

var hiking_ratings = [
    'T1',
    'T2',
    'T3',
    'T4',
    'T5'
];

var ice_ratings = [
    '1',
    '2',
    '3',
    '3+',
    '4',
    '4+',
    '5',
    '5+',
    '6',
    '6+',
    '7',
    '7+'
];

var labande_ski_ratings = [
    'S1',
    'S2',
    'S3',
    'S4',
    'S5',
    'S6',
    'S7'
];

var mixed_ratings = [
    'M1',
    'M2',
    'M3',
    'M3+',
    'M4',
    'M4+',
    'M5',
    'M5+',
    'M6',
    'M6+',
    'M7',
    'M7+',
    'M8',
    'M8+',
    'M9',
    'M9+',
    'M10',
    'M10+',
    'M11',
    'M11+',
    'M12',
    'M12+'
];

var mtb_down_ratings = [
    'V1',
    'V2',
    'V3',
    'V4',
    'V5'
];

var mtb_up_ratings = [
    'M1',
    'M2',
    'M3',
    'M4',
    'M5'
];

var quality_types = [
    'empty',
    'draft',
    'medium',
    'fine',
    'great'
];

var risk_ratings = [
    'X1',
    'X2',
    'X3',
    'X4',
    'X5'
];

// Unsorted in c2c source
var rock_types = [
    'basalte',
    'calcaire',
    'conglomerat',
    'craie',
    'gneiss',
    'gres',
    'granit',
    'migmatite',
    'mollasse_calcaire',
    'pouding',
    'quartzite',
    'rhyolite',
    'schiste',
    'trachyte',
    'artificial'
];

var route_configuration_types = [
    'edge',
    'pillar',
    'face',
    'corridor',
    'goulotte',
    'glacier'
];

var route_duration_types = [
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '10',
    '10+'
];

var route_types = [
    'return_same_way',  // aller-retour (descente en rappel dans la voie)
    'loop',             // boucle avec retour au pied de la voie (descente en
                        // rappel dans une autre voie)
    'loop_hut',         // boucle avec retour au refuge
    'traverse',         // traversee
    'raid',             // raid
    'expedition'        // expe
];

var ski_ratings = [
    '1.1',
    '1.2',
    '1.3',
    '2.1',
    '2.2',
    '2.3',
    '3.1',
    '3.2',
    '3.3',
    '4.1',
    '4.2',
    '4.3',
    '5.1',
    '5.2',
    '5.3',
    '5.4',
    '5.5',
    '5.6'
];

var snowshoe_ratings = [
    'R1',
    'R2',
    'R3',
    'R4',
    'R5'
];

var via_ferrata_ratings = [
    'K1',
    'K2',
    'K3',
    'K4',
    'K5',
    'K6'
];
