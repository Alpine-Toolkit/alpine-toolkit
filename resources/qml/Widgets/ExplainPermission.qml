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

import QtQml 2.2
import QtQuick 2.6

import QtQuick.Controls 2.2

import Constants 1.0
import Widgets 1.0 as Widgets

// Fixme: qrc:qml/Widgets/ExplainPermission.qml:34:1: QML ExplainPermission: Binding loop detected for property "implicitWidth"

Widgets.Dialog {
    id: dialog

    title: qsTr('An Android Permission is Required')
    standardButtons: Dialog.Cancel | Dialog.Ok

    property string permission;

    signal accepted_permission(string permission)
    signal rejected_permission(string permission)

    function ask(permission, explain_text) {
        var common_text = qsTr('<p><strong>Do you want to proceed ?</strong></p>');
        dialog.permission = permission;
 	text_area.text = qsTr(explain_text) + common_text;
 	open();
    }

    contentItem: Flickable {
        id: flickable
        // anchors.fill: parent

        TextArea.flickable: TextArea {
            id: text_area
            font.pointSize: Style.font_size.base
            readOnly: true
            text: ''
            textFormat: TextEdit.RichText
            wrapMode: Text.WordWrap

            background: null // suppress bottom line

            onLinkActivated: Qt.openUrlExternally(link)
            // Fixme: hover style
            // http://doc.qt.io/qt-5/richtext-html-subset.html
            // :hover is not supported
        }

        ScrollBar.vertical: ScrollBar { }
    }

    onAccepted: accepted_permission(dialog.permission)
    onRejected: rejected_permission(dialog.permission)
}
