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
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0

// import QtSensors 5.1

import "qrc:Widgets" as Widgets

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
                application_toolbar.state = "BACK"
                nav_icon.visible = false
                back_icon.visible = true
                var properties = {'model': refuge_model[model.index]}
                // stack_view.push("qrc:/Pages/BleauMassif.qml", properties, StackView.Transition)
            }
        }

        section.property: "name"
        section.criteria: ViewSection.FirstCharacter
        // section.property: "first_letter"
        // section.criteria: ViewSection.FullString
        section.delegate: section_heading
    }
}
