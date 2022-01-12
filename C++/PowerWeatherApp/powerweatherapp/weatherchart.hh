#ifndef WEATHERCHART_HH
#define WEATHERCHART_HH

#include <QChart>
#include <QLineSeries>
#include <QObject>

class WeatherChart : public QObject
{
    Q_OBJECT
    //Connection to tell UI when new data is added to chart
    Q_PROPERTY(QtCharts::QLineSeries* weatherSeries READ getLineSeries WRITE setLineSeries NOTIFY lineSeriesSignal)

public:
    WeatherChart(QObject* parent = nullptr);
    virtual ~WeatherChart();

    /**
     * @brief getLineSeries
     * @return pointer to linseSeries_
     */
    QtCharts::QLineSeries* getLineSeries() const;

    /**
     * @brief setLineSeries creates new lineSeries
     * @param lineSeries
     */
    void setLineSeries(QtCharts::QLineSeries *lineSeries);

    /**
     * @brief addWeatherData, Adds weatherData to graph
     * @param weatherData
     * @param name = tells the graphs name
     * @param type = tells how to scale the x-axis
     */
    void addWeatherData(std::vector<std::pair<QDateTime, float>> WeatherData, QString name, QString type);

    /**
     * @brief setAxis, sets the y- and x-axis
     * @param start = startDate
     * @param end = endDate
     * @param minMaxPair = min y- and x-axis value
     * @param type = tells how to scale the x-axis
     */
    void setAxis(QDateTime start, QDateTime end, std::pair<float, float> minMaxPair, QString type);

    /**
     * @brief minMaxValue finds the min and max value for given data
     * @param powerData
     * @return minMaxPair = first value is the min value and second value is max value
     */
    std::pair<float, float> minMaxValue(std::vector<std::pair<QDateTime, float> > WeatherData);

    /**
     * @brief clearData clear all graphs from weatherChart
     */
    void clearData();

signals:
    void lineSeriesSignal();

private:
    QtCharts::QLineSeries* lineSeries_;

};

#endif // WEATHERCHART_HH
