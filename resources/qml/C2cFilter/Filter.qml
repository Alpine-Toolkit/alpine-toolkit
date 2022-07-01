/***************************************************************************************************
**
** This file is part of the Alpine Toolkit software.
** Copyright (C) 2017 Fabrice Salvaire
** Contact: http://www.fabrice-salvaire.fr
** SPDX-License-Identifier: GPL-3.0-only
**
**************************************************************************************************/

import QtQuick 2.6

import QtQuick.Controls 2.0

import Constants 1.0

Column {
    property string title: ''

    anchors.horizontalCenter: parent.horizontalCenter
    width: parent.width

    spacing: Style.spacing.base

    Rectangle {
	width: parent.width
	height: 1
	color: 'black'
    }

    Text {
	id: title_label
	anchors.horizontalCenter: parent.horizontalCenter
	text: title
    }
}
