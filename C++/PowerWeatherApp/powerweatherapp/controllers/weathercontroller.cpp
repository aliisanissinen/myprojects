#include "weathercontroller.hh"


WeatherController::WeatherController()
{

}

void WeatherController::getVariable(QString variable, bool predicted)
{
    variable_ = variable;

    // If predicted, then data is for the next 48h
    if (predicted) {
        weatherModel_->setChartName(variablesPredicted_.at(variable_));
        startDate_ = today();
        endDate_ = startDate_.left(8) +
                QString::number(startDate_.midRef(8, 2).toInt() + 2)
                + startDate_.right(9);
    }
    else {
        weatherModel_->setChartName(variables_.at(variable_));
    }
    qDebug() << variable_;
}

void WeatherController::getCity(QString city)
{
    city_ = city;
}

void WeatherController::getWeatherData()
{
    buildURL();
    weatherModel_->getWeatherData(URL_);
}

void WeatherController::setWeatherModule(WeatherModel *weathermodel)
{
    weatherModel_ = weathermodel;
}

void WeatherController::buildURL()
{

    if (variable_ != noVariableWeather && city_ != NULL &&
            startDate_ != UNDEFINED && endDate_ != UNDEFINED &&
            (endDate_ < today())) {
        URL_ = "https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0"
               "&storedquery_id=fmi::observations::weather::simple&place=" +
                city_ + "&timestep=10&parameters=" + variable_ + "&starttime=" +
                startDate_ + "Z&endtime=" + endDate_ + "Z&";
        qDebug() << URL_;
    }

    // If data is predicted
    if (variable_ != noVariableWeather && city_ != NULL &&
            startDate_ != UNDEFINED && endDate_ != UNDEFINED &&
            (endDate_ > today()) ) {
        URL_ = "http://opendata.fmi.fi/wfs?service=WFS&version=2.0.0"
                "&request=getFeature&storedquery_id=fmi::forecast::hirlam::"
               "surface::point::timevaluepair&place=" + city_ +
                "&timestep=60&parameters=" + variable_;
        qDebug() << URL_ << (endDate_ > today()) << startDate_ << endDate_;

        // Start and enddate to UNDEFINED, so one can't do a new query in to
        // the future with non-predicted types
        startDate_ = UNDEFINED;
        endDate_ = UNDEFINED;
    }

    else {
        stats_.get()->changePhase(3);
        qDebug() << "StarDate, EndDate, Variable or City not defined";
    }
}

void WeatherController::saveData(QString filename) const
{
    weatherModel_->saveData(filename);
}

void WeatherController::importData(QString filename) const
{
    weatherModel_->dataChanged(weatherModel_->importData(filename));
    weatherModel_->setChartName("Imported data");
}

void WeatherController::clearAll() const
{
    weatherModel_->clearAll();
}
