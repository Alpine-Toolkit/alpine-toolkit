import QtQml 2.2
import QtQuick 2.6
import QtQuick.Window 2.2

import QtQuick.Layouts 1.1
import Qt.labs.controls 1.0

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

    ListView {
        id: list_view
        anchors.fill: parent
        model: refuge_model
        // model: sql_model
        delegate: ItemDelegate {
            width: parent.width
            font.pixelSize: 12
            text: model.name
            onClicked: {
                // model = QQmlDMObjectData(0x3f24860)
                app_bar.state = "BACK"
                nav_icon.visible = false
                back_icon.visible = true
                var properties = {'model': refuge_model[model.index]}
                // console.info(refuge_model, model.index, refuge_model.at(model.index));
                // var properties = {'model': refuge_model.at(model.index)}
                // var properties = {'model': {
                //     'altitude': model.altitude,
                //     'description': model.description,
                //     'guardian': model.guardian,
                //     'coordinate': {'latitude': model.latitude, 'longitude': model.longitude},
                //     'name': model.name,
                //     'phone': model.phone,
                //     'region': model.region
                // }};
                stack_view.push("qrc:/pages/Refuge.qml", properties, StackView.Transition)
            }
        }

        // section.property: "short_name"
        // section.criteria: ViewSection.FirstCharacter
        section.property: "first_letter"
        section.criteria: ViewSection.FullString
        section.delegate: section_heading
    }
}
