import QtQuick 2.14

Item {
    Flickable {
        id: flick
        anchors.fill: parent
        Row {
            id: row
            Item {
                width: flick.width / 4
                height: 10
            }
            Image {
                source: "qrc:/img.jpg"
                height: flick.height
                sourceSize.height: flick.height
            }
            Item {
                width: flick.width / 4
                height: 10
            }
        }
    }
    Timer {
        id: timer
        property real percentage: 0.0
        onPercentageChanged: {
            flick.contentX = row.width * timer.percentage
            //            console.log(percentage)
        }

        interval: 16
        repeat: true
        running: true
        onTriggered: {
            timer.percentage += 0.001
            if (timer.percentage > 1.0)
                timer.percentage = 0.0
        }
    }
}
