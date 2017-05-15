import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import QtQuick.Controls 2.1

import QtSensors 5.1


Pane {
    id: refuge_directory_pane

    // Component.onCompleted: {
    //     console.info('Refuge Model:', refuge_model);
    // }

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
                onPressed: search()
                onTextChanged: search()
	    }

	    ToolButton {
                id: search_icon
                contentItem: Image {
		    fillMode: Image.Pad
		    horizontalAlignment: Image.AlignHCenter
		    verticalAlignment: Image.AlignVCenter
		    source: 'qrc:/icons/search-black.png'
                }
                onClicked: search()
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
                onClicked: {
                }
	    }
        }

        ListView {
            id: list_view
            Layout.fillHeight: true
            Layout.fillWidth: true

            // model: refuge_model // ok
            // model: refuge_schema_manager.refuges_as_object_list() // model.name -> Unable to assign [undefined] to QString
            // model: refuge_schema_manager.refuges_as_object_list_variant() // idem
            // model: refuge_schema_manager.model() // ok
            // model: refuge_schema_manager_model // ok
            model: refuge_schema_manager.refuges // ok

            delegate: ItemDelegate {
                width: parent.width
                font.pixelSize: 12
                text: model.name
                onClicked: {
                    var properties = {'model': refuge_model[model.index]}
                    console.info("refuge " + properties)
                    application_window.push_page("qrc:/Pages/Refuge.qml", properties)
                }
            }

            section.property: "first_letter"
            // FirstLetter considers diacritic as different letters
            section.criteria: ViewSection.FullString
            section.delegate: section_heading
        }
    }

    function search() {
        console.info("Search " + search_textfield.text)
        refuge_schema_manager.filter_refuge_list(search_textfield.text)
    }
}
