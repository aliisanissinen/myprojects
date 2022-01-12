#include "powercontroller.hh"

PowerController::PowerController()
{

}

void PowerController::getVariable(QString variable)
{
    variable_ = variable;

    // If variable is for the next 24h data
    if (variable_ == DATA24H_1 || variable_ == DATA24H_2) {
        startDate_ = today();
        endDate_ = startDate_.left(8) +
                QString::number(startDate_.midRef(8, 2).toInt() + 1) +
                startDate_.right(9);
    }
    qDebug() << variable_;
}

void PowerController::getPowerData()
{
    buildURL();
    powerModel_->setChartName(variables_.at(variable_));
    powerModel_->getPowerData(URL_, true);
}

void PowerController::drawExtraData()
{
    buildURL();
    powerModel_->setChartName(variables_.at(variable_));
    powerModel_->getPowerData(URL_, false);
}

void PowerController::clearAll() const
{
    powerModel_->clearAll();
}

void PowerController::setPowerModule(PowerModel* powermodel)
{
    powerModel_ = powermodel;
}

void PowerController::buildURL()
{
    if (variable_ != noVariablePower && startDate_ != UNDEFINED &&
            endDate_ != UNDEFINED) {
        URL_ = "https://api.fingrid.fi/v1/variable/" + variable_ +
                "/events/csv?start_time=" + startDate_ + "Z&end_time=" +
                endDate_ + "Z";
        qDebug() << URL_;
    }

    else {
        stats_.get()->changePhase(2);
        qDebug() << "StarDate, EndDate or variable not defined";
    }
}

void PowerController::saveData(QString filename) const
{
    powerModel_->saveData(filename);
}

void PowerController::importData(QString filename) const
{
    powerModel_->dataChanged(powerModel_->importData(filename));
    powerModel_->setChartName("Imported data");
}
