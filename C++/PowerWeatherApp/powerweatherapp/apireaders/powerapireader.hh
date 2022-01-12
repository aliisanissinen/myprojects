#ifndef PowerAPIReader_HH
#define PowerAPIReader_HH

#include "apireader.hh"
#include <QObject>

class PowerAPIReader : public APIReader
{
    Q_OBJECT
public:
    PowerAPIReader();

    /**
     * @brief method for fetching Power data
     * @param QString contains URL
     */
    void fetchData(QString input) override;

};

#endif // PowerAPIReader_HH
