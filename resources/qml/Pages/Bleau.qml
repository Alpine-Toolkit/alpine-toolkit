/***************************************************************************************************
 *
 * This file is part of the Alpine Toolkit software.
 * Copyright (C) 2017 Fabrice Salvaire
 * Contact: http://www.fabrice-salvaire.fr
 * SPDX-License-Identifier: GPL-3.0-only
 *
 **************************************************************************************************/

import QtQml 2.2
import QtQuick 2.6

import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

// import QtSensors 5.1

import Constants 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: bleau_pane

    // Component.onCompleted: {
    // }

  Component {
        id: section_heading
        Rectangle {
            width: bleau_pane.width
            height: childrenRect.height

            Label {
                font.bold: true
                font.pixelSize: 20
                text: section
            }
        }
    }

    ListView {
        id: list_view
        anchors.fill: parent
        model: massif_model
        delegate: ItemDelegate {
            width: parent.width
            font.pixelSize: 12
            text: model.name
            onClicked: {
                application_toolbar.state = 'BACK'
                nav_icon.visible = false
                back_icon.visible = true
                var properties = {'model': refuge_model[model.index]}
                // stack_view.push('qrc:/qml/Pages/BleauMassif.qml', properties, StackView.Transition)
            }
        }

        section.property: 'name'
        section.criteria: ViewSection.FirstCharacter
        // section.property: 'first_letter'
        // section.criteria: ViewSection.FullString
        section.delegate: section_heading
    }
}
