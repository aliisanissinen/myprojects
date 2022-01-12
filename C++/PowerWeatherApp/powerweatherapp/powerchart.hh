#ifndef POWERCHART_HH
#define POWERCHART_HH

#include <QChart>
#include <QLineSeries>
#include <QObject>

class PowerChart : public QObject
{
    Q_OBJECT
    //Connection to tell UI when new data is added to chart
    Q_PROPERTY(QtCharts::QLineSeries* powerSeries READ getLineSeries WRITE setLineSeries NOTIFY lineSeriesSignal)

public:
    PowerChart(QObject* parent = nullptr);
    virtual ~PowerChart();

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
     * @brief addPowerData, Adds powerData to graph
     * @param powerData
     * @param name = tells the graphs name
     * @param type = tells how to scale the x-axis
     */
    void addPowerData(std::vector<std::pair<QDateTime, float>> powerData, QString name, QString type);

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
    std::pair<float, float> minMaxValue(std::vector<std::pair<QDateTime, float> > powerData);

    /**
     * @brief addExtraPowerData, Adds extraPowerData to same graph as regular powerData
     * @param powerData
     * @param name = tells the graphe name
     * @param type = tells how to scale the x-axis
     */
    void addExtraPowerData(std::vector<std::pair<QDateTime, float>> powerData, QString name, QString type);

    /**
     * @brief clearData clear all graphs from powerChart
     */
    void clearData();
    /**
     * @brief clearNormal clear normal/main graphe
     */
    void clearNormal();
    /**
     * @brief clearExtra clears extra graphe
     */
    void clearExtra();

signals:
    void lineSeriesSignal();

private:
    QtCharts::QLineSeries* lineSeries_;
    QtCharts::QLineSeries* lineSeriesExtra_;
    std::pair<float, float> minMaxPair_;
    bool minMaxPairSet = false;
    bool lineSeriesActive_ = false;
    bool lineSeriesExtraActive_ = false;

};

#endif // POWERCHART_HH
