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

import QtMultimedia 5.5

import "qrc:Widgets" as Widgets

Widgets.Page {
    id: camera_pane

    //color: "black"

    state: "PhotoCapture"
    states: [
        State {
            name: "PhotoCapture"
            StateChangeScript {
                script: {
                    camera.captureMode = Camera.CaptureStillImage
                    camera.start()
                }
            }
        },
        State {
            name: "PhotoPreview"
        } //,
        // State {
        //     name: "VideoCapture"
        //     StateChangeScript {
        //         script: {
        //             camera.captureMode = Camera.CaptureVideo
        //             camera.start()
        //         }
        //     }
        // },
        // State {
        //     name: "VideoPreview"
        //     StateChangeScript {
        //         script: {
        //             camera.stop()
        //         }
        //     }
        // }
    ]

    Row {
        id: camera_toolbox
        x: 0
        y: 0
        width: parent.width
        height: 100

        Button {
            onClicked: {
                if (camera.lockStatus == Camera.Unlocked) {
                    camera.searchAndLock();
                } else {
                    camera.unlock();
                }
            }

            text: {
                if (camera.lockStatus == Camera.Unlocked) {
                    "Focus";
                } else if (camera.lockStatus == Camera.Searching) {
                    "Focusing"
                } else {
                    "Unlock"
                }
            }
        }

        Button {
            text: "Capture"
            visible: camera.imageCapture.ready
            onClicked: camera.imageCapture.capture()
        }
    }

    Camera {
        id: camera
        captureMode: Camera.CaptureStillImage

        // exposure {
        //     exposureCompensation: -1.0
        //     exposureMode: Camera.ExposurePortrait
        // }

        // flash.mode: Camera.FlashRedEyeReduction

        imageCapture {
            onImageCaptured: {
                photo_preview.source = preview // Show the preview in an Image
                // stillControls.previewAvailable = true
                camera_pane.state = "PhotoPreview"
            }
        }

        videoRecorder {
           // resolution: "1920x1080"
           frameRate: 30
        }
    }

    VideoOutput {
        id: view_finder
        // anchors.fill: parent
        x: 0
        y: camera_toolbox.height
        width: parent.width
        height: parent.height - camera_toolbox.height

        visible: camera_pane.state == "PhotoCapture" // || cameraUI.state == "VideoCapture"
        focus : visible // to receive focus and capture key events when visible

        source: camera
        autoOrientation: true
    }

    // PhotoPreview
    Item {
        id : photo_preview

        // anchors.fill : parent
        x: 0
        y: camera_toolbox.height
        width: parent.width
        height: parent.height - camera_toolbox.height

        visible: camera_pane.state == "PhotoPreview"
        focus: visible

        property alias source : preview.source
        signal closed

        onClosed: camera_pane.state = "PhotoCapture"

        Image {
            id: preview
            anchors.fill : parent
            fillMode: Image.PreserveAspectFit
            smooth: true
        }

        MouseArea {
            anchors.fill: parent
            onClicked: parent.closed()
        }
    }
}
