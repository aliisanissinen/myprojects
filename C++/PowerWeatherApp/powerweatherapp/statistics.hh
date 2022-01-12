#ifndef STATISTICS_HH
#define STATISTICS_HH

#include <QObject>

class Statistics : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString textToUser READ giveMessage NOTIFY textToUserChanged)

public:
    Statistics();
    /**
     * @brief gives right message to Q_PROPERTY -> view
     * @return QString message to user
     */
    QString giveMessage();

    /**
     * @brief sets correct phasenumber to private phaseNumber_
     * @param int number for different messages
     */
    Q_INVOKABLE void changePhase(int number);

signals:
    void textToUserChanged();

private:
    int phaseNumber_ = 0;

};

#endif // STATISTICS_HH
