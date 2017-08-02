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
// import QtWebView 1.1

import "qrc:/Widgets" as Widgets

Widgets.Page {
    id: camptocamp_media_pane

    property string media: null

    property string image_url: "image://c2c/" + media

     // Image {
     //     id: image
     //     anchors.fill: parent
     //     // anchors.centerIn: parent
     //     fillMode: Image.PreserveAspectFit
     //     source: "image://c2c/" + media
     //     antialiasing: true
     // }

    Flickable {
        id: image_flickable
        anchors.fill: parent
        contentWidth: image_container.width
	contentHeight: image_container.height
        clip: true
        onHeightChanged: if (image_preview.status === Image.Ready) image_preview.fitToScreen()

        Item {
            id: image_container
	    // cannot be smaller than flickable
            width: Math.max(image_preview.width * image_preview.scale, image_flickable.width)
            height: Math.max(image_preview.height * image_preview.scale, image_flickable.height)

            Image {
                id: image_preview

                property real previous_scale

                function fitToScreen() {
                    scale = Math.min(image_flickable.width / width, image_flickable.height / height, 1)
		    console.info("fitToScreen " + scale, + " " + width + "x" + height)
                    pinchArea.min_scale = scale
                    previous_scale = scale
                }

                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
                cache: false
                asynchronous: true
                source: image_url
                // sourceSize.height: 1000;
                smooth: !image_flickable.moving

                onStatusChanged: {
                    if (status == Image.Ready) {
                        fitToScreen()
                        // loadedAnimation.start()
                    }
                }

                // NumberAnimation {
                //     id: loadedAnimation
                //     target: image_preview
                //     property: "opacity"
                //     duration: 250
                //     from: 0; to: 1
                //     easing.type: Easing.InOutQuad
                // }

                onScaleChanged: {
                    if ((width * scale) > image_flickable.width) {
                        var xoff = (image_flickable.width / 2 + image_flickable.contentX) * scale / previous_scale;
			console.info("onScaleChanged " + xoff);
                        image_flickable.contentX = xoff - image_flickable.width / 2
                    }
                    if ((height * scale) > image_flickable.height) {
                        var yoff = (image_flickable.height / 2 + image_flickable.contentY) * scale / previous_scale;
			console.info("onScaleChanged " + xoff);
                        image_flickable.contentY = yoff - image_flickable.height / 2
                    }
                    previous_scale = scale
                }
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                image_preview.scale *= 2
            }
            onDoubleClicked: {
                image_preview.fitToScreen()
            }
        }

        PinchArea {
            id: pinchArea

            property real min_scale: 1.0
            property real max_scale: 3.0

            anchors.fill: parent
            enabled: image_preview.status === Image.Ready
            pinch.target: image_preview
            pinch.minimumScale: min_scale * 0.5 // This is to create "bounce back effect"
            pinch.maximumScale: max_scale * 1.5 // when over zoomed

            onPinchFinished: {
                image_flickable.returnToBounds()
                if (image_preview.scale < pinchArea.min_scale) {
                    bounceBackAnimation.to = pinchArea.min_scale
                    bounceBackAnimation.start()
                }
                else if (image_preview.scale > pinchArea.max_scale) {
                    bounceBackAnimation.to = pinchArea.max_scale
                    bounceBackAnimation.start()
                }
            }

            NumberAnimation {
                id: bounceBackAnimation
                target: image_preview
                duration: 250
                property: "scale"
                from: image_preview.scale
            }
        }
    }
}
