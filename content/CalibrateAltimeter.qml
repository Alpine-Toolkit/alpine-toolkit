import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1

Item {
    width: parent.width
    height: parent.height

    property real progress: 0

    SequentialAnimation on progress {
        loops: Animation.Infinite
        running: true
        NumberAnimation {
            from: 0
            to: 1
            duration: 3000
        }
        NumberAnimation {
            from: 1
            to: 0
            duration: 3000
        }
    }

    TextField {
        id: altitude_text_field
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 30
        anchors.bottomMargin: 30
        validator: IntValidator {bottom: 0; top: 11000;}
    }

    Button {
        id: set_altitude_button
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: altitude_text_field.bottom
        anchors.topMargin: 30
        anchors.bottomMargin: 30
        text: "Set"
        onClicked: {
            pressure_sensor.reading.altitude = altitude_text_field.value; // undefined
            stack_view.pop();
        }
    }

}
