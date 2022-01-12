import QtQuick 2.12
import QtQuick.Window 2.12
import Qt.labs.calendar 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.1

Item {
    width: 290
    height: parent.height
    property bool isQueryPredicted: false
    property string unitPower: "MW"
    property string unitWeather: ""

    // Uncheck the other boxes and send variable to controller
    function powerCheckBoxControl(variableNumber, checkBoxNumber, predicted) {
        // Clear the dates if last data was predicted and the next isn't
        if (isQueryPredicted && !predicted) {
            calendarItem.changeDates("clear")
        }

        var checkBoxVector = [powercheck1, powercheck2, powercheck3,
                              powercheck4, powercheck5, powercheck6,
                              powercheck7]

        powerController.getVariable(variableNumber)

        for (var i = 0; i <= 6; i++) {
            if (checkBoxVector[i] !== checkBoxVector[checkBoxNumber-1]) {
                checkBoxVector[i].checked = false
            }
        }
    }

    // Uncheck the other boxes and send variable to controller
    function weatherCheckBoxControl(variableNumber, checkBoxNumber, predicted) {
        // Clear the dates if last data was predicted and the next isn't
        if (isQueryPredicted && !predicted) {
            calendarItem.changeDates("clear")
        }

        var checkBoxVector = [weathercheck1, weathercheck2,
                              weathercheck3, weathercheck4,
                              weathercheck5]

        weatherController.getVariable(variableNumber, predicted)

        for (var i = 0; i <= 4; i++) {
            if (checkBoxVector[i] !== checkBoxVector[checkBoxNumber-1]) {
                checkBoxVector[i].checked = false
            }
        }
    }

    ScrollView {
        anchors.fill: parent
        ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        ScrollBar.vertical.interactive: true

        ToolBar {
            id: toolbars
            width: 290
            height: 2000
            Column {
                id: toolbarcolumn

                // Calendar implementation in other QML file
                CalendarView {
                    id: calendarItem
                }

                Text {
                    text: "Fingrid/Power"
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    font.pixelSize: 22
                    font.bold: true
                }

                CheckBox {
                    id: powercheck1
                    checked: false
                    text: qsTr("Electricity consumptions in Finland")
                    font.pixelSize: 13
                    indicator.width: 15
                    indicator.height: 15

                    onClicked: {
                        if (checked) {
                            powerCheckBoxControl(124, 1, false)
                            lineplot.pString = "dd-MM"
                            isQueryPredicted = false
                        }
                    }
                }

                CheckBox {
                    id: powercheck2
                    checked: false
                    text: qsTr("Electricity consumptions forecast for\nthe next 24 hours")
                    font.pixelSize: 13
                    indicator.width: 15
                    indicator.height: 15

                    onClicked: {
                        if (checked) {
                            calendarItem.changeDates("power")
                            powerCheckBoxControl(165, 2, true)
                            lineplot.pString = "hh:ss"
                            isQueryPredicted = true
                        }
                    }
                }

                CheckBox {
                    id: powercheck3
                    checked: false
                    text: qsTr("A tentative production prediction for\nthe next 24 hours as hourly energy")
                    font.pixelSize: 13
                    indicator.width: 15
                    indicator.height: 15

                    onClicked: {
                        if (checked) {
                            calendarItem.changeDates("power")
                            powerCheckBoxControl(242, 3, true)
                            lineplot.pString = "hh:ss"
                            isQueryPredicted = true
                        }
                    }
                }

                CheckBox {
                    id:powercheck4
                    checked: false
                    text: qsTr("Electricity production in Finland")
                    font.pixelSize: 13
                    indicator.width: 15
                    indicator.height: 15

                    onClicked: {
                        if (checked) {
                            powerCheckBoxControl(192, 4, false)
                            lineplot.pString = "dd-MM"
                            isQueryPredicted = false
                        }
                    }
                }

                CheckBox {
                    id: powercheck5
                    checked: false
                    text: qsTr("Wind power production forecast")
                    font.pixelSize: 13
                    indicator.width: 15
                    indicator.height: 15

                    onClicked: {
                        if (checked) {
                            powerCheckBoxControl(181, 5, false)
                            lineplot.pString = "dd-MM"
                            isQueryPredicted = false
                        }
                    }
                }

                CheckBox {
                    id: powercheck6
                    checked: false
                    text: qsTr("Nuclear power production")
                    font.pixelSize: 13
                    indicator.width: 15
                    indicator.height: 15

                    onClicked: {
                        if (checked) {
                            powerCheckBoxControl(188, 6, false)
                            lineplot.pString = "dd-MM"
                            isQueryPredicted = false
                        }
                    }
                }

                CheckBox {
                    id: powercheck7
                    checked: false
                    text: qsTr("Hydro power production")
                    font.pixelSize: 13
                    indicator.width: 15
                    indicator.height: 15

                    onClicked: {
                        if (checked) {
                            powerCheckBoxControl(191, 7, false)
                            lineplot.pString = "dd-MM"
                            isQueryPredicted = false
                        }
                    }
                }

                Text {
                    text: "FMI/Weather"
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    font.pixelSize: 22
                    font.bold: true
                }

                TextField {
                    id: citytext
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    placeholderText: qsTr("Enter the city")

                    onTextChanged: {
                        citytext.text = text
                        weatherController.getCity(text)
                        isQueryPredicted = false
                    }
                }

                CheckBox {
                    id: weathercheck1
                    checked: false
                    text: qsTr("Temperature")
                    font.pixelSize: 13
                    indicator.width: 15
                    indicator.height: 15

                    onClicked: {
                        if (checked) {
                            weatherCheckBoxControl("Temperature", 1, false)
                            lineplot.wString = "dd-MM"
                            isQueryPredicted = false
                            unitWeather = "°C"
                        }
                    }
                }

                CheckBox {
                    id: weathercheck2
                    checked: false
                    text: qsTr("Observed wind")
                    font.pixelSize: 13
                    indicator.width: 15
                    indicator.height: 15

                    onClicked: {
                        if (checked) {
                            weatherCheckBoxControl("WindSpeedMS", 2, false)
                            lineplot.wString = "dd-MM"
                            isQueryPredicted = false
                            unitWeather = "m/s"
                        }
                    }
                }

                CheckBox {
                    id: weathercheck3
                    checked: false
                    text: qsTr("Observed cloudiness")
                    font.pixelSize: 13
                    indicator.width: 15
                    indicator.height: 15
                    onClicked: {
                        if (checked) {
                            weatherCheckBoxControl("TotalCloudCover", 3, false)
                            lineplot.wString = "dd-MM"
                            isQueryPredicted = false
                            unitWeather = "(0/8)"
                        }
                    }
                }

                CheckBox {
                    id: weathercheck4
                    checked: false
                    text: qsTr("Predicted wind")
                    font.pixelSize: 13
                    indicator.width: 15
                    indicator.height: 15

                    onClicked: {
                        if (checked) {
                            calendarItem.changeDates("weather")
                            weatherCheckBoxControl("WindSpeedMS", 4, true)
                            lineplot.wString = "dd-MM"
                            isQueryPredicted = true
                            unitWeather = "m/s"
                        }
                    }
                }

                CheckBox {
                    id: weathercheck5
                    checked: false
                    text: qsTr("Predicted temperature")
                    font.pixelSize: 13
                    indicator.width: 15
                    indicator.height: 15

                    onClicked: {
                        if (checked) {
                            calendarItem.changeDates("weather")
                            weatherCheckBoxControl("Temperature", 5, true)
                            lineplot.wString = "dd-MM"
                            isQueryPredicted = true
                            unitWeather = "°C"
                        }
                    }
                }
            }
        }
    }
}
