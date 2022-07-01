/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

var explain_permission_dialog_component = Qt.createComponent('qrc:qml/Widgets/ExplainPermission.qml');
var explain_permission_dialog = null;

/**************************************************************************************************/

function create_explain_permission_dialog()
{
    console.info("create_explain_permission_dialog");
    var status = explain_permission_dialog_component.status;
    if (status == Component.Ready)
	finish_explain_permission_dialog();
    else if (status == Component.Ready) // usually here
	explain_permission_dialog_component.statusChanged.connect(finish_explain_permission_dialog);
    else
	console.error("create_explain_permission_dialog", explain_permission_dialog_component.errorString());
}

function finish_explain_permission_dialog()
{
    console.info("finish_explain_permission_dialog");
    if (explain_permission_dialog_component.status == Component.Ready) {
	var properties = {
	    id: 'explain_permission_dialog'
	}
	explain_permission_dialog = explain_permission_dialog_component.createObject(application_window, properties);
        var permission_manager = platform_abstraction.permission_manager;
        // permission manager -> js slots
        permission_manager.open_explain_permission.connect(explain_permission_dialog.ask);
	// dialog signals -> js slots
	explain_permission_dialog.accepted_permission.connect(permission_manager.on_accepted_explain_permission)
        explain_permission_dialog.rejected_permission.connect(permission_manager.on_rejected_explain_permission)
    } else {
	// Fixme: 
    }
}
