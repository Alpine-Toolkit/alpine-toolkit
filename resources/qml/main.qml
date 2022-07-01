/***************************************************************************************************
 *
 * This file is part of the Alpine Toolkit software.
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 * SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

import QtQml.Models 2.2
import QtQuick 2.6

import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

import 'qrc:/js/android_permission.js' as AndroidPermission // Fixme: to module ?
import Constants 1.0
import Widgets 1.0 as Widgets

ApplicationWindow {
    id: application_window
    objectName: 'application_window'
    title: 'Alpine Toolkit'
    visible: true

    // Overwriting binding on QQuickApplicationWindow_QML_26::_stack_view_stack at qrc:/qml/main.qml:169 that was initially bound at qrc:/qml/main.qml:43:36
    property string _application_title: 'Alpine Toolkit'
    property var _stack_view_stack: []
    property var _stack_view_history: []

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
        console.info(
            "Screen info:",
            Screen.height, Screen.width,
            Screen.desktopAvailableHeight, Screen.desktopAvailableWidth,
            Screen.pixelDensity, Screen.devicePixelRatio
        )

	if (platform_abstraction.on_android() || platform_abstraction.on_android_fake()) {
	    AndroidPermission.create_explain_permission_dialog()
	}
    }

    Widgets.About {
        id: about_dialog
        // must be child of the application window
    }

    // Widgets.ExplainPermission {
    //     id: explain_permission_dialog
    //     // must be child of the application window
    // }

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
            spacing: Style.spacing.large_horizontal
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
                font.pixelSize: Style.font_size.huge
                elide: Label.ElideRight
                color: 'white'
                text: _application_title
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

        DelegateModel{
            id: page_delegate_model

            delegate: ItemDelegate {
	        id: control // item_menu_delegate
                width: parent.width
                font.pixelSize: Style.font_size.large
                text: model.title
	        // Try to get a smaller spacing
	        topPadding: 0
	        bottomPadding: 0
	        contentItem: Row {
		    spacing: Style.spacing.base_horizontal
 		    Image {
		        // fillMode: Image.Pad
		        // horizontalAlignment: Image.AlignHCenter
		        // verticalAlignment: Image.AlignVCenter
		        anchors.verticalCenter: parent.verticalCenter
		        source: model.icon
		    }
		    Label {
		        text: control.text
		        font: control.font
		        // verticalAlignment: Text.AlignVCenter
		        anchors.verticalCenter: parent.verticalCenter
		    }
	        }
                onClicked: {
                    // if (list_view.currentIndex != index) {
                    //     list_view.currentIndex = index
                    if (!is_current_page(model)) {
                        if (model.require_storage === true && !application.config.is_storage_enabled)
                            XXX_show_dialog()
                        else
                            replace_page(model)
                    }
                    drawer.close()
                }
            }

            model: PageModel {}

            groups: [
                DelegateModelGroup {
                    includeByDefault: false
                    name: 'enabled'
                }
            ]
            filterOnGroup: 'enabled'

            Component.onCompleted: {
                console.info("Insert pages...")
                for (var i = 0; i < items.count; i++) {
                    var item = items.get(i)
                    var page = item.model
                    if (page.group !== undefined)
                        if ((page.group == 'main') ||
                            (page.group == 'mockup' && application.config.is_mockup_enabled))
                            item.inEnabled = true
                }
            }
        }

        ListView {
            id: list_view
            // currentIndex: -1
            anchors.fill: parent
	    spacing: 0

            model: page_delegate_model
            ScrollIndicator.vertical: ScrollIndicator {}
        }
    }

    StackView {
        id: stack_view
        anchors.fill: parent

        initialItem: Widgets.SplashScreen {}
    }

    function is_current_page(page) {
        var stack_size = _stack_view_stack.length
        return stack_size > 0 && _stack_view_stack[stack_size -1].source == page.source
    }

    function replace_page(page) {
        _stack_view_stack = []
        var data = {source: page.source, title: page.title}
        _stack_view_stack.push(data) // {page: page}

        data = {source: page.source}
        _stack_view_history.push({action: 'replace', data: data})

        title_label.text = page.title
        platform_abstraction.orientation_lock = page.lock_orientation
        var item = stack_view.replace(page.source)
        update_options_menu(item)

        return item
    }

    function push_page(page, properties) {
        if ('title' in page)
            title_label.text = page.title
        var title = title_label.text

        var data = {source: page.source, title: title} // , properties:properties
        _stack_view_stack.push(data) // Fixme: contains model data ... ???
        _stack_view_history.push({action: 'push', data: data})

        properties = properties !== undefined ? properties : {}
        var item = stack_view.push(page.source, properties, StackView.Transition)
        update_options_menu(item)

        return item
    }

    function pop_page() {
        _stack_view_stack.pop()
        _stack_view_history.push({action: 'pop'})

        var stack_size = _stack_view_stack.length
        if (stack_size > 0)
            title_label.text = _stack_view_stack[stack_size -1].title
        else
            title_label.text = _application_title
        var item = stack_view.pop(StackView.Transition)
        update_options_menu(item)

        return item
    }

    function update_options_menu(item) {
        // Fixme: don't work ???
        // var has_settings = typeof item.settings_dialog !== 'undefined'
        // Fixme Qt6: TypeError: Property 'has_settings_dialog' of object SplashScreen is not a function
        var has_settings = item.has_settings_dialog()
        options_menu.enable_settings_menu(has_settings)
    }

    onClosing: {
        // Fixme: get item status ?
        console.info('Close windows\n' + JSON.stringify(_stack_view_stack) + '\n ' + JSON.stringify(_stack_view_history))
    }
}
