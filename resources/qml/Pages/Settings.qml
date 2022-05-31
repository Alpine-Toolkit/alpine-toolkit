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
import QtQml.Models 2.2
import QtQuick 2.6

import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

import Constants 1.0
import Settings 1.0
import Widgets 1.0 as Widgets

Widgets.Page {
    id: settings_pane

    DelegateModel{
        id: page_delegate_model

        delegate: ItemDelegate {
	    id: control // item_menu_delegate
            width: parent.width
            font.pixelSize: 18
            text: model.title
	    // Try to get a smaller spacing
	    topPadding: 0
	    bottomPadding: 0
	    contentItem: Row {
		spacing: Style.spacing.base
 		Image {
		    anchors.verticalCenter: parent.verticalCenter
		    source: model.icon
		}
		Label {
		    text: control.text
		    font: control.font
		    anchors.verticalCenter: parent.verticalCenter
		}
	    }
            onClicked: {
                if (!is_current_page(model))
                    push_page(model)
            }
        }

        model: SettingsPageModel {}

        groups: [
            DelegateModelGroup {
                includeByDefault: false
                name: 'enabled'
            }
        ]
        filterOnGroup: 'enabled'

        Component.onCompleted: {
            var row_count = model.count
            items.remove(0, row_count)
            for (var i = 0; i < row_count; i++) {
                var page = model.get(i)
                if (page.group !== undefined)
                    if ((page.group == 'main'))
                        items.insert(page, 'enabled')
            }
        }
    }

    ListView {
        id: list_view
        anchors.fill: parent
	spacing: 0

        model: page_delegate_model
        ScrollIndicator.vertical: ScrollIndicator {}
    }
}
