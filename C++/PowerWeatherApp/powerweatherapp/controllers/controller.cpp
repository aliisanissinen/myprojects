#include "controller.hh"


Controller::Controller(QObject *parent) : QObject(parent)
{

}

void Controller::setStatistics(std::shared_ptr<Statistics> stats)
{
    stats_ = stats;
}

QString Controller::today()
{
    QDateTime time = QDateTime::currentDateTime();
    QString formattedTime = time.toString("yyyy-MM-ddThh:mm:ss");
    return formattedTime;
}

void Controller::getStartDate(QString date)
{
    if (date == UNDEFINED) {
        startDate_ = date;
    }
    else {
        startDate_ = date + STARTTIME;
    }
    qDebug() << startDate_;
}

void Controller::getEndDate(QString date)
{
    if (date == UNDEFINED) {
        endDate_ = date;
    }
    // If the date is today, the time needs to be current not 00:00
    else if (today().left(10) == date) {
        endDate_ = today();
    }
    else {
        endDate_ = date + ENDTIME;
    }
    qDebug() << endDate_;
}
