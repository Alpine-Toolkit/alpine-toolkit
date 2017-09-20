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

var explain_permission_dialog_component = Qt.createComponent('qrc:Widgets/ExplainPermission.qml');
var explain_permission_dialog = null;

var explain_texts = {
    // Fixme: better place ?
    'WRITE_EXTERNAL_STORAGE':
        '<p>The permission to read and write the external storage is required ' +
        'in order to write permanent data and access an external sdcard on your device.<p> ' +
        '<p>The application will create a top directory named <strong>alpine-toolkit</strong> ' +
        'at the root of the primary external storage, where it will store all the data. ' +
        '<strong>This directory will remain if you uninstall the application.</strong></p> ' +
        '<p>If you need more space on your device, you can later move this directory to an external sdcard.</p>'
};

function create_explain_permission_dialog()
{
    console.info("create_explain_permission_dialog");
    if (explain_permission_dialog_component.status == Component.Ready)
	finish_explain_permission_dialog();
    else
	explain_permission_dialog_component.statusChanged.connect(finish_explain_permission_dialog);
}

function finish_explain_permission_dialog()
{
    console.info("finish_explain_permission_dialog");
    if (explain_permission_dialog_component.status == Component.Ready) {
	var properties = {
	    id: 'explain_permission_dialog'
	}
	explain_permission_dialog = explain_permission_dialog_component.createObject(application_window, properties);
	explain_permission_dialog.accepted_permission.connect(on_accepted_explain_permission)
        explain_permission_dialog.rejected_permission.connect(on_rejected_explain_permission)
        platform_abstraction.on_permission_granted.connect(on_permission_granted)
        platform_abstraction.on_permission_denied.connect(on_permission_denied)
	if (platform_abstraction.on_android()) {
            AndroidPermission.check_permissions();
	} else if (platform_abstraction.on_linux()) {
            AndroidPermission.check_permissions_mockup();
        }
    } else {
	// Fixme: 
    }
}

function check_permissions()
{
    var need_grant = platform_abstraction.need_grant();
    var i;
    for (i = 0; i < need_grant.length; i++) {
	// platform_abstraction.(need_grant[i]);
    }

    var need_explain = platform_abstraction.need_explain();
    open_explain_permission(need_explain[0]);
}

function check_permissions_mockup()
{
    open_explain_permission('WRITE_EXTERNAL_STORAGE');
}

function open_explain_permission(permission_id)
{
    var explain_text = explain_texts[permission_id];
    explain_text += '<p><strong>Do you want to proceed ?</strong></p>';
    explain_permission_dialog.ask(permission_id, explain_text);
}

function on_accepted_explain_permission(permission)
{
    console.info("on_accepted_explain_permission " + permission);
    if (platform_abstraction.on_android()) {
        platform_abstraction.require_permission(permission);
    } else if (platform_abstraction.on_linux()) {
        platform_abstraction.emit_on_permission_granted(permission);
    }
}

function on_rejected_explain_permission(permission)
{
    console.info("on_rejected_explain_permission " + permission);
}

function on_permission_granted(permission)
{
    console.info("on_permission_granted " + permission);
}

function on_permission_denied(permission)
{
    console.info("on_permission_denied " + permission);
}
