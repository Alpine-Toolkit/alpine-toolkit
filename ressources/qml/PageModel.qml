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
