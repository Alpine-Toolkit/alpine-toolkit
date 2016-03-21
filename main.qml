import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.3
import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0
import Qt.labs.settings 1.0

ApplicationWindow {
    id: application_window
    visible: true
    width: 360 // for desktop test
    height: 520
    title: "α Ursae Minoris"

    // Settings {
    //     id: settings
    //     property string style: "Material"
    // }

    // AndroidActivity {
    //     id: android_activity
    // }

    FontLoader { id: roboto_regular; source: "qrc:/fonts/Roboto-Regular.ttf" }
    font.family: roboto_regular.name

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

        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                id: nav_icon
                label: Image {
                    anchors.centerIn: parent
                    source: "qrc:/icons/menu-white.png"
                }
                onClicked: drawer.open()
            }

            Label {
                id: title_label
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                font.pixelSize: 20
                elide: Label.ElideRight
                color: "white"
                text: "α Ursae Minoris"
            }

            ToolButton {
                id: menu_icon
                label: Image {
                    anchors.centerIn: parent
                    source: "qrc:/icons/more-vert-white.png"
                }
                onClicked: options_menu.open()

                Menu {
                    id: options_menu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        text: "Settings"
                    }
                    MenuItem {
                        text: "About"
                        onTriggered: about_dialog.open()
                    }
                }
            }
        }
    }

    Drawer {
        id: drawer

        Pane {
            padding: 0
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
                    ListElement { title: qsTr("Altimeter"); source: "qrc:/pages/Altimeter.qml"; lock_orientation: false }
                    ListElement { title: qsTr("Inclination"); source: "qrc:/pages/Inclination.qml"; lock_orientation: true  }
                    ListElement { title: qsTr("Illuminance"); source: "qrc:/pages/Illuminance.qml"; lock_orientation: false  }
                    ListElement { title: qsTr("GPS"); source: "qrc:/pages/Gps.qml"; lock_orientation: true  }
                }

                ScrollIndicator.vertical: ScrollIndicator {}
            }
        }

        onClicked: close()
    }

    StackView {
        id: stack_view
        anchors.fill: parent

        initialItem: Pane {
            id: pane
            anchors.fill: parent

            Column {
                spacing: 20

                Label {
                    font.bold: true
                    text: "Main Page"
                }
            }
        }
    }

    Popup {
        id: about_dialog
        modal: true
        focus: true
        x: (application_window.width - width) / 2
        y: application_window.height / 6
        width: Math.min(application_window.width, application_window.height) / 3 * 2
        contentHeight: about_column.height
        closePolicy: Popup.OnEscape | Popup.OnPressOutside

        Column {
            id: about_column
            spacing: 20

            Label {
                font.bold: true
                text: "About"
            }

            Label {
                width: about_dialog.availableWidth
                wrapMode: Label.Wrap
                font.pixelSize: 12
                text: "Lorem lipsum ..."
            }
        }
    }
}
