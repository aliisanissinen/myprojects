#include "apireader.hh"


APIReader::APIReader()
{
    manager_ = new QNetworkAccessManager(this);
    connect(manager_, &QNetworkAccessManager::finished, this, &APIReader::replyFinished);
}


void APIReader::replyFinished(QNetworkReply *reply)
{
    if(!reply->error())
    {
        rawData_ = QString(reply->readAll());
        reply->deleteLater();
    }
    else
    {
        qDebug() << "APIReader::replyFinished something went wrong!";
        rawData_ = "";
    }

    emit newDataReady(rawData_); // Signal outside that data is ready.
}
