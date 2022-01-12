#ifndef POWERCONTROLLER_HH
#define POWERCONTROLLER_HH

#include "controller.hh"
#include "models/powermodel.hh"

#include "statistics.hh"

#include <QObject>
#include <QDebug>
#include <QTime>


class PowerController : public Controller
{
    Q_OBJECT
public:
    const QString DATA24H_1 = "165";
    const QString DATA24H_2 = "242";
    const QString noVariablePower = "power";

    /**
    * @brief Constructor
    */
    explicit PowerController();

    /**
    * @brief Get the variable from the view
    * @param Variable number
    */
    Q_INVOKABLE void getVariable(QString variable);

    /**
    * @brief Send the data header to the model and request it to
    * search the right data
    */
    Q_INVOKABLE void getPowerData();

    /**
    * @brief Send the data header of the second search to the model and
    * request it to search the right data / Only used when drawing two line
    * plots in the same window
    */
    Q_INVOKABLE void drawExtraData();

    /**
    * @brief Clear the current data from the model
    */
    Q_INVOKABLE void clearAll() const override;

    /**
    * @brief Set powermodel to the class variables
    * @param Pointer to the powermodel
    */
    void setPowerModule(PowerModel* powermodel);

    /**
    * @brief Build the URL to the model
    */
    void buildURL() override;

    /**
    * @brief Request model to save the current power data as txt format
    * @param The filename, given by the user
    */
    Q_INVOKABLE void saveData(QString filename) const override;

    /**
    * @brief Request model to show the imported power data in the chart
    * @param The filename, given by the user
    */
    Q_INVOKABLE void importData(QString filename) const override;

private:
    // The data headers of the variables
    std::map<QString, QString> variables_ =
                            {{"power","Power"},
                            {"124", "Electricity consumption"},
                            {"165", "Electricity consumption forecast"},
                            {"242", "Tentative production forecast"},
                            {"192", "Electricity production"},
                            {"181", "Wind power production forecast"},
                            {"188", "Nuclear power production"},
                            {"191", "Hydro power production"}};

    PowerModel* powerModel_;
    QString variable_ = noVariablePower;
    QString URL_;

};

#endif // POWERCONTROLLER_HH
