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

    ListElement {
        title: qsTr('Altimeter')
        icon: 'qrc:/icons/altimeter-black.png'
        source: 'qrc:/Pages/Altimeter.qml' // Pages.Altimeter is not supported
        lock_orientation: false
    }

    // ListElement {
    //     title: qsTr('Bleau')
    //     icon: ''
    //     source: 'qrc:/Pages/Bleau.qml'
    //     lock_orientation: false
    // }

    ListElement {
        title: qsTr('Camptocamp')
        icon: 'qrc:/icons/camptocamp-black.png'
        source: 'qrc:/Pages/Camptocamp.qml'
        lock_orientation: false
    }

    // ListElement {
    //     title: qsTr('Check List')
    //     icon: ''
    //     source: 'qrc:/Pages/Checklist.qml'
    //     lock_orientation: false
    // }

    ListElement {
        title: qsTr('Data Logger')
        icon: ''
        source: 'qrc:/Pages/DataLogger.qml'
        lock_orientation: false
    }

    ListElement {
        title: qsTr('Ephemeride')
        icon: 'qrc:/icons/ephemeride-black.png'
        source: 'qrc:/Pages/Ephemeride.qml'
        lock_orientation: false
    }

    ListElement {
        title: qsTr('Emergency')
        icon: 'qrc:/icons/helicopter-black.png'
        source: 'qrc:/Pages/Emergency.qml'
        lock_orientation: false
    }

    ListElement {
        title: qsTr('Fuel Gauge')
        icon: 'qrc:/icons/fuel-black.png'
        source: 'qrc:/Pages/FuelGauge.qml'
        lock_orientation: false
    }

    ListElement {
        title: qsTr('Inclination')
        icon: 'qrc:/icons/clignometre-black.png'
        source: 'qrc:/Pages/Inclination.qml'
        lock_orientation: true
    }

    ListElement {
        title: qsTr('Illuminance')
        icon: 'qrc:/icons/sun-black.png'
        source: 'qrc:/Pages/Illuminance.qml'
        lock_orientation: false
    }

    ListElement {
        title: qsTr('GPS')
        icon: 'qrc:/icons/explore-black.png'
        source: 'qrc:/Pages/Gps.qml'
        lock_orientation: true
    }

    ListElement {
        title: qsTr('Lamp Signal')
        icon: 'qrc:/icons/lamp-signal-black.png'
        source: 'qrc:/Pages/LampSignal.qml'
        lock_orientation: false
    }

    ListElement {
        title: qsTr('Person Counter')
        icon: 'qrc:/icons/people-black.png'
        source: 'qrc:/Pages/PersonCounter.qml'
        lock_orientation: false
    }

    ListElement {
        title: qsTr('Refuges')
        icon: 'qrc:/icons/hut-black.png'
        source: 'qrc:/Pages/RefugeDirectory.qml'
        lock_orientation: false
    }

    ListElement {
        title: qsTr('Torch')
        icon: 'qrc:/icons/torch-black.png'
        source: 'qrc:/Pages/Torch.qml'
        lock_orientation: false
    }

    /*
      ListElement {
      title: qsTr('Camera')
      icon: ''
      source: 'qrc:/Pages/Camera.qml'
      lock_orientation: false
      }
      ListElement {
      title: qsTr('Heart Rate')
      icon: ''
      source: 'qrc:/Pages/HeartRate.qml'
      lock_orientation: false
      }
      ListElement {
      title: qsTr('Chart')
      icon: ''
      source: 'qrc:/Pages/Chart.qml'
      lock_orientation: false
      }
      ListElement {
      title: qsTr('UI Test')
      icon: ''
      source: 'qrc:/Pages/UiTest.qml'
      lock_orientation: false
      }
    */
}
