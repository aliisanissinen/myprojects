#include "weatherchart.hh"
#include <QValueAxis>
#include <QDebug>
#include <QDate>

#include <QDateTimeAxis>
#include <QAbstractAxis>
#include <QValueAxis>
#include <math.h>

const QString LINE_SERIES_NAME_MAIN = "Weather";


WeatherChart::WeatherChart(QObject* parent) :
    QObject{ parent },
    lineSeries_{}
{
}

WeatherChart::~WeatherChart()
{

}

QtCharts::QLineSeries *WeatherChart::getLineSeries() const
{
    return lineSeries_;
}

void WeatherChart::setLineSeries(QtCharts::QLineSeries *lineSeries)
{
    if (lineSeries_ == lineSeries) return;
    if (lineSeries_ && lineSeries_->parent() == this) delete lineSeries_;
    lineSeries_ = lineSeries;
    lineSeries->setName(LINE_SERIES_NAME_MAIN);
    lineSeries_->setColor(QColor(72, 61, 139));

    QDateTime start = QDateTime::fromString("2020-07-10", "yyyy-MM-dd");
    QDateTime end = QDateTime::fromString("2020-07-20", "yyyy-MM-dd");

    std::pair<float, float> minMaxPair = {0,10};
    setAxis(start, end, minMaxPair,"hh:ss");

    lineSeries_->hide();

    emit lineSeriesSignal();
}

void WeatherChart::addWeatherData(std::vector<std::pair<QDateTime, float> > WeatherData, QString name, QString type)
{

    lineSeries_->setName(name);
    lineSeries_->show();
    QDateTime start = WeatherData.front().first;
    QDateTime end = WeatherData.back().first;

    std::pair<float, float> minMaxPair = minMaxValue(WeatherData);

    setAxis(start, end, minMaxPair, type);

    if(lineSeries_)
    {
        for(unsigned int i = 0; i < WeatherData.size(); i++)
        {
            if (std::to_string(WeatherData.at(i).second) != "nan"){
                lineSeries_->append(WeatherData.at(i).first.toMSecsSinceEpoch() , WeatherData.at(i).second);
            }
        }
    }
}

void WeatherChart::setAxis(QDateTime start, QDateTime end, std::pair<float, float> minMaxPair, QString type)
{


    // Sets the axis limits to the values given in this file
    // Assumes that there are 2 QValueAxis objects generated for the series (xAxis and yAxis)
    // (This should be the case if the series has been created in the QML side)
    QList<QtCharts::QAbstractAxis*> axisList = lineSeries_->attachedAxes();
    for (int axisIndex{ 0 }; axisIndex < 2 && axisIndex < axisList.length(); ++axisIndex)
    {
        auto axis = axisList.at(axisIndex);

        if (axis->type() == QtCharts::QAbstractAxis::AxisType::AxisTypeValue)
        {
            float diff = (minMaxPair.second-minMaxPair.first)*0.05;
            auto valueAxis = dynamic_cast<QtCharts::QValueAxis*>(axis);
            valueAxis->setMin(floor(minMaxPair.first-diff));
            valueAxis->setMax(ceil(minMaxPair.second+diff));
            valueAxis->setTickCount(20);
        }
        else
        {
            auto valueAxis = dynamic_cast<QtCharts::QDateTimeAxis*>(axis);
            valueAxis->setMin(start);
            valueAxis->setMax(end);
            valueAxis->setTickCount(8);
            valueAxis->setLabelsAngle(45);
            valueAxis->setFormat(type);
        }
    }
}

std::pair<float, float> WeatherChart::minMaxValue(std::vector<std::pair<QDateTime, float> > weatherData)
{
    std::sort(weatherData.begin(), weatherData.end(), [](std::pair<QDateTime, float> &left, std::pair<QDateTime, float> &right) {
        return left.second < right.second;
    });

    float min = weatherData.front().second;
    float max = weatherData.back().second;

    std::pair<float, float> minMaxPair = {min, max};

    return minMaxPair;

}

void WeatherChart::clearData()
{
    if (lineSeries_)
    {
        lineSeries_->clear();
        lineSeries_->hide();
    }
}
