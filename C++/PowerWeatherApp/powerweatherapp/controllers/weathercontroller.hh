#ifndef WEATHERCONTROLLER_HH
#define WEATHERCONTROLLER_HH

#include "controller.hh"
#include "models/weathermodel.hh"

#include <QObject>
#include <QTime>
#include <QDebug>


class WeatherController : public Controller
{
    Q_OBJECT
public:
    const QString noVariableWeather = "weather";

    /**
    * @brief Constructor
    */
    explicit WeatherController();

    /**
    * @brief Get the variable from the view
    * @param Variable string
    * @param The boolean value of whether data is predicted or actual
    */
    Q_INVOKABLE void getVariable(QString variable, bool predicted);

    /**
    * @brief Get the city from the view
    * @param City
    */
    Q_INVOKABLE void getCity(QString city);

    /**
    * @brief Send the data header to the model and request it to
    * search the right data
    */
    Q_INVOKABLE void getWeatherData();

    /**
    * @brief Set weathermodel to the class variables
    * @param Pointer to the weathermodel
    */
    void setWeatherModule(WeatherModel* weathermodel);

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

    /**
    * @brief Clear the current data from the model
    */
    Q_INVOKABLE void clearAll() const override;

private:
    // The data headers of the current variables
    std::map<QString, QString> variables_ =
                            {{"weather","Weather"},
                            {"Temperature", "Temperature"},
                            {"WindSpeedMS","Wind speed"},
                            {"TotalCloudCover", "Total cloud cover"}};

    // The data headers of the predicted variables
    std::map<QString, QString> variablesPredicted_ =
                            {{"weather","Weather"},
                            {"WindSpeedMS","Predicted wind speed"},
                            {"Temperature", "Predicted temperature"}};

    WeatherModel* weatherModel_;
    QString variable_ = noVariableWeather;
    QString city_;
    QString URL_;

};

#endif // WEATHERCONTROLLER_HH
