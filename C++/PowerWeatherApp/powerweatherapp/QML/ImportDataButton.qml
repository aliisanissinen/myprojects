import QtQuick 2.0
import QtQuick.Controls 2.12

Item {

    anchors.fill: parent

    Button {
        id: importbutton
        width: parent.width / 3
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("Import data from computer (.txt)")

        onClicked: {
            popup.open()
        }

        palette {
            buttonText: "white"
        }

        background: Rectangle {
            color: "teal"
            border.width: 3
            border.color: "white"
            radius: 15
        }
    }

    // Pop up window where user can enter the filename
    Popup {
        id: popup
        width: 420
        height: 90
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        property var dataType: "weather"

        TextField {
            id: filename
            width:  300
            placeholderText: qsTr("Enter the filename (without .txt)")
            onTextChanged: {
                filename.text = text
            }
        }

        RoundButton {
            id: filenamebutton
            anchors.right: parent.right
            width: 80
            text: qsTr("Import")
            onClicked: {
                if (popup.dataType === "weather") {
                    weatherController.importData(filename.text);
                }
                else if (popup.dataType === "power") {
                    powerController.importData(filename.text);
                }
                popup.close()
            }
        }

        Row {
            id: rowlayot
            height: 15
            anchors.bottom: parent.bottom

            RadioButton {
                text: qsTr("WeatherData")
                implicitHeight: rowlayot.height
                checked: true
                font.pixelSize: 13
                onClicked: {
                    popup.dataType = "weather"
                }
            }

            RadioButton {
                text: qsTr("PowerData")
                implicitHeight: rowlayot.height
                font.pixelSize: 13
                onClicked:  {
                    popup.dataType = "power"
                }
            }
        }
    }
}
