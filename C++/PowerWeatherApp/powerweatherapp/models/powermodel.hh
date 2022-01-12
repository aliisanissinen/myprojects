#ifndef POWERMODEL_HH
#define POWERMODEL_HH

#include <QObject>
#include <QDate>
#include "dataparser.hh"
#include "apireaders/powerapireader.hh"
#include "powerchart.hh"
#include "model.hh"

#include "statistics.hh"

class PowerModel : public Model
{
    Q_OBJECT

    //Signals for updating UI
    Q_PROPERTY(float powerAverage READ calculateAverage NOTIFY averageChanged)
    Q_PROPERTY(float powerMin READ calculateMin NOTIFY minChanged)
    Q_PROPERTY(float powerMax READ calculateMax NOTIFY maxChanged)
    Q_PROPERTY(float powerAverageSecondary READ calculateAverage NOTIFY averageChangedSecondary)
    Q_PROPERTY(float powerMinSecondary READ calculateMin NOTIFY minChangedSecondary)
    Q_PROPERTY(float powerMaxSecondary READ calculateMax NOTIFY maxChangedSecondary)
    Q_PROPERTY(float powerPrecentage READ calculatePrecentage NOTIFY precentageChanged)

public:
    PowerModel();
    /**
     * @brief getPowerData
     * @param input is the URL
     * @param extra is boolen variable that controlls where the data is plotted
     *        if true plots main graphe, false plots extra graphe
     */
    void getPowerData(QString input, bool extra);

    /**
     * @brief drawData draws the data to chart
     */
    void drawData();

    /**
     * @brief drawExtraLine draw the extra line to same chart
     */
    void drawExtraLine();

    /**
     * @brief clearAll all data from chart and resets all values to zero
     */
    void clearAll();

    /**
     * @brief setPowerChart set powerChart pointer to private variable
     * @param powerChart pointer to powerChart
     */
    void setPowerChart(std::shared_ptr<PowerChart> powerChart);

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

    /**
     * @brief calculateTotal, calculates total production of given time period
     * @param mainOrExtra true = main grapge, false = extra graphe
     */
    void calculateTotal(bool mainOrExtra);

    /**
     * @brief calculatePrecentage, calculates precentage difference between two graphe
     * @return precentage difference
     */
    float calculatePrecentage();


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

    void averageChangedSecondary();
    void minChangedSecondary();
    void maxChangedSecondary();

    void precentageChanged();

private:

    std::shared_ptr<PowerChart> powerChart_;
    std::vector<std::pair<QDateTime, float>> parsedPowerData_;

    QString chartName_;

    DataParser parser_;
    PowerAPIReader reader_;

    float average_ = 0;
    float min_ = 0;
    float max_ = 0;
    float total_ = 0;
    float secondTotal_ = 0;
    float precentage_ = 0;

    bool extra_ = false;
    bool isEmpty = true;

};
#endif // POWERMODEL_HH
