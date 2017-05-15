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
