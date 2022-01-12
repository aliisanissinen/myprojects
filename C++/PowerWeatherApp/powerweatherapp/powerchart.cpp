#include "powerchart.hh"
#include <QValueAxis>
#include <QDebug>
#include <QDate>

#include <QDateTimeAxis>
#include <QAbstractAxis>
#include <QValueAxis>
#include <math.h>

const QString LINE_SERIES_NAME_MAIN = "Power";

PowerChart::PowerChart(QObject* parent) :
    QObject{ parent },
    lineSeries_{},
    lineSeriesExtra_{}
{
}

PowerChart::~PowerChart()
{

}

QtCharts::QLineSeries *PowerChart::getLineSeries() const
{
    return lineSeries_;
}

void PowerChart::setLineSeries(QtCharts::QLineSeries *lineSeries)
{
    if (lineSeries_ == lineSeries) return;
    if (lineSeries_ && lineSeries_->parent() == this) delete lineSeries_;
    lineSeries_ = lineSeries;
    lineSeries->setName(LINE_SERIES_NAME_MAIN);
    lineSeries_->setColor(QColor(72, 61, 139));

    QDateTime start = QDateTime::fromString("2020-07-10", "yyyy-MM-dd");
    QDateTime end = QDateTime::fromString("2020-07-20", "yyyy-MM-dd");

    std::pair<float, float> minMaxPair = {0,10};
    setAxis(start, end, minMaxPair, "hh:ss");

    lineSeries_->hide();

    emit lineSeriesSignal();
}

void PowerChart::addPowerData(std::vector<std::pair<QDateTime, float> > powerData, QString name, QString type)
{
    lineSeries_->clear();
    lineSeries_->setName(name);
    lineSeries_->show();

    QDateTime start = powerData.front().first;
    QDateTime end = powerData.back().first;

    //If there is lineSeries already when we try to plot new lineSeries
    //this is used to calculate min and max value and scale the y-axis
    if(lineSeriesActive_)
    {
        minMaxPair_ = minMaxValue(powerData);
    }
    lineSeriesActive_ = true;

    //If there is difference between min and max values in
    //main and extra graph this is used to scale y-axis in that way we can see both graphs
    if(minMaxPairSet == true)
    {
        std::pair<float, float> minMaxPairNew = minMaxValue(powerData);

        if(minMaxPair_.first >= minMaxPairNew.first)
        {
            minMaxPair_.first = minMaxPairNew.first;
        }
        if(minMaxPair_.second < minMaxPairNew.second)
        {
            minMaxPair_.second = minMaxPairNew.second;
        }
    }
    else
    {
        minMaxPair_ = minMaxValue(powerData);
        minMaxPairSet = true;
    }

    setAxis(start, end, minMaxPair_, type);

    if(lineSeries_)
    {
        for(unsigned int i = 0; i < powerData.size(); i++)
        {
            lineSeries_->append(powerData.at(i).first.toMSecsSinceEpoch() , powerData.at(i).second);
        }
    }
}

