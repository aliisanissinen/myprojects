#include "dataparser.hh"
#include <QtDebug>
#include <QDateTime>
DataParser::DataParser()
{
}
std::vector<std::pair<QDateTime, float>> DataParser::parseFmiXml(QString& data)
{
    const int LAST_CHARACTERS = 59;

    QString str = "<BsWfs:ParameterValue>";
    QString str1 = "<wfs:member>";
    QString str2 = "<BsWfs:Time>";
    QString str3 = "</wfs:member>";

    QStringList temporary_list;
    temporary_list = data.split(str1);
    temporary_list.removeFirst();
    QString rejoined = temporary_list.join(" ");
    temporary_list = rejoined.split(str3);
    temporary_list.removeLast();

    std::vector<std::pair<QDateTime, float>> weatherData;

    for (int i = 0; i < temporary_list.size(); i++){

        QString startTime = temporary_list.at(i).mid(temporary_list.at(i).indexOf(str2)+str2.size(),20);
        QDateTime date = QDateTime::fromString (startTime,"yyyy-MM-ddThh:mm:ssZ");
        QString temp = temporary_list.at(i);
        temp.chop(LAST_CHARACTERS);
        float temperature = temp.midRef(temporary_list.at(i).indexOf(str)+str.size()).toFloat();
        if (std::to_string(temperature) != "nan"){
            std::pair<QDateTime, float> pair = std::make_pair(date, temperature);
            weatherData.push_back(pair);
        }
    }
    //qDebug() << weatherData;
    qDebug() << "DataParser::parseXML()";
    return weatherData;
}

std::vector<std::pair<QDateTime, float> > DataParser::parseHirlamXml(QString& data)
{
    const int LAST_CHARACTERS = 90;

    QString str = "<wml2:value>";
    QString str1 = "<wml2:point>";
    QString str2 = "<wml2:time>";
    QString str3 = "</wml2:point>";

    QStringList temporary_list;
    temporary_list = data.split(str1);
    temporary_list.removeFirst();
    QString rejoined = temporary_list.join(" ");
    temporary_list = rejoined.split(str3);
    temporary_list.removeLast();

    std::vector<std::pair<QDateTime, float>> weatherData;

    for (int i = 0; i < temporary_list.size(); i++){

        QString startTime = temporary_list.at(i).mid(temporary_list.at(i).indexOf(str2)+str2.size(),20);
        QDateTime date = QDateTime::fromString (startTime,"yyyy-MM-ddThh:mm:ssZ");
        QString temp = temporary_list.at(i);
        temp.chop(LAST_CHARACTERS);
        float temperature = temp.midRef(temporary_list.at(i).indexOf(str)+str.size()).toFloat();
        if (std::to_string(temperature) != "nan"){
            std::pair<QDateTime, float> pair = std::make_pair(date, temperature);
            weatherData.push_back(pair);
        }
    }
    //qDebug() << weatherData;
    qDebug() << "DataParser::parseXML()";
    return weatherData;
}

std::vector<std::pair<QDateTime, float>> DataParser::parseCsv(QString& data)
{
    const int LAST_CHARACTERS = 19;

    QStringList strings = data.split('\n');
    std::vector<std::pair<QDateTime, float>> powerData;


    for(int i = 1; i < strings.size() - 1; i++){
        QStringList line = strings.at(i).split(',');
        QString time = line.at(0).left(LAST_CHARACTERS); //Changed to date
        QDateTime date = QDateTime::fromString(time, "yyyy-MM-ddThh:mm:ss");
        float value = line.at(2).toFloat();

        std::pair<QDateTime, float> pair= std::make_pair(date, value);
        powerData.push_back(pair);
    }

    //qDebug() << powerData;
    qDebug() << "DataParser::parseCsv";
    return powerData;
}
