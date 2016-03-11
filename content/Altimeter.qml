import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import QtSensors 5.1
import QtCarto 1.0

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

    // Temperature

    // Altimeter {
    //     // doesn't work
    //     id: altimeter
    //     // dataRate: 100 // Hz
    //     active: true
    //     onReadingChanged: {
    //         var altitude = altimeter.reading.altitude;
    //         console.info(altitude);
    //     }
    // }

    // PressureSensor
    BarimeterAltimeterSensor {
        id: pressure_sensor
        // id: barimeter_altimeter_sensor
        active: true // ???

        function pressure_to_temperature(pressure) {
            // Freescale Semiconductor AN4528
            // Equation 1 is used for computing atmospheric pressure (P, in Pa) at a
            // different altitude (h, in m) below 11 km.
            //
            // P = P0 * (1 - (L0 – h)/P)^((g0 * M)/(R * L0))   Eqn. 1
            //
            // where:
            //
            // Symbol | Value     | Unit        | Description
            // P0     | 101,325   | kPa         | Sea-level standard atmospheric pressure
            // L0     | 0.0065    | K/m         | Temperature lapse rate from sea level to 11 km
            // T0     | 288.15    | K           | Sea-level standard temperature
            // g0     | 9.80665   | m/s^2       | Sea-level gravitational acceleration
            // M      | 0.0289644 | kg/mol      | Mean-molecular weight of air
            // R      | 8.31432   | N·m/(K·mol) | Universal gas constant
            //
            // By inserting these parameters into Equation 1, we get the simplified
            // Equation 2 for atmospheric-pressure calculation based on known
            // altitude.
            //
            // P = P0 * (1 - h/44330.77)^5.255876   Eqn. 2
            //
            // Equation 3 is used for altitude calculation based on known atmospheric
            // pressure after the conversion to Equation 2.
            //
            // h = 44330.77 * (1 - (P/P0)^0.190263)   Eqn. 3
            //
            // According to Equation 3, we can determine the altitude value with an
            // accurate atmospheric-pressure measurement.

            var P0 = 101325; // Pa Fixme: calibration
            var h0 = 40; // m IGN sea level
            return 44330.77 * (1 - Math.pow(pressure/P0, .190263)) - h0;
        }

        onReadingChanged: {
            // Mean Filter
            var pressure = pressure_sensor.reading.pressure; // 82500 Pa
            var temperature = pressure_sensor.reading.temperature; // 0
            var altitude = pressure_to_temperature(pressure);
            pressure_label.text = pressure + " Pa";
            altitude_label.text = altitude + " m";
            console.info(pressure, temperature, altitude);
        }
    }

    // TextField {
    //     anchors.top = parent.top;
    //     validator: IntValidator {bottom: 11; top: 31;}
    // }

    GridLayout {
        anchors.fill: parent
        anchors.leftMargin: 30
        columns: 2

        Text {
            color: "white"
            text: "Pressure"
        }
        Text {
            color: "white"
            id: pressure_label
        }

        Text {
            color: "white"
            text: "Altitude"
        }
        Text {
            color: "white"
            id: altitude_label
        }
    }
}
