import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4

Item
{
    height: parent.height / 20
    width: parent.width

    // Two fetch data buttons and one clear button
    Row {
        id: buttonrow
        anchors.fill: parent

        Button {
            id: weatherbutton
            width: parent.width / 4
            height: parent.height
            text: qsTr("Draw weather data")

            onClicked: {
                weatherController.getWeatherData()
                lineplot.unitWeather = sidebar.unitWeather
            }

            background: Rectangle {
                border.width: 1
                border.color: "white"
                color: "teal"
            }

            palette {
                buttonText: "white"
            }

        }

        Button {
            id: powerbutton
            width: parent.width / 4
            height: parent.height
            text: qsTr("Draw power data")
            onClicked: {
                powerController.getPowerData()
                lineplot.unitPower = sidebar.unitPower
            }

            background: Rectangle {
                border.width: 1
                border.color: "white"
                color: "teal"
            }

            palette {
                buttonText: "white"
            }
        }

        Button {
            id: powerExtra
            width: parent.width / 4
            height: parent.height
            text: qsTr("Draw extra power")

            onClicked: {
                powerController.drawExtraData()
                lineplot.unitPower = sidebar.unitPower
            }

            background: Rectangle {
                border.width: 1
                border.color: "white"
                color: "teal"
            }

            palette {
                buttonText: "white"
            }
        }

        Button {
            id: clearPower
            width: parent.width / 4
            height: parent.height
            text: qsTr("Clear all")

            onClicked: {
                powerController.clearAll()
                weatherController.clearAll()
            }

            background: Rectangle {
                border.width: 1
                border.color: "white"
                color: "teal"
            }

            palette {
                buttonText: "white"
            }
        }
    }
}
