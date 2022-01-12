#include "weatherapireader.hh"

WeatherAPIReader::WeatherAPIReader()
{

}

void WeatherAPIReader::fetchData(QString input)
{
    QNetworkRequest request;
    request.setUrl(QUrl(input));
    manager_->get(QNetworkRequest(request));
}
