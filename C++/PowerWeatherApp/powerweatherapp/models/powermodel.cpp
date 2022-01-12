#include "powermodel.hh"

PowerModel::PowerModel()
{
    // Connect data ready event (signal) your dataCahanged slot
    connect(&reader_, &APIReader::newDataReady, this, &PowerModel::dataChanged);
}

void PowerModel::getPowerData(QString input, bool extra)
{
    extra_ = extra;
    reader_.fetchData(input);
}

void PowerModel::dataChanged(QString newData)
{
    //prevents crash if wrong datatype
    if(!newData.contains("xmlns")){

        rawData_ = newData;
        parsedPowerData_ = parser_.parseCsv(rawData_);

        //Extra_ if true = main graph, false = extra graph
        if(extra_)
        {
            //This is for main graph
            if (parsedPowerData_.size() != 0)
            {
                powerChart_->clearNormal();
                isEmpty = false;
                calculateTotal(true);
                calculatePrecentage();
                emit precentageChanged();
                drawData();
            }
        }
        else
        {
            //This is for the extra graph
            if (parsedPowerData_.size() != 0)
            {
                powerChart_->clearExtra();
                isEmpty = false;
                calculateTotal(false);
                calculatePrecentage();
                emit precentageChanged();
                drawExtraLine();
            }
        }
    }
    else{
        stats_.get()->changePhase(8);
    }

}


void PowerModel::drawData()
{
    if (!isEmpty)
    {
        averageValue(parsedPowerData_);

        emit averageChanged();
        emit minChanged();
        emit maxChanged();

        stats_.get()->changePhase(1);

        //If the data is for a period of more than seven days the data is plotted by calculating all data from one day to one point
        if(parsedPowerData_.front().first.date().daysTo(parsedPowerData_.back().first.date()) >= 7)
        {
            powerChart_.get()->addPowerData(medianDateData(parsedPowerData_), chartName_, "dd-MM");
        }
        //If the data is between one and seven days the data is plotted by calculating all data from one hour to on point
        else if(parsedPowerData_.front().first.date().daysTo(parsedPowerData_.back().first.date()) > 1)
        {
            powerChart_.get()->addPowerData(medianHourData(parsedPowerData_), chartName_, "hh:ss");//medianDateData(parsedPowerData_),medianHourData(parsedPowerData_),parsedPowerData_
        }
        //Plots all data as it is from the API
        else
        {
            powerChart_.get()->addPowerData(parsedPowerData_, chartName_, "hh:ss");
        }
    }

}

void PowerModel::drawExtraLine()
{
    if (!isEmpty)
    {
        averageValue(parsedPowerData_);

        emit averageChangedSecondary();
        emit minChangedSecondary();
        emit maxChangedSecondary();

        //If the data is for a period of more than seven days the data is plotted by calculating all data from one day to one point
        if(parsedPowerData_.front().first.date().daysTo(parsedPowerData_.back().first.date()) >= 7)
        {
            powerChart_.get()->addExtraPowerData(medianDateData(parsedPowerData_), chartName_, "dd-MM");
        }
        //If the data is between one and seven days the data is plotted by calculating all data from one hour to on point
        else if(parsedPowerData_.front().first.date().daysTo(parsedPowerData_.back().first.date()) > 1)
        {
            powerChart_.get()->addExtraPowerData(medianHourData(parsedPowerData_), chartName_, "hh:ss");//medianDateData(parsedPowerData_),medianHourData(parsedPowerData_),parsedPowerData_
        }
        //Plots all data as it is from the API
        else
        {
            powerChart_.get()->addExtraPowerData(parsedPowerData_, chartName_, "hh:ss");
        }
    }
}

void PowerModel::clearAll()
{
    powerChart_->clearData();

    stats_.get()->changePhase(0);

    parsedPowerData_.clear();
    calculateTotal(true);
    emit averageChanged();
    emit minChanged();
    emit maxChanged();
    emit averageChangedSecondary();
    emit minChangedSecondary();
    emit maxChangedSecondary();
    emit precentageChanged();
}

void PowerModel::setPowerChart(std::shared_ptr<PowerChart> powerChart)
{
    powerChart_ = powerChart;
}

void PowerModel::setChartName(QString name)
{
    chartName_ = name;
}

float PowerModel::calculateAverage()
{
    if(parsedPowerData_.size()!=0)
    {
        average_ = averageValue(parsedPowerData_);
    }
    else
    {
        //If there is no data
        return 0;
    }
    return average_;
}

float PowerModel::calculateMin()
{
    if(parsedPowerData_.size()!=0)
    {
        min_ = minValue(parsedPowerData_);
    }
    else
    {
        //If there is no data
        return 0;
    }
    return min_;
}

float PowerModel::calculateMax()
{
    if(parsedPowerData_.size()!=0)
    {
        max_ = maxValue(parsedPowerData_);
    }
    else
    {
        //If there is no data
        return 0;
    }
    return max_;
}

void PowerModel::calculateTotal(bool mainOrExtra)
{
    if(parsedPowerData_.size() != 0)
    {
        //True = main graph, False = extra graph
        if(mainOrExtra)
        {
            total_ = 0;
            for(const auto &it : medianHourData(parsedPowerData_))
            {
               total_ += it.second;
            }
        }
        else
        {
            secondTotal_ = 0;
            for(const auto &it : medianHourData(parsedPowerData_))
            {
                secondTotal_ += it.second;
            }
        }
    }
    else
    {
        //If there is no data
        total_ = 0;
        secondTotal_ = 0;
    }
}

float PowerModel::calculatePrecentage()
{
    float precentage_ = 0;
    if(total_ != 0){
        precentage_ = (secondTotal_/total_) *100;
    }
    return precentage_;
}

