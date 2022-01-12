#include "powerapireader.hh"
#include "statistics.hh"
#include <QThread>

PowerAPIReader::PowerAPIReader()
{

}

void PowerAPIReader::fetchData(QString input)
{
    QNetworkRequest request;
    request.setUrl(QUrl(input));
    request.setRawHeader("x-api-key", "sp26WtGsEf9rOyOcKInrC3h4CK6RKc517zut8MKX");
    manager_->get(QNetworkRequest(request));
}

