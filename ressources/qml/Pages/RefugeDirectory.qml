import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1

import QtSensors 5.1

import "qrc:Widgets" as Widgets

Widgets.Page {
    id: refuge_directory_pane

  Component {
        id: section_heading

        Rectangle {
            width: refuge_directory_pane.width
            height: childrenRect.height

            Label {
                font.bold: true
                font.pixelSize: 20
                text: section
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true

	    TextField {
                id: search_textfield
                Layout.fillWidth: true
                placeholderText: qsTr('Search')
                onTextChanged: search()
                onPressed: search()
	    }

	    ToolButton {
                id: clear_icon
                visible: search_textfield.text
                contentItem: Image {
		    fillMode: Image.Pad
		    horizontalAlignment: Image.AlignHCenter
		    verticalAlignment: Image.AlignVCenter
		    source: 'qrc:/icons/clear-black.png'
                }
                onClicked: search_textfield.clear()
	    }

	    ToolButton {
                id: gps_icon
                checkable: true
                contentItem: Image {
		    fillMode: Image.Pad
		    horizontalAlignment: Image.AlignHCenter
		    verticalAlignment: Image.AlignVCenter
		    source: gps_icon.checked ?
                        'qrc:/icons/gps-fixed-black.png' :
                        'qrc:/icons/gps-not-fixed-black.png'
                }
                // onClicked: {}
	    }
        }

        ListView {
            id: list_view
            Layout.fillHeight: true
            Layout.fillWidth: true

            model: refuge_schema_manager.refuges

            delegate: ItemDelegate {
                width: parent.width
                font.pixelSize: 12
                text: model.name
                onClicked: {
                    var properties = {'model': list_view.model[model.index]}
                    application_window.push_page('qrc:/Pages/Refuge.qml', properties)
                }
            }

            section.property: 'first_letter'
            // FirstLetter considers diacritic as different letters
            section.criteria: ViewSection.FullString
            section.delegate: section_heading
        }
    }

    Widgets.Popup {
        id: settings_dialog

        Text {
            text: "foo bar"
        }
    }

    function search() {
        refuge_schema_manager.filter_refuge_list(search_textfield.text)
    }
}
