import QtQuick 2.0
import QtCharts 2.3
import QtQuick.Layouts 1.12

Item
{
    width: insideWindow.width
    height: insideWindow.height * (2/3)

    property var pString: "hh:ss"
    property var wString: "hh:ss"

    property alias powerAverageText: powerAverage.text
    property alias powerMinText: powerMin.text
    property alias powerMaxText: powerMax.text
    property alias powerPrecentageText: powerPrecentage.text

    property alias powerAverageSecondaryText: powerAverageSecondary.text
    property alias powerMinSecondaryText: powerMinSecondary.text
    property alias powerMaxSecondaryText: powerMaxSecondary.text

    property alias weatherAverageText: weatherAverage.text
    property alias weatherMinText: weatherMin.text
    property alias weatherMaxText: weatherMax.text

    property string unitWeather: ""
    property string unitPower: ""

    // Save the powerchart, when the user has selected image format and pressed
    // the save button
    function savePowerChart(filename) {
        powerplot.grabToImage(function(result)
        {result.saveToFile(`savedFiles/${filename}.png`);});
        statistics.changePhase(7);
    }

    // Save the weatherchart, when the user has selected image format and
    // pressed the save button
    function saveWeatherChart(filename) {
        weatherplot.grabToImage(function(result)
        {result.saveToFile(`savedFiles/${filename}.png`); });
        statistics.changePhase(7);
    }

    ChartView {
        id: weatherplot
        title: "Weather"
        titleFont.pixelSize: 24
        anchors.left: parent.left
        antialiasing: true
        width: parent.width / 2 * 0.9
        height: parent.height * 0.9


        LineSeries {
            id: weatherSeries
            axisX: DateTimeAxis{format:wString}
        }

        //Rectangle and MouseArea are for zooming in and reseting zoom
        Rectangle{
            id: rectangW
            color: "teal"
            opacity: 0.6
            visible: false
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.AllButtons

            onPressed: {rectangW.x = mouseX; rectangW.y = mouseY; rectangW.visible = true}
            onMouseXChanged: {rectangW.width = mouseX - rectangW.x}
            onMouseYChanged: {rectangW.height = mouseY - rectangW.y}
            onReleased: {
                    weatherplot.zoomIn(Qt.rect(rectangW.x, rectangW.y, rectangW.width, rectangW.height))
                    rectangW.visible = false
            }
            onDoubleClicked: weatherplot.zoomReset()
        }
    }

    ChartView {
        id: powerplot
        title: "Power"
        titleFont.pixelSize: 24
        anchors.left: weatherplot.right
        anchors.leftMargin: parent.width / 2 * 0.1
        width: parent.width / 2 * 0.9
        height: parent.height * 0.9
        antialiasing: true

        LineSeries {
            id: powerSeries
            axisX: DateTimeAxis{format:pString} //"hh:ss" or "yyyy-MM-dd"
        }

        //Rectangle and MouseArea are for zooming in and reseting zoom
        Rectangle{
            id: rectangP
            color: "teal"
            opacity: 0.6
            visible: false
        }

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.AllButtons

            onPressed: {rectangP.x = mouseX; rectangP.y = mouseY; rectangP.visible = true}
            onMouseXChanged: {rectangP.width = mouseX - rectangP.x}
            onMouseYChanged: {rectangP.height = mouseY - rectangP.y}
            onReleased: {
                    powerplot.zoomIn(Qt.rect(rectangP.x, rectangP.y, rectangP.width, rectangP.height))
                    rectangP.visible = false
            }
            onDoubleClicked: powerplot.zoomReset()
        }

    }

    Component.onCompleted: {
        // Share the empty data series to the C++ side
        powerchart.powerSeries = powerSeries;
        weatherchart.weatherSeries = weatherSeries;
    }

    Column {
        anchors.top: weatherplot.bottom
        anchors.left: weatherplot.left
        anchors.leftMargin: 70

        Text {
            id: weatherAverage
            text: `Average: ${(weatherModel.weatherAverage).toFixed(2)} ${unitWeather}`
            font.pixelSize: lineplot.height * 0.026
            color: "darkslateblue"
        }

        Text {
            id: weatherMin
            text: `Min: ${(weatherModel.weatherMin).toFixed(2)} ${unitWeather}`
            font.pixelSize: lineplot.height * 0.026
            color: "darkslateblue"
        }

        Text {
            id: weatherMax
            text: `Max: ${(weatherModel.weatherMax).toFixed(2)} ${unitWeather}`
            font.pixelSize: lineplot.height * 0.026
            color: "darkslateblue"
        }
    }

    RowLayout {
        id: powerStatistic
        anchors.top: powerplot.bottom
        anchors.left: powerplot.left
        anchors.leftMargin: 80

        Column {
            Text {
                id: powerAverage
                text: `Average: ${(powerModel.powerAverage).toFixed(2)} ${unitPower}`
                font.pixelSize: lineplot.height * 0.026
                color: "darkslateblue"
            }

            Text {
                id: powerMin
                text: `Min: ${(powerModel.powerMin).toFixed(2)} ${unitPower}`
                font.pixelSize: lineplot.height * 0.026
                color: "darkslateblue"
            }

            Text {
                id: powerMax
                text: `Max: ${(powerModel.powerMax).toFixed(2)} ${unitPower}`
                font.pixelSize: lineplot.height * 0.026
                color: "darkslateblue"
            }
        }

        Column {
            Text {
                id: powerAverageSecondary
                text: `Average: ${(powerModel.powerAverageSecondary).toFixed(2)} ${unitPower}`
                font.pixelSize: lineplot.height * 0.026
                color: "teal"
            }

            Text {
                id: powerMinSecondary
                text: `Min: ${(powerModel.powerMinSecondary).toFixed(2)} ${unitPower}`
                font.pixelSize: lineplot.height * 0.026
                color: "teal"
            }

            Text {
                id: powerMaxSecondary
                text: `Max: ${(powerModel.powerMaxSecondary).toFixed(2)} ${unitPower}`
                font.pixelSize: lineplot.height * 0.026
                color: "teal"
            }
        }

        Text {
            id: powerPrecentage
            Layout.alignment: Qt.AlignTop
            text: `Percentage: ${(powerModel.powerPrecentage).toFixed(2)} %`
            font.pixelSize: lineplot.height * 0.026
            color: "teal"
        }
    }
}
