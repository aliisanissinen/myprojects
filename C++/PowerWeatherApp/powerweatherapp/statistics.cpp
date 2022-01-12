#include "statistics.hh"
#include <QDebug>

Statistics::Statistics()
{

}
QString Statistics::giveMessage()
{
    switch(phaseNumber_) {
    case 1:
         return "You can import and save data from buttons above.\nYou can also draw extra line for power data by pressing draw extra line - button. Try it!";
    case 2:
        return "Check your start date, end date and one power checkbox is selected.";
    case 3:
        return "Check your start date, end date and one weather checkbox is selected. \n Also remember to write city.";
    case 4:
        return "Data saved!";
    case 5:
        return "Data imported!";
    case 6:
        return "Check file name!";
    case 7:
        return "Image saved!";
    case 8:
        return "Wrong datatype!";
    default:
        return "Welcome to Power Weather App!";
    }
}

void Statistics::changePhase(int number)
{
    phaseNumber_ = number;
    emit textToUserChanged();
}
