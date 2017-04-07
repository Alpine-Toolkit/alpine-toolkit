import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

ApplicationWindow {
    id: application_window
    visible: true
    width: 360 // set window size for desktop test
    height: 520
    title: 'Alpine Toolkit'

    // Done in main.cpp
    // AndroidActivity {
    //     id: android_activity
    // }

    // Done by Material theme
    // FontLoader { id: roboto_regular; source: 'qrc:/fonts/Roboto-Regular.ttf' }
    // font.family: roboto_regular.name

    FontLoader { id: activities_font; source: 'qrc:/fonts/c2c-activities.ttf' } // name: icomoon

    Component.onCompleted: {
        // S5: 640 360 5535 3240 5.551839464882943 3
        // 5.1 in 1080 x 1920 px ~432 dpi
        // math.sqrt(1920**2+1080**2)/5.1 = 431.9425
        // 1920 - 75 px for android bar = 1845
        // 1080*3 = 3240   1845*3 = 5535
        // 5.551839464882943*3*25.4 = 423
        console.info(Screen.height, Screen.width,
                     Screen.desktopAvailableHeight, Screen.desktopAvailableWidth,
                     Screen.pixelDensity, Screen.devicePixelRatio);
    }

    header: ToolBar {
        id: app_bar

        states: [
        State { name: 'BACK' }
        ]

        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                id: nav_icon
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: 'qrc:/icons/menu-white.png'
                }
                onClicked: drawer.open()
            }

            ToolButton {
                id: back_icon
                visible: false
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: 'qrc:/icons/arrow-back-white.png'
                }
                onClicked: {
                    if (app_bar.state == 'BACK') {
                        app_bar.state == ''
                        back_icon.visible = false
                        nav_icon.visible = true
                    }
                    stack_view.pop(StackView.Transition)
                }
            }

            Label {
                id: title_label
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                font.pixelSize: 20
                elide: Label.ElideRight
                color: 'white'
                text: 'Alpine Toolkit'
            }

            ToolButton {
                id: menu_icon
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: 'qrc:/icons/more-vert-white.png'
                }
                onClicked: options_menu.open()

                Menu {
                    id: options_menu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        text: 'Settings'
                    }
                    MenuItem {
                        text: 'About'
                        onTriggered: about_dialog.open()
                    }
                }
            }
        }
    }

    Drawer {
        id: drawer
        width: Math.min(application_window.width, application_window.height) / 3 * 2
        height: application_window.height

        ListView {
            id: list_view
            currentIndex: -1
            anchors.fill: parent

            delegate: ItemDelegate {
                width: parent.width
                font.pixelSize: 16
                text: model.title
                highlighted: ListView.isCurrentItem
                onClicked: {
                    if (list_view.currentIndex != index) {
                        list_view.currentIndex = index
                        title_label.text = model.title
                        if (on_android) {
                            android_activity.orientation_lock = model.lock_orientation;
                        }
                        stack_view.replace(model.source)
                    }
                    drawer.close()
                }
            }

            model: ListModel {
                ListElement {
                    title: qsTr('Altimeter')
                    icon: ''
                    source: 'qrc:/pages/Altimeter.qml'
                    lock_orientation: false
                }
                ListElement {
                    title: qsTr('Bleau')
                    icon: ''
                    source: 'qrc:/pages/Bleau.qml'
                    lock_orientation: false
                }
                ListElement {
                    title: qsTr('Camptocamp')
                    icon: ''
                    source: 'qrc:/pages/Camptocamp.qml'
                    lock_orientation: false
                }
                ListElement {
                    title: qsTr('Check List')
                    icon: ''
                    source: 'qrc:/pages/Checklist.qml'
                    lock_orientation: false
                }
                ListElement {
                    title: qsTr('Ephemeride')
                    icon: ''
                    source: 'qrc:/pages/Ephemeride.qml'
                    lock_orientation: false
                }
                ListElement {
                    title: qsTr('Emergency')
                    icon: ''
                    source: 'qrc:/pages/Emergency.qml'
                    lock_orientation: false
                }
                ListElement {
                    title: qsTr('Inclination')
                    icon: ''
                    source: 'qrc:/pages/Inclination.qml'
                    lock_orientation: true
                }
                ListElement {
                    title: qsTr('Illuminance')
                    icon: ''
                    source: 'qrc:/pages/Illuminance.qml'
                    lock_orientation: false
                }
                ListElement {
                    title: qsTr('GPS')
                    icon: 'qrc:/icons/explore-black.png'
                    source: 'qrc:/pages/Gps.qml'
                    lock_orientation: true
                }
                ListElement {
                    title: qsTr('Lamp Signal')
                    icon: ''
                    source: 'qrc:/pages/LampSignal.qml'
                    lock_orientation: false
                }
                ListElement {
                    title: qsTr('Refuges')
                    icon: ''
                    source: 'qrc:/pages/RefugeDirectory.qml'
                    lock_orientation: false
                }
                ListElement {
                    title: qsTr('Torch')
                    icon: ''
                    source: 'qrc:/pages/Torch.qml'
                    lock_orientation: false
                }
                /*
                ListElement {
                    title: qsTr('Camera')
                    icon: ''
                    source: 'qrc:/pages/Camera.qml'
                    lock_orientation: false
                }
                ListElement {
                    title: qsTr('Heart Rate')
                    icon: ''
                    source: 'qrc:/pages/HeartRate.qml'
                    lock_orientation: false
                }
                ListElement {
                    title: qsTr('Chart')
                    icon: ''
                    source: 'qrc:/pages/Chart.qml'
                    lock_orientation: false
                }
                ListElement {
                    title: qsTr('UI Test')
                    icon: ''
                    source: 'qrc:/pages/UiTest.qml'
                    lock_orientation: false
                }
                */
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

    StackView {
        id: stack_view
        anchors.fill: parent

        initialItem: Pane {
            id: pane

            Image {
                anchors.centerIn: parent
                property int image_size: Math.min(parent.width, parent.height) * .9
                width: image_size
                height: image_size
                // source: 'asset:///application-icons/icon.svg'
                source: 'qrc:/application-icons/icon.svg'
                // property int image_size: Math.min(Math.min(parent.width, parent.height) * .9, 512)
                // source: 'qrc:/application-icons/icon-512.png'
            }
        }
    }

    function push_page(url, properties) {
	properties = properties !== undefined ? properties : {}
        app_bar.state = 'BACK'
        nav_icon.visible = false
        back_icon.visible = true
	console.info('push_page ' + url + ' ' + JSON.stringify(properties))
        return stack_view.push(url, properties, StackView.Transition)
    }

    Popup {
        id: about_dialog
        modal: true
        focus: true
        x: (application_window.width - width) / 2
        y: application_window.height / 6
        width: Math.min(application_window.width, application_window.height) / 3 * 2
        contentHeight: about_column.height
        // closePolicy: Popup.OnEscape | Popup.OnPressOutside

        Column {
            id: about_column
            spacing: 20

            Label {
                font.bold: true
                text: 'About'
            }

            Label {
                width: about_dialog.availableWidth
                wrapMode: Label.Wrap
                font.pixelSize: 12
                text: 'Lorem lipsum ...'
            }
        }
    }
}
