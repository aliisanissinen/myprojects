#ifndef MODEL_HH
#define MODEL_HH

#include <QObject>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QDateTime>
#include "statistics.hh"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    /**
    * @brief Set Statistics to the class variables
    * @param Pointer to the statistics
    */
    void setStatistics(std::shared_ptr<Statistics> stats);

    /**
     * @brief getRawData
     * @return rawData (same format as it came from API, powerData = csv and weatherData = xml)
     */
    QString getRawData();
    /**
     * @brief saveData save the data to file
     * @param filename name of the file where data is saved
     */
    void saveData(QString filename);
    /**
     * @brief importData imports data from file
     * @param filename name of the file that you want to import
     * @return the imported data as QString (File is .txt and accepted format are csv (Fingrid) and xml(Ilmatieteen laitois))
     */
    QString importData(QString filename);
    /**
     * @brief medianHourData calculates all data points inside one hour to one hour point
     * @param data
     * @return data that has point count reduced to hours
     */
    std::vector<std::pair<QDateTime, float>> medianHourData(std::vector<std::pair<QDateTime, float>> data);
    /**
     * @brief medianDateData calculates all data points inside one day to one date point
     * @param data
     * @return data that has point count reduced to day
     */
    std::vector<std::pair<QDateTime, float>> medianDateData(std::vector<std::pair<QDateTime, float>> data);
    /**
     * @brief minValue find minimum value from given data
     * @param data
     * @return minValue
     */
    float minValue(std::vector<std::pair<QDateTime, float>> data);
    /**
     * @brief maxValue  find maximum value from given data
     * @param data
     * @return maxValue
     */
    float maxValue(std::vector<std::pair<QDateTime, float>> data);
    /**
     * @brief averageValue calculates average to given data
     * @param data
     * @return averegaeValue
     */
    float averageValue(std::vector<std::pair<QDateTime, float>> data);
    /**
     * @brief roundFloats to 2 decimals
     * @param var variable to round
     * @return rounded variable
     */
    float roundFloats(float var);


protected:
    QString rawData_;   
    std::shared_ptr<Statistics> stats_;

};

#endif // MODEL_HH
