import QtQuick 2.0
import QtQuick.Controls 2.0

Dial {
    id: knob
//    anchors.centerIn: parent
    property real knobValue: 0.0
    from: 0
    to: 100
    value: knobValue * 100

    onValueChanged: {
        knobValue = value / 100.0
        knobQML.setValue(knobValue)
        console.log(knobValue)
    }
}
