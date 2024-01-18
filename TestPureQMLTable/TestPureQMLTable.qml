import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Window 2.14
import TestNameSpace 1.0
import QtQuick.Controls 2.14
import QtQuick.Controls 1.4 as COLLL

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Test_Pure_QML_Table_On_Mac")
    Component.onCompleted: showMaximized()
    ColumnLayout {
        anchors.fill: parent
        CorrectedComp {
            id: animatedImage
            Layout.fillWidth: true
            height: 177
        }
        RowLayout {
            height: 100
            Layout.fillWidth: true
            Item {
                Layout.fillWidth: true
            }
            SpinBox {
                id: rowsSpinBox
                from: 1
                to: 999999
                value: 3000
            }
            SpinBox {
                id: colsSpinBox
                from: 1
                to: 30
                value: 12
            }
            Button {
                id: regenerateBtn
                text: "Regenerate items"
                onClicked: {
                    defaultModel.removeAndRegenerateRows(rowsSpinBox.value,
                                                         colsSpinBox.value)
                }
            }

            Item {
                Layout.fillWidth: true
            }
        }

        Rectangle {
            id: bordering
            Layout.fillHeight: true
            Layout.fillWidth: true
            border.width: 2
            border.color: "aqua"
            Component {
                id: columnComponent
                COLLL.TableViewColumn {
                    width: 100
                }
            }
            TableView {
                id: tableView
                anchors.fill: parent
                delegate: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 50
                    Text {
                        text: display
                    }
                }
                model: CustomModel {
                    id: defaultModel
                    //                    onRoleNamesForQMLChanged: tableView.updateResources()
                }

                //                Instantiator {
                //                    model: defaultModel.roleNamesForQML
                //                    onObjectAdded: tableView.addColumn(object)
                //                    onObjectRemoved: tableView.removeColumn(object)
                //                    delegate: COLLL.TableViewColumn {
                //                        width: 100
                //                        title: modelData
                //                        role: modelData
                //                    }
                //                }
                function update2() {
                    for (var i = 0; i < titles.length; i++) {
                        if (curTitles.indexOf(titles[i]) === -1) {
                            var column = addColumn(columnComponent)
                            column.title = titles[i]
                            column.role = titles[i]
                        }
                    }
                    for (var i = curTitles.length - 1; i >= 0; i--) {
                        if (titles.indexOf(curTitles[i]) == -1) {
                            removeColumn(i)
                        }
                    }
                }

                function updateResources() {
                    var roleList = defaultModel.roleNamesForQML
                    console.log(roleList)
                    var temp = []
                    for (var i = 0; i < roleList.length; i++) {
                        var role = roleList[i]
                        temp.push(columnComponent.createObject(tableView, {
                                                                   "role": role,
                                                                   "title": role
                                                               }))
                    }
                    tableView.resources = temp
                }
            }
        }
    }
}
