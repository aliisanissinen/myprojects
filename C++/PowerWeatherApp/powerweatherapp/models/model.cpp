#include "model.hh"
#include <math.h>

Model::Model(QObject *parent) : QObject(parent)
{

}

void Model::setStatistics(std::shared_ptr<Statistics> stats)
{
    stats_ = stats;
}

QString Model::getRawData()
{
    return rawData_;
}


void Model::saveData(QString filename)
{
    const QString path("./savedFiles/");
    qDebug()<< filename;
    QFile file(path + filename + ".txt");

    if(filename == ""){
        stats_.get()->changePhase(6);
    }
    else if (file.open(QIODevice::WriteOnly)) {
        qDebug()<< "PowerModel::saveData()";
        QTextStream out(&file);
        out << rawData_;
        file.close();

        stats_.get()->changePhase(4);
    }
    else{
        stats_.get()->changePhase(6);
    }
}
QString Model::importData(QString filename)
{
    qDebug()<< "importing data in model, filename: " << filename;

    const QString path("./savedFiles/");

    QString fileName(filename);
    QString loadedData = "";

    QFile file(path + fileName + ".txt");
    if (file.open(QIODevice::ReadOnly)) {
        qDebug()<< "PowerModel::loadData()";
        loadedData = file.readAll();
        file.close();
        stats_.get()->changePhase(5);
    }
    else{
        stats_.get()->changePhase(6);
    }
    return loadedData;
}

std::vector<std::pair<QDateTime, float>> Model::medianHourData(std::vector<std::pair<QDateTime, float>> data)
{
    QDateTime currentDate = data.begin()->first;
    std::vector<std::pair<QDateTime, float>> medianVector;
    float hourData = 0;
    float counter = 0;
    for(const auto &it : data)
    {
        if(it.first.time().hour() == currentDate.time().hour())
        {
            hourData += it.second;
            counter++;
        }
        else
        {
            if(counter != 0)
            {
                medianVector.push_back({currentDate,hourData/counter});
                hourData = 0;
                counter = 0;
                currentDate = it.first;
            }
            else
            {
                return data;
            }
        }
    }
    return medianVector;
}

std::vector<std::pair<QDateTime, float>> Model::medianDateData(std::vector<std::pair<QDateTime, float>> data)
{
    QDateTime currentDate = data.begin()->first;
    std::vector<std::pair<QDateTime, float>> medianVector;
    float dailyDate = 0;
    float counter = 0;
    if(data.front().first.date() != data.back().first.date())
    {
        for(const auto &it : data)
        {
            if(it.first.date() == currentDate.date())
            {
                dailyDate += it.second;
                counter++;
            }
            else
            {
                medianVector.push_back({currentDate,dailyDate/counter});
                dailyDate = 0;
                counter = 0;
                currentDate = it.first;
            }
        }
        return medianVector;
    }
    medianVector = medianHourData(data);
    return medianVector;

}

float Model::minValue(std::vector<std::pair<QDateTime, float> > data)
{
    std::pair<QDateTime, float> min = {data.begin()->first,data.begin()->second};

    for(const auto &it : data)
    {
        if (min.second > it.second)
        {
            min = {it.first,it.second};
        }
    }
    return roundFloats(min.second);
}

float Model::maxValue(std::vector<std::pair<QDateTime, float> > data)
{
    std::pair<QDateTime, float> max = {data.begin()->first,data.begin()->second};

    for(const auto &it : data)
    {
        if(max.second < it.second)
        {
            max = {it.first,it.second};
        }
    }

    return roundFloats(max.second);
}

float Model::averageValue(std::vector<std::pair<QDateTime, float>> data)
{
    float average = 0;
    float counter = 0;
    for(const auto &it : data)
    {
        average += it.second;
        counter++;
    }

    average = average / counter;
    qDebug() << average;
    return roundFloats(average);
}

float Model::roundFloats(float var)
{
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

