#ifndef APIREADER_HH
#define APIREADER_HH

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

class APIReader: public QObject
{
    Q_OBJECT

public:
    APIReader();

    /**
     * @brief virtual method for fetching data
     * @param QString contains URL
     */
    virtual void fetchData(QString input) = 0;

protected:
    QString rawData_;
    QNetworkAccessManager *manager_;


protected slots:
    void replyFinished(QNetworkReply *reply);

signals:
    void newDataReady(QString newData); // This signals outside when data is ready

};

#endif // APIREADER_HH