void PowerChart::setAxis(QDateTime start, QDateTime end, std::pair<float, float> minMaxPair, QString type)
{


    //Sets the axis limits to the values given in this file
    QList<QtCharts::QAbstractAxis*> axisList = lineSeries_->attachedAxes();
    for (int axisIndex{ 0 }; axisIndex < 2 && axisIndex < axisList.length(); ++axisIndex)
    {
        auto axis = axisList.at(axisIndex);

        if (axis->type() == QtCharts::QAbstractAxis::AxisType::AxisTypeValue)
        {
            //This is for y-axis that is QValueAxisType
            //Diff calcultas difference between min and max value and takes 5% of the value
            //Diff is used to scale the y-axis is both directions
            float diff = (minMaxPair.second-minMaxPair.first)*0.05;

            auto valueAxis = dynamic_cast<QtCharts::QValueAxis*>(axis);

            valueAxis->setMin(floor(minMaxPair.first-diff));
            valueAxis->setMax(ceil(minMaxPair.second+diff));
            valueAxis->setTickCount(20);

            // Attach the same axis to the extra series (which should not yet have any axis)
            if(lineSeriesExtra_)
            {
                lineSeriesExtra_->attachAxis(valueAxis);
            }
        }
        else
        {
            //This is for x-axis that is QDateTimeAxis
            auto valueAxis = dynamic_cast<QtCharts::QDateTimeAxis*>(axis);
            valueAxis->setMin(start);
            valueAxis->setMax(end);
            valueAxis->setTickCount(8);
            valueAxis->setLabelsAngle(45);
            valueAxis->setFormat(type);

            // Attach the same axis to the extra series (which should not yet have any axis)
            if(lineSeriesExtra_)
            {
                lineSeriesExtra_->attachAxis(valueAxis);
            }
        }
    }
}

std::pair<float, float> PowerChart::minMaxValue(std::vector<std::pair<QDateTime, float> > powerData)
{
    std::sort(powerData.begin(), powerData.end(), [](std::pair<QDateTime, float> &left, std::pair<QDateTime, float> &right) {
        return left.second < right.second;
    });

    float min = powerData.front().second;
    float max = powerData.back().second;

    std::pair<float, float> minMaxPair = {min, max};

    return minMaxPair;
}

void PowerChart::addExtraPowerData(std::vector<std::pair<QDateTime, float> > powerData, QString name, QString type)
{
    // Add an extra line series to the same chart as the original line series
    // If there is no extra line series already
    if(!lineSeriesExtra_)
    {
        lineSeriesExtra_ = new QtCharts::QLineSeries();
        lineSeriesExtra_->setColor(QColor(0, 128, 128));
        lineSeries_->chart()->addSeries(lineSeriesExtra_);
        lineSeriesExtra_->setName(name);
    }

    lineSeriesExtra_->show();
    lineSeriesExtra_->clear();
    lineSeriesExtra_->setName(name);

    //If there is lineSeriesExtra already when we try to plot  new extra line
    //this is used to calculate ne min and max value and scale the y-axis
    if(lineSeriesExtraActive_)
    {
        minMaxPair_ = minMaxValue(powerData);
    }
    lineSeriesExtraActive_ = true;

    QDateTime start = powerData.front().first;
    QDateTime end = powerData.back().first;

    //If there is difference between min and max values in
    //main and extra graphe this is used to scale y-axis in that way we can see both graphs
    if(minMaxPairSet == true)
    {
        std::pair<float, float> minMaxPairNew = minMaxValue(powerData);

        if(minMaxPair_.first >= minMaxPairNew.first)
        {
            minMaxPair_.first = minMaxPairNew.first;
        }
        if(minMaxPair_.second < minMaxPairNew.second)
        {
            minMaxPair_.second = minMaxPairNew.second;
        }
    }
    else
    {
        minMaxPair_ = minMaxValue(powerData);
        minMaxPairSet = true;
    }

    setAxis(start, end, minMaxPair_, type);

    if(lineSeriesExtra_)
    {
        for(unsigned int i = 0; i < powerData.size(); i++)
        {
            lineSeriesExtra_->append(powerData.at(i).first.toMSecsSinceEpoch() , powerData.at(i).second);
        }
    }
}

void PowerChart::clearData()
{
    clearNormal();

    clearExtra();

    minMaxPairSet = false;
}

void PowerChart::clearNormal()
{
    if (lineSeries_)
    {
        lineSeries_->clear();
        lineSeriesActive_ = false;
        lineSeries_->hide();
    }
}

void PowerChart::clearExtra()
{
    if (lineSeriesExtra_)
    {
        lineSeriesExtra_->clear();
        lineSeriesExtraActive_ = false;
        lineSeriesExtra_->hide();
    }

}
