import QtPositioning 5.5
import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1
import QtSensors 5.1

ApplicationWindow {
    id: application_window
    visible: true
    width: 1280
    height: 800
    title: "Sensors"

    Component.onCompleted: {
        var types = QmlSensors.sensorTypes();
        console.log(types.join(", "));

        // console.log("pressure_sensor availableDataRates", pressure_sensor.availableDataRates);

        // QAccelerometer
        // QAmbientLightSensor
        // QCompass
        // QGyroscope
        // QLightSensor
        // QMagnetometer
        // QOrientationSensor
        // QPressureSensor
        // QProximitySensor
        // QRotationSensor
        // QTiltSensor
    }

    // Temperature

//    Altimeter {
//        // doesn't work
//        id: altimeter
//        // dataRate: 100 // Hz
//        active: true
//        onReadingChanged: {
//            var altitude = altimeter.reading.altitude;
//            console.info(altitude);
//        }
//    }
//
//    PressureSensor {
//        id: pressure_sensor
//        active: true
//        onReadingChanged: {
//            var pressure = pressure_sensor.reading.pressure; // 82500 Pa
//            var temperature = pressure_sensor.reading.temperature; // 0
//            pressure_label.text = pressure + " Pa";
//            console.info(pressure, temperature);
//        }
//    }
//
//    TiltSensor {
//        // calibration
//        id: tilt_sensor
//        active: true
//        // Calibrates the tilt sensor. Uses the current tilt angles as 0.
//        onReadingChanged: {
//            var x_rotation = tilt_sensor.reading.xRotation;
//            var y_rotation = tilt_sensor.reading.yRotation;
//            x_tilt_label.text = x_rotation;
//            y_tilt_label.text = y_rotation;
//            console.info(x_rotation, y_rotation);
//        }
//    }
//
//    Compass {
//        // calibration
//        id: compass
//        active: true
//        onReadingChanged: {
//            var azimuth = compass.reading.azimuth;
//            var calibration_level = compass.reading.calibrationLevel;
//            azimuth_label.text = azimuth;
//            console.info(azimuth, calibration_level);
//        }
//    }

    PositionSource {
        id: position_source
        updateInterval: 1000
        active: true

        onPositionChanged: {
            var coordinate = position_source.position.coordinate;
            position_label.text = coordinate.longitude + " " + coordinate.latitude + " " + position_source.position.horizontalAccuracy + " / " + coordinate.altitude;
            console.log("Coordinate:", coordinate.longitude, coordinate.latitude);
        }
    }

    GridLayout {
        id: grid
        anchors.fill: parent
        columns: 2

        Text { text: "Pressure" }
        Text { id: pressure_label }
        Text { text: "Azimuth" }
        Text { id: azimuth_label }
        Text { text: "X Tilt" }
        Text { id: x_tilt_label }
        Text { text: "Y Tilt" }
        Text { id: y_tilt_label }
        Text { text: "Position" }
        Text { id: position_label }

    }
}
