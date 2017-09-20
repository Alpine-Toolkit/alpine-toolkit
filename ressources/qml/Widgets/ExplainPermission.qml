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

Dialog {
    id: dialog
    modal: true

    // cf. Popup.qml
    property real factor: .9
    width: parent.width * factor
    height: parent.height * factor
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

    title: qsTr("An Android Permission is Required")
    standardButtons: Dialog.Cancel | Dialog.Ok

    property string permision_id;

    signal accepted_permission(string permission_id)
    signal rejected_permission(string permission_id)

    function ask(permision_id, explain_text) {
        dialog.permision_id = permision_id;
 	text_area.text = qsTr(explain_text);
 	open();
    }

    contentItem: Flickable {
        id: flickable
        // anchors.fill: parent

        TextArea.flickable: TextArea {
            id: text_area
            font.pointSize: 12
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

    onAccepted: accepted_permission(dialog.permission_id)
    onRejected: rejected_permission(dialog.permission_id)
}
