#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include "models/model.hh"

#include <QObject>
#include <QDebug>
#include <QTime>

class Controller : public QObject
{
    Q_OBJECT
public:
    const QString UNDEFINED = "undefined";
    const QString STARTTIME= "T00:00:00";
    const QString ENDTIME= "T23:59:59";

    /**
    * @brief Constructor
    */
    Controller(QObject *parent = nullptr);

    /**
    * @brief Set Statistics to the class variables
    * @param Pointer to the statistics
    */
    void setStatistics(std::shared_ptr<Statistics> stats);

    /**
    * @brief Give today's date
    * @return Today's date, format is yyyy-MM-ddThh:mm:ss
    */
    QString today();

    /**
    * @brief Get the startdate from the view
    * @param Startdate, format yyyy-MM-dd
    */
    Q_INVOKABLE void getStartDate(QString date);

    /**
    * @brief Get the enddate from the view
    * @param Enddate, format yyyy-MM-dd
    */
    Q_INVOKABLE void getEndDate(QString date);

    /**
    * @brief Build the URL to the models
    */
    virtual void buildURL() = 0;

    /**
    * @brief Request model to save the current power data as txt format
    * @param The filename, given by the user
    */
    virtual void saveData(QString filename) const = 0;

    /**
    * @brief Request model to show the imported power data in the chart
    * @param The filename, given by the user
    */
    virtual void importData(QString filename) const = 0;

    /**
    * @brief Clear the current data from the model
    */
    virtual void clearAll() const = 0;

protected:
    // If dates are not picked from view, dates are undefined
    QString startDate_ = "undefined";
    QString endDate_ = "undefined";
    std::shared_ptr<Statistics> stats_;
};

#endif // CONTROLLER_HH
