
import QtQuick 2.15

Rectangle {
    width: 200
    height: 200

    property real knobValue: 0.0

    Rectangle {
        width: parent.width
        height: parent.height
        color: "transparent"

        Rectangle {
            width: parent.width
            height: parent.height / 2
            color: "red"
            radius: 100

            Rectangle {
                width: parent.width / 2
                height: parent.height
                color: "white"
                radius: 100

                Rectangle {
                    width: parent.width / 2
                    height: parent.height
                    color: "transparent"
                    radius: 100

                    Rectangle {
                        width: parent.width / 2
                        height: parent.height
                        color: "gray"
                        radius: 100

                        Rectangle {
                            width: parent.width / 2
                            height: parent.height
                            color: "transparent"
                            radius: 100

                            Rectangle {
                                width: parent.width / 2
                                height: parent.height
                                color: "darkgray"
                                radius: 100
                                border.width: 2
                                border.color: "black"

                                MouseArea {
                                    id: knob
                                    width: parent.width
                                    height: parent.height

                                    onClicked: {
                                        knobValue = knobValue === 1.0 ? 0.0 : 1.0
                                        knobQML.setValue(knobValue)
                                    }
                                }

                                Rectangle {
                                    width: parent.width / 2
                                    height: parent.height / 2
                                    color: "transparent"
                                    border.width: 2
                                    border.color: "black"
                                    radius: parent.width / 4

                                    Rectangle {
                                        width: parent.width / 2
                                        height: parent.height / 2
                                        color: "black"
                                        radius: parent.width / 4
                                    }

                                    Rectangle {
                                        width: 2
                                        height: parent.height
                                        color: "black"
                                    }

                                    Rectangle {
                                        width: parent.width
                                        height: 2
                                        color: "black"
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
