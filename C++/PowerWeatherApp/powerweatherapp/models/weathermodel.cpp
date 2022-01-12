#include "weathermodel.hh"

WeatherModel::WeatherModel()
{
    connect(&reader_, &APIReader::newDataReady, this, &WeatherModel::dataChanged);
}

void WeatherModel::getWeatherData(QString input)
{
    reader_.fetchData(input);
}
void WeatherModel::dataChanged(QString newData)
{
    rawData_ = newData;
    //prevents crash if wrong datatype
    if(newData.contains("xmlns")){
        if (rawData_.contains("hirlam") ){
            parsedWeatherData_ = parser_.parseHirlamXml(rawData_);
        }
        else {
            parsedWeatherData_ = parser_.parseFmiXml(rawData_);
        }

        if (parsedWeatherData_.size() != 0){
            isEmpty = false;
            drawData();
        }
    }
    else{
        //prevents crash if wrong datatype
        stats_.get()->changePhase(8);
    }
}

void WeatherModel::drawData()
{
    if (!isEmpty){
        WeatherChart_->clearData();
        averageValue(parsedWeatherData_);

        calculateAverage();
        calculateMin();
        calculateMax();

        emit averageChanged();
        emit minChanged();
        emit maxChanged();

        stats_.get()->changePhase(1);

        if(parsedWeatherData_.front().first.date().daysTo(parsedWeatherData_.back().first.date()) >= 6)
        {
            WeatherChart_.get()->addWeatherData(medianDateData(parsedWeatherData_), chartName_, "dd-MM");
        }
        else if(parsedWeatherData_.front().first.date().daysTo(parsedWeatherData_.back().first.date()) > 1)
        {
            WeatherChart_.get()->addWeatherData(medianHourData(parsedWeatherData_), chartName_, "hh:ss");//medianDateData(parsedPowerData_),medianHourData(parsedPowerData_),parsedPowerData_
        }
        else
        {
            WeatherChart_.get()->addWeatherData(parsedWeatherData_, chartName_, "hh:ss");
        }

        //WeatherChart_.get()->addWeatherData(parsedWeatherData_, chartName_);//medianDateData(parsedWeatherData_),parsedWeatherData_
    }
}

void WeatherModel::clearAll()
{
    WeatherChart_->clearData();

    stats_.get()->changePhase(0);
    emit stats_.get()->textToUserChanged();

    parsedWeatherData_.clear();
    emit averageChanged();
    emit minChanged();
    emit maxChanged();

}

void WeatherModel::setWeatherChart(std::shared_ptr<WeatherChart> WeatherChart)
{
    WeatherChart_ = WeatherChart;
}

void WeatherModel::setChartName(QString name)
{
    chartName_ = name;
}

float WeatherModel::calculateAverage()
{
    if(parsedWeatherData_.size()!=0)
    {
        average_ = averageValue(parsedWeatherData_);
        qDebug() << average_;
    }
    else
    {
        return 0;
    }
    return average_;
}

float WeatherModel::calculateMin()
{
    if(parsedWeatherData_.size()!=0)
    {
        min_ = minValue(parsedWeatherData_);
        qDebug() << min_;
    }
    else
    {
        return 0;
    }
    return min_;
}

float WeatherModel::calculateMax()
{
    if(parsedWeatherData_.size()!=0)
    {
        max_ = maxValue(parsedWeatherData_);
        qDebug() << max_;
    }
    else
    {
        return 0;
    }
    return max_;

}

