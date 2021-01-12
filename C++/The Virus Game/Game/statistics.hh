#ifndef STATISTICS_HH
#define STATISTICS_HH

#include <QString>
#include <map>
#include <string>
#include <QDebug>
#include <QFile>

class Statistics
{
public:
    /**
    * @brief Constructor
    */
    Statistics();

    /**
    * @brief Deconstructor
    */
    ~Statistics();

    /**
    * @brief Get level that has chosen in the dialog window
    * @pre level > 0 && level <= 3
    * @post Exception guarantee: basic.
    */
    void getLevel(int level);

    /**
    * @brief Get name that has chosen in the dialog window
    * @pre -
    * @post Exception guarantee: strong.
    */
    void getName(QString name);

    /**
    * @brief Add points
    * @pre points > 0
    * @post Exception guarantee: basic.
    */
    void addPoints(int points);

    /**
    * @brief Reads the data from scorefile (scoreData)
    * @post Exception guarantee: basic.
    */
    void readData();

    /**
    * @brief Writes data to the scorefile (scoreData)
    * @post Exception guarantee: basic.
    */
    void writeData();

    /**
    * @brief Gives the scoredata
    * @return Map with top10 names and points
    * @post Exception guarantee: basic.
    */
    std::map<int, std::string> giveData();

    /**
    * @brief Gives the current points
    * @return Points
    * @post Exception guarantee: nothrow.
    */
    int givePoints();

    /**
    * @brief Gives the level
    * @return Level, level > 0 && level <=3
    * @post Exception guarantee: nothrow.
    */
    int giveLevel();


private:

    std::string playerName_;
    int points_ = 0;
    int level_ = 1;

    QString filecontent_;
    std::map<int, std::string> topScore_;

    /**
    * @brief Check that parameters are invariant, points => 0 &&
    * level > 0 && level <=3
    */
    void invariant() const;
};

#endif // STATISTICS_HH
