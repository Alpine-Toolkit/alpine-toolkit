/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

import QtQml 2.2
import QtQuick 2.6

import QtQuick.Controls 2.2

import Constants 1.0

// Fixme: qrc:qml/Widgets/ExplainPermission.qml:34:1: QML ExplainPermission: Binding loop detected for property "implicitWidth"

Dialog {
    id: dialog
    modal: true

    // cf. Popup.qml
    property real factor: .9
    width: parent.width * factor
    height: parent.height * factor
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2

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
