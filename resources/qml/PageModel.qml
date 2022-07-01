/***************************************************************************************************
 *
 * This file is part of the Alpine Toolkit software.
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 * SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

import QtQuick 2.6

ListModel {
    id: page_model

    // Fixme: can we move attributes to page ?

    ListElement {
        group: 'mockup'
        title: qsTr('UI Test')
        icon: ''
        source: 'qrc:/qml/Pages/UiTest.qml'
        lock_orientation: false
    }

    ListElement {
        group: 'settings'
        title: qsTr('Settings')
        icon: 'qrc:/icons/settings-sliders-black.png'
        source: 'qrc:/qml/Pages/Settings.qml'
        lock_orientation: false
    }

    ListElement {
        group: 'main'
        title: qsTr('Altimeter')
        icon: 'qrc:/icons/altimeter-black.png'
        source: 'qrc:/qml/Pages/Altimeter.qml' // Pages.Altimeter is not supported
        lock_orientation: false
    }

    // ListElement {
    //     group: 'main'
    //     title: qsTr('Bleau')
    //     icon: ''
    //     source: 'qrc:/qml/Pages/Bleau.qml'
    //     lock_orientation: false
    // }

    ListElement {
        group: 'main'
        title: qsTr('Camptocamp')
        icon: 'qrc:/icons/camptocamp-black.png'
        source: 'qrc:/qml/Pages/Camptocamp.qml'
        lock_orientation: false
        require_storage: true
    }

    // ListElement {
    //     group: 'main'
    //     title: qsTr('Check List')
    //     icon: ''
    //     source: 'qrc:/qml/Pages/Checklist.qml'
    //     lock_orientation: false
    // }

    ListElement {
        group: 'main'
        title: qsTr('Data Logger')
        icon: 'qrc:/icons/data-logger-black.png'
        source: 'qrc:/qml/Pages/DataLogger.qml'
        lock_orientation: false
    }

    ListElement {
        group: 'main'
        title: qsTr('Ephemeride')
        icon: 'qrc:/icons/ephemeride-black.png'
        source: 'qrc:/qml/Pages/Ephemeride.qml'
        lock_orientation: false
    }

    ListElement {
        group: 'main'
        title: qsTr('Emergency')
        icon: 'qrc:/icons/helicopter-black.png'
        source: 'qrc:/qml/Pages/Emergency.qml'
        lock_orientation: false
    }

    ListElement {
        group: 'main'
        title: qsTr('Fuel Gauge')
        icon: 'qrc:/icons/fuel-black.png'
        source: 'qrc:/qml/Pages/FuelGauge.qml'
        lock_orientation: false
    }

    ListElement {
        group: 'main'
        title: qsTr('Inclination')
        icon: 'qrc:/icons/clignometre-black.png'
        source: 'qrc:/qml/Pages/Inclination.qml'
        lock_orientation: true
    }

    ListElement {
        group: 'main'
        title: qsTr('Illuminance')
        icon: 'qrc:/icons/sun-black.png'
        source: 'qrc:/qml/Pages/Illuminance.qml'
        lock_orientation: false
    }

    ListElement {
        group: 'main'
        title: qsTr('GPS')
        icon: 'qrc:/icons/explore-black.png'
        source: 'qrc:/qml/Pages/Gps.qml'
        lock_orientation: true
    }

    ListElement {
        group: 'main'
        title: qsTr('Lamp Signal')
        icon: 'qrc:/icons/lamp-signal-black.png'
        source: 'qrc:/qml/Pages/LampSignal.qml'
        lock_orientation: false
    }

    ListElement {
        group: 'main'
        title: qsTr('Map')
        icon: 'qrc:/icons/map-black.png'
        source: 'qrc:/qml/Pages/Map.qml'
        lock_orientation: false
        require_storage: true
    }

    ListElement {
        group: 'main'
        title: qsTr('Person Counter')
        icon: 'qrc:/icons/people-black.png'
        source: 'qrc:/qml/Pages/PersonCounter.qml'
        lock_orientation: false
    }

    ListElement {
        group: 'main'
        title: qsTr('Refuges')
        icon: 'qrc:/icons/hut-black.png'
        source: 'qrc:/qml/Pages/RefugeDirectory.qml'
        lock_orientation: false
    }

    ListElement {
        group: 'main'
        title: qsTr('Torch')
        icon: 'qrc:/icons/torch-black.png'
        source: 'qrc:/qml/Pages/Torch.qml'
        lock_orientation: false
    }

    /*
      ListElement {
      title: qsTr('Camera')
      icon: ''
      source: 'qrc:/qml/Pages/Camera.qml'
      lock_orientation: false
      }
      ListElement {
      title: qsTr('Heart Rate')
      icon: ''
      source: 'qrc:/qml/Pages/HeartRate.qml'
      lock_orientation: false
      }
      ListElement {
      title: qsTr('Chart')
      icon: ''
      source: 'qrc:/qml/Pages/Chart.qml'
      lock_orientation: false
      }
    */
}
