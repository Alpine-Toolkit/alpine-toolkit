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
import "qrc:/js/camptocamp_definitions.js" as C2cDefinitions

Widgets.Page {
    id: camptocamp_route_pane

    property var route: null

    ListModel { id: image_model }

    function format_activity_list(activities) {
        var activity_glyphs = [];
        activities.forEach(function (activity) {
            activity_glyphs.push(C2cDefinitions.activity_dict[activity].glyph)
        });
        return activity_glyphs.join(' ');
    }

    function format_rating(route) {
        var string = '%1 %2 > %3 %4 %5 %6';
        string = string.arg(route.global_rating);
        string = string.arg(route.rock_free_rating);
        string = string.arg(route.rock_required_rating);
        string = string.arg(route.engagement_rating);
        string = string.arg(route.equipment_rating);
        string = string.arg(route.exposition_rock_rating);
        return string;
    }

    Component.onCompleted: {
        /* console.info("camptocamp route pane\n" + route.to_json_string()); */
        compass_rose.set_state(route.orientations);
        // web_view.loadHtml(route.description("fr"), '');
        /* route.images.forEach(function (image) { */
        /*     console.info("Image", image.filename); */
        /* }); */
        var images = route.images
        for (var i = 0; i < images.length; i++) {
	    var image = images[i];
            console.info("Load image", image.filename);
            image_model.append({"filename": image.filename, "loaded": false}); // Fixme:
            c2c_client.media(image.filename);
        }
    }

    Connections {
        target: c2c_client
        onReceivedMedia: {
            // busy_indicator.running = false;
            console.info('Received image ' + media);
            c2c_client.save_media(media);
            for (var i = 0; i < image_model.count; i++) {
	        var image = image_model.get(i);
                if (image.filename == media) {
                    image_model.setProperty(i, "loaded", true);
                }
            }
        }
    }

    Column {
        id: header
        anchors.top: parent.top
        width: parent.width

        Row {
            width: parent.width
            layoutDirection: Qt.RightToLeft

            // BusyIndicator {
            //     id: busy_indicator
            //     running: true
            // }

            ToolButton {
                id: download_icon
                contentItem: Image {
                    id: download_icon_image
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: c2c_client.is_document_cached(route.id) ? "qrc:/icons/cloud-done-black.png" : "qrc:/icons/cloud-download-black.png"
                }
                // Fixme: cached / update
                onClicked: {
                    c2c_client.save_document(route.id)
                    // Fixme:
                    download_icon_image.source = c2c_client.is_document_cached(route.id) ? "qrc:/icons/cloud-done-black.png" : "qrc:/icons/cloud-download-black.png"
                }
            }
        }

        Label {
            id: title
            width: parent.width
            font.pointSize: 20
            font.bold: true
            wrapMode: Text.WordWrap
            text: route.title("fr")
        }
    }

    SwipeView {
        id: swipe_view
        anchors.top: header.bottom
        width: parent.width
        height: parent.height - header.height - page_indicator.height
        currentIndex: 0

        Pane {
            Label {
                id: description_label
                anchors.top: parent.top
                font.pointSize: 18
                font.bold: true
                text: 'Description'
            }

            Flickable {
                id: flickable
                // anchors.fill: parent
                anchors.top: description_label.bottom
                width: parent.width
                height: parent.height - description_label.height

                TextArea.flickable: TextArea {
                    id: description
                    font.pointSize: 12
                    readOnly: true
                    text: route.description("fr")
                    textFormat: TextEdit.RichText
                    wrapMode: Text.WordWrap

                    background: null // suppress bottom line
                }

                ScrollBar.vertical: ScrollBar { }
            }
        }

        Pane {
            Label {
                id: information_label
                anchors.top: parent.top
                anchors.bottomMargin: 10
                font.pointSize: 18
                font.bold: true
                text: 'Information'
            }

            Flickable {
                anchors.top: information_label.bottom
                width: parent.width
                height: parent.height - information_label.height
                contentHeight: information_container.height
                clip: true

                Grid {
                    id: information_container
                    width: parent.width
                    columns: 2
                    columnSpacing: 10
                    rowSpacing: 10
                    verticalItemAlignment: Grid.AlignVCenter

                    Label {
                        font.pointSize: 16
                        text: 'General'
                    }
                    Column {
                        spacing: 5

                        Label {
                            text: 'Route types: ' + route.route_types.join(', ')
                        }
                        Row {
                            spacing: 10
                            Label {
                                text: 'Activities'
                            }
                            Label {
                                font.family: activities_font.name
                                font.pointSize: 16
                                text: format_activity_list(route.activities)
                            }
                        }
                        Label {
                            text: 'Durations: 1 day(s)'
                        }
                        Label {
                            text: 'Rock types: ' + route.rock_types.join(', ')
                        }
                        Label {
                            text: 'Climbing outdoor type: ' + route.climbing_outdoor_type
                        }
                        Label {
                            text: 'Configuration: ' + route.configuration.join(', ')
                        }
                        Label {
                            text: 'Completeness: ' + route.quality
                        }
                        // Label {
                        //     text: 'Download track as'
                        // }
                    }

                    Label {
                        font.pointSize: 16
                        text: 'Heights'
                    }
                    Column {
                        spacing: 5

                        Label {
                            text: 'Elevation min/max : %1 m / %2 m'.arg(route.elevation_min).arg(route.elevation_max)
                        }
                        Label {
                            text: 'Elevation loss: %1 m'.arg(0) // Fixme: height_diff_difficulties height_diff_up ???
                        }
                        Label {
                            text: 'Difficulties height difference: %1 m'.arg(route.height_diff_difficulties)
                        }
                    }

                    Label {
                        font.pointSize: 16
                        text: 'Rating'
                    }
                    Label {
                        // 'TD- 6a+ > 6aA0 II P1 E1'
                        text: format_rating(route) // Fixme: A0 ???
                    }

                    Label {
                        font.pointSize: 16
                        text: 'Orientations'
                    }
                    Widgets.CompassRose {
                        id: compass_rose
                        radius: 100
                    }

                    // Label {
                    //     font.pointSize: 16
                    //     text: 'License'
                    // }
                    // Label {
                    //     text: '...'
                    // }

                    // Label {
                    //     font.pointSize: 16
                    //     text: 'Maps'
                    // }
                    // Label {
                    //     text: '...'
                    // }
                }
            }
        }

        // Pane {
        //     WebView {
        //         id: web_view
        //         anchors.fill: parent
        //     }
        // }


        Pane {
            ListView {
                id: media_list_view
                width: parent.width
                height: parent.height
                model: image_model
                delegate: ItemDelegate {
                    width: media_list_view.width
                    height: media_list_view.height

                    Column {
                        width: parent.width
                        height: parent.height

                        Image {
                            visible: loaded
                            source: loaded ? "image://c2c/" + filename : null
                            width: parent.width
                            height: parent.height
                            fillMode: Image.PreserveAspectFit
                            smooth: true
                        }

                        BusyIndicator {
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            running: loaded == false
                            visible: running
                        }
                    }

                    onClicked: {
                        console.info("clicked on media", filename);
                        var properties = { 'media': filename };
                        push_page('qrc:/Pages/CamptocampMedia.qml', properties);
                    }
                }
                clip: true
                orientation: ListView.Vertical
                snapMode: ListView.SnapToItem
                ScrollBar.vertical: ScrollBar { }
            }
        }

        // Pane {
        //     // Remarks
        //     // Gear
        //     // Route history
        //     // external ressources
        // }

        // Pane {
        //     // Associated waypoints
        // }

        // Pane {
        //     // Last outings
        // }
    }

    PageIndicator {
        id: page_indicator
        anchors.top: swipe_view.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        count: swipe_view.count
        currentIndex: swipe_view.currentIndex
    }
}
