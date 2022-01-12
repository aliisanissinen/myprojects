#ifndef DATAPARSER_HH
#define DATAPARSER_HH

#include <QString>
#include <vector>
#include <QDate>

class DataParser
{

public:
    DataParser();

    /**
    * @brief Parse XML data to easier form. (weatherData_ changed)
    * @pre only XML type data (weatherdata)
    * @post Exception guarantee: strong
    * @return vector including pair of time and float value
    */
    std::vector<std::pair<QDateTime, float>> parseFmiXml(QString& data);

    /**
    * @brief Parse predicted XML data to easier form. (weatherData_ changed)
    * @pre only XML type data (weatherdata)
    * @post Exception guarantee: strong
    * @return vector including pair of time and float value
    */
    std::vector<std::pair<QDateTime, float>> parseHirlamXml(QString& data);

    /**
    * @brief Parse CSV data to easier form. (powerData_ changed)
    * @pre only csv type data (powerdata)
    * @post Exception guarantee: strong
    * @return vector including pair of time and float value
    */
    std::vector<std::pair<QDateTime, float>> parseCsv(QString& data);

};

#endif // DATAPARSER_HH
