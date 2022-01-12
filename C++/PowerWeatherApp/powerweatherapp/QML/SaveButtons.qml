import QtQuick 2.5
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtCharts 2.2

Item {
    anchors.fill: parent

    // Invalid symbols that are not allowed in the filename
    property string invalidSymbolsText:
        "Invalid symbols: * . / \ [ ] : ; | , ) € $ ? < > \"\ ä ö å"

    Button {
        id: weatherSave
        anchors.left: parent.left
        width: parent.width / 3
        height: parent.height
        text: qsTr("Save weatherdata")

        onClicked: {
            popupweather.open()
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

    Button {
        id: powerSave
        anchors.right: parent.right
        width: parent.width / 3
        height: parent.height
        text: qsTr("Save powerdata")

        onClicked: {
            popuppower.open()
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

    // Pop up window where user can enter the filename for weatherdata
    Popup {
        id: popupweather
        width: 420
        height: 110
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        property string saveType: "txt"

        TextField {
            id: filenameweather
            width:  300
            placeholderText: qsTr("Enter the filename (without .txt / .png)")
            onTextChanged: {
                filenameweather.text = text
            }
        }

        RoundButton {
            id: filenamebuttonweather
            anchors.right: parent.right
            width: 80
            text: qsTr("Save")
            onClicked: {
                if (popupweather.saveType === "txt") {
                    weatherController.saveData(filenameweather.text)
                }
                else if (popupweather.saveType === "png") {
                    lineplot.saveWeatherChart(filenameweather.text)
                }
                popupweather.close()
            }
        }

       Text {
            id: invalidsymbolsweather
            height: 20
            anchors.top: filenameweather.bottom
            text: invalidSymbolsText
            font.pixelSize: 12
            color: "gray"
        }

       // User can choose the format of the data
       Row {
            id: rowlayotweather
            height: 15
            anchors.bottom: parent.bottom

            RadioButton {
                id: txtformatweather
                text: qsTr(".txt format")
                implicitHeight: rowlayotweather.height
                checked: true
                font.pixelSize: 13
                onClicked:  {
                    popupweather.saveType = "txt"
                }
            }

            RadioButton {
                id: imageformatweather
                text: qsTr(".png format")
                implicitHeight: rowlayotweather.height
                font.pixelSize: 13
                onClicked:  {
                    popupweather.saveType = "png"
                }
            }
        }
    }

    // Pop up window where user can enter the filename for powerdata
    Popup {
        id: popuppower
        width: 420
        height: 110
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
        property string saveType: "txt"

        TextField {
            id: filenamepower
            width:  300
            placeholderText: qsTr("Enter the filename (without .txt / .png)")

            onTextChanged: {
                filenamepower.text = text
            }
        }

        RoundButton {
            id: filenamebuttonpower
            anchors.right: parent.right
            width: 80
            text: qsTr("Save")

            onClicked: {
                if (popuppower.saveType === "txt") {
                    powerController.saveData(filenamepower.text)
                }
                else if (popuppower.saveType === "png") {
                    lineplot.savePowerChart(filenamepower.text)
                }
                popuppower.close()
            }
        }

        Text {
            id: invalidsymbolspower
            height: 20
            anchors.top: filenamepower.bottom
            text: invalidSymbolsText
            font.pixelSize: 12
            color: "gray"
        }

         // User can choose the format of the data
        Row {
            id: rowlayotpower
            height: 15
            anchors.bottom: parent.bottom

            RadioButton {
                id: txtformatpower
                text: qsTr(".txt format")
                implicitHeight: rowlayotpower.height
                checked: true
                font.pixelSize: 13
                onClicked:  {
                    popuppower.saveType = "txt"
                }
            }

            RadioButton {
                id: imageformatpower
                text: qsTr(".png format")
                implicitHeight: rowlayotpower.height
                font.pixelSize: 13
                onClicked:  {
                    popuppower.saveType = "png"
                }
            }
        }
    }
}


