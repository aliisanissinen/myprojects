#ifndef WeatherAPIReader_HH
#define WeatherAPIReader_HH

#include "apireader.hh"
#include <QObject>

class WeatherAPIReader : public APIReader
{
    Q_OBJECT
public:
    WeatherAPIReader();

    /**
     * @brief method for fetching Power data
     * @param QString contains URL
     */
    void fetchData(QString input) override;
};

#endif // WeatherAPIReader_HH
