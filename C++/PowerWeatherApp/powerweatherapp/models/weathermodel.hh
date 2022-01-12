#ifndef WEATHERMODEL_HH
#define WEATHERMODEL_HH

#include <QObject>
#include <QDate>
#include "dataparser.hh"
#include "apireaders/weatherapireader.hh"
#include "weatherchart.hh"
#include "model.hh"

class WeatherModel : public Model
{
    Q_OBJECT

    // Signals for updating UI
    Q_PROPERTY(float weatherAverage READ calculateAverage NOTIFY averageChanged)
    Q_PROPERTY(float weatherMin READ calculateMin NOTIFY minChanged)
    Q_PROPERTY(float weatherMax READ calculateMax NOTIFY maxChanged)


public:
    WeatherModel();
    /**
     * @brief getWeatherData
     * @param input is the generated URL
     */
    void getWeatherData(QString input);
    /**
     * @brief drawData draws the data to chart
     */
    void drawData();
    /**
     * @brief clear all data from chart and reset all values to zero
     */
    void clearAll();
    /**
     * @brief setWeatherChart set weatherChart pointer to private variable
     * @param weatherChart pointer to weatherChart
     */
    void setWeatherChart(std::shared_ptr<WeatherChart> WeatherChart);
    /**
     * @brief setChartName set name to chart
     * @param name is the chart name
     */
    void setChartName(QString name);
    /**
     * @brief calculateAverage
     * @return average production
     */
    float calculateAverage();
    /**
     * @brief calculateMin
     * @return minimum value of given data
     */
    float calculateMin();
    /**
     * @brief calculateMax
     * @return maximum value of given data
     */
    float calculateMax();

public slots:
    /**
     * @brief dataChanged callback function where fetched data returns when it is ready
     * @param newData fetched data
     */
    void dataChanged(QString newData);

signals:

    void averageChanged();
    void minChanged();
    void maxChanged();

private:

    std::shared_ptr<WeatherChart> WeatherChart_;
    std::vector<std::pair<QDateTime, float>> parsedWeatherData_;

    DataParser parser_;
    WeatherAPIReader reader_;

    QString chartName_;

    float average_ = 0;
    float min_ = 0;
    float max_ = 0;

    bool isEmpty = true;

};
#endif // WeatherMODEL_HH
