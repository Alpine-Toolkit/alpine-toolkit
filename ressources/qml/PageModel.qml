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
        icon: ''
        source: 'qrc:/Pages/Altimeter.qml' // Pages.Altimeter is not supported
        lock_orientation: false
    }
    ListElement {
        title: qsTr('Bleau')
        icon: ''
        source: 'qrc:/Pages/Bleau.qml'
        lock_orientation: false
    }
    ListElement {
        title: qsTr('Camptocamp')
        icon: ''
        source: 'qrc:/Pages/Camptocamp.qml'
        lock_orientation: false
    }
    ListElement {
        title: qsTr('Check List')
        icon: ''
        source: 'qrc:/Pages/Checklist.qml'
        lock_orientation: false
    }
    ListElement {
        title: qsTr('Data Logger')
        icon: ''
        source: 'qrc:/Pages/DataLogger.qml'
        lock_orientation: false
    }
    ListElement {
        title: qsTr('Ephemeride')
        icon: ''
        source: 'qrc:/Pages/Ephemeride.qml'
        lock_orientation: false
    }
    ListElement {
        title: qsTr('Emergency')
        icon: ''
        source: 'qrc:/Pages/Emergency.qml'
        lock_orientation: false
    }
    ListElement {
        title: qsTr('Inclination')
        icon: ''
        source: 'qrc:/Pages/Inclination.qml'
        lock_orientation: true
    }
    ListElement {
        title: qsTr('Illuminance')
        icon: ''
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
        icon: ''
        source: 'qrc:/Pages/LampSignal.qml'
        lock_orientation: false
    }
    ListElement {
        title: qsTr('Refuges')
        icon: ''
        source: 'qrc:/Pages/RefugeDirectory.qml'
        lock_orientation: false
    }
    ListElement {
        title: qsTr('Torch')
        icon: ''
        source: 'qrc:/Pages/Torch.qml'
        lock_orientation: false
    }
    ListElement {
        title: qsTr('Person Counter')
        icon: ''
        source: 'qrc:/Pages/PersonCounter.qml'
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
