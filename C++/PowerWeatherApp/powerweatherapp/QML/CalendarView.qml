import QtQuick 2.12
import QtQuick.Window 2.12
import Qt.labs.calendar 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.1

Item {
    height: 350
    width: 290

    // Change the dates in view if data is predicted or
    // clear the dates if user change from predicted data to actual data
    function changeDates(datatype, startdate, enddate) {
        calendar.startDate = new Date()
        calendar.endDate = new Date()
        calendar.selectedDate = new Date()
        calendar.predictedData = false

        // If predicted power data, the data is the next 24h
        if (datatype === "power") {
            calendar.futureDate = new Date()
            calendar.futureDate.setDate(calendar.futureDate.getDate() + 1)
            calendar.predictedData = true
        }

        // If predicted weather data, the data is the next 48h
        else if (datatype === "weather") {
            calendar.futureDate = new Date()
            calendar.futureDate.setDate(calendar.futureDate.getDate() + 2)
            calendar.predictedData = true
        }

        else if (datatype === "clear") {
            calendar.startDate = undefined
            calendar.endDate = undefined
        }
    }

    // Sends startDate to controllers
    function setStartDateOnControllers(date) {
        powerController.getStartDate(date)
        weatherController.getStartDate(date)
    }

    // Sends endDate to controllers
    function setEndDateOnControllers(date) {
        powerController.getEndDate(date)
        weatherController.getEndDate(date)
    }

    Calendar {
        id: calendar
        property var today: new Date()
        property var lastDay: new Date(2018, 0, 1)
        maximumDate: calendar.today
        minimumDate: calendar.lastDay
        property var startDate: undefined
        property var endDate: undefined
        property var futureDate: undefined
        property bool predictedData: false


        style: CalendarStyle {
            dayDelegate: Item {
                readonly property color sameMonthDateTextColor: "dimgray"
                readonly property color differentMonthDateTextColor: "lightgray"
                readonly property color selectedDateColor: "teal"
                readonly property color selectedDateTextColor: "white"
                readonly property color invalidDatecolor: "lightgray"
                property var dateOnFocus: styleData.date


                Rectangle {
                    anchors.fill: parent
                    border.color: "transparent"
                    color: (styleData.date !== undefined &&
                            styleData.selected)?selectedDateColor : "transparent"
                }

                Rectangle {
                    anchors.fill: parent
                    color: ((dateOnFocus > calendar.startDate) &&
                            (dateOnFocus < calendar.stopDate))?"gray":
                           (calendar.startDate !== undefined &&
                            dateOnFocus.getTime()===
                            calendar.startDate.getTime())?"teal":"transparent"
                }


                MouseArea {
                    anchors.fill: parent
                    propagateComposedEvents: true
                    onPressed: {
                        sidebar.isQueryPredicted = false

                        if (styleData.date > calendar.today || styleData.date < calendar.lastDay) {

                        }

                        else if (calendar.startDate === undefined){
                            calendar.startDate = styleData.date
                            setStartDateOnControllers(Qt.formatDateTime(calendar.startDate, "yyyy-MM-dd"))
                        }

                        else if (calendar.endDate === undefined){
                            calendar.endDate = styleData.date
                            setEndDateOnControllers(Qt.formatDateTime(calendar.endDate, "yyyy-MM-dd"))
                        }

                        else {
                            calendar.startDate = styleData.date
                            calendar.endDate = undefined
                            setStartDateOnControllers(Qt.formatDateTime(calendar.startDate, "yyyy-MM-dd"))
                            setEndDateOnControllers("undefined")
                        }

                        if (calendar.endDate < calendar.startDate){
                            calendar.startDate = styleData.date
                            calendar.endDate = undefined
                            setStartDateOnControllers(Qt.formatDateTime(calendar.startDate, "yyyy-MM-dd"))
                            setEndDateOnControllers("undefined")
                        }

                        mouse.accepted = false
                        calendar.predictedData= false
                    }
                }

                // Change the color of the selected date
                Label {
                    id: dayText
                    text: styleData.date.getDate()
                    font.pixelSize: 12
                    anchors.centerIn: parent
                    color: {
                        var color = invalidDatecolor;

                        if (styleData.valid) {
                            if (styleData.visibleMonth) {
                                color = sameMonthDateTextColor;
                            }
                            else {
                                color = differentMonthDateTextColor;
                            }
                            if (styleData.selected) {
                                color = selectedDateTextColor;
                            }
                        }
                        color;
                    }
                }
            }
        }
    }

    // The text below the calendar, shows selected dates
    Column {
        anchors.top: calendar.bottom

        Text {
            font.pixelSize: 14
            text: {
                if (calendar.startDate === undefined) {
                    "Start Date: "
                }
                else {
                    `Start Date: ${calendar.startDate.toLocaleDateString(Locale.ShortFormat)}`
                }
            }
        }

        Text {
            font.pixelSize: 14
            text: {
                if (calendar.predictedData) {
                    `End Date: ${calendar.futureDate.toLocaleDateString(Locale.ShortFormat)}`
                }
                else if (calendar.endDate === undefined) {
                    "End Date: "
                }
                else {
                    `End Date: ${calendar.endDate.toLocaleDateString(Locale.ShortFormat)}`
                }
            }
        }
    }
}
