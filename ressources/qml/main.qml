import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

// import Widgets 1.0 // Fixme: don't work
import "qrc:Widgets" as Widgets
import "qrc:Pages" as Pages

ApplicationWindow {
    id: application_window
    objectName: "application_window"
    title: 'Alpine Toolkit'
    visible: true

    property var stack_view_stack: []
    property var stack_view_history: []

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

    Widgets.About {
        id: about_dialog
        // must be child of the application window
    }

    Widgets.OptionsMenu {
        id: options_menu
        about_dialog: about_dialog

        function open_settings_dialog() {
            var current_item = stack_view.currentItem
            if (typeof current_item.open_settings_dialog !== 'undefined')
                current_item.open_settings_dialog()
        }
    }

    header: ToolBar {
        id: application_toolbar

        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                id: nav_icon
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: stack_view.depth > 1 ?
                        'qrc:/icons/arrow-back-white.png' :
                        'qrc:/icons/menu-white.png'
                }
                onClicked: {
                    if (stack_view.depth > 1)
                        pop_page()
                    else
                        drawer.open()
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
                        replace_page(model)
                    }
                    drawer.close()
                }
            }

            model: Pages.PageModel {}
            ScrollIndicator.vertical: ScrollIndicator {}
        }
    }

    StackView {
        id: stack_view
        anchors.fill: parent

        initialItem: Widgets.SplashScreen {}
    }

    function replace_page(model) {
        title_label.text = model.title
        if (on_android)
            android_activity.orientation_lock = model.lock_orientation
        stack_view_stack = []
        var data = {page: model.source}
        stack_view_stack.push(data) // {model:model}
        stack_view_history.push({action: 'replace', data: data})
        var item = stack_view.replace(model.source)
        update_options_menu(item)
        return item
    }

    function push_page(url, properties) {
	properties = properties !== undefined ? properties : {}
        var data = {url:url} // , properties:properties
        stack_view_stack.push(data) // Fixme: contains model data ... ???
        stack_view_history.push({action: 'push', data: data})
        var item = stack_view.push(url, properties, StackView.Transition)
        update_options_menu(item)
        return item
    }

    function pop_page() {
        stack_view_stack.pop()
        stack_view_history.push({action: 'pop'})
        var item = stack_view.pop(StackView.Transition)
        update_options_menu(item)
        return item
    }

    function update_options_menu(item) {
        var has_settings = typeof item.open_settings_dialog !== 'undefined'
        options_menu.enable_settings(has_settings)
    }

    onClosing: {
        // Fixme: get item status ?
        console.info("Close windows\n" + JSON.stringify(stack_view_stack) + "\n " + JSON.stringify(stack_view_history))
    }
}
