#include <QtTest>
#include "../Game/statistics.hh"

// add necessary includes here

class StatisticsUnitTest : public QObject
{
    Q_OBJECT

public:
    StatisticsUnitTest();
    ~StatisticsUnitTest();

private slots:
    void testPoints();
    void testLevel();
    void testReadData();

};

StatisticsUnitTest::StatisticsUnitTest()
{
}

StatisticsUnitTest::~StatisticsUnitTest()
{
}

void StatisticsUnitTest::testPoints()
{
    Statistics s;

    s.addPoints(1);
    QCOMPARE(s.givePoints(), 1);

    s.addPoints(2);
    QCOMPARE(s.givePoints(), 3);

    s.addPoints(5);
    QCOMPARE(s.givePoints(), 8);

}

void StatisticsUnitTest::testLevel()
{
    Statistics s;
    s.getLevel(1);
    QCOMPARE(s.giveLevel(), 1);

    s.getLevel(2);
    QCOMPARE(s.giveLevel(), 2);
}

void StatisticsUnitTest::testReadData()
{
    Statistics s;
    s.getLevel(1);
    s.readData();
    std::map<int, std::string> top10 = s.giveData();

    for (std::pair<int, std::string> pair: top10) {
        int points = pair.first;
        std::string name = pair.second;
        QVERIFY2(points >= 0, "Points less than zero");
        QVERIFY2(!name.empty(), "Name is empty");
    }

    s.getLevel(2);
    s.readData();
    std::map<int, std::string> top10_2 = s.giveData();

    for (std::pair<int, std::string> pair: top10_2) {
        int points = pair.first;
        std::string name = pair.second;
        QVERIFY2(points >= 0, "Points less than zero");
        QVERIFY2(!name.empty(), "Name is empty");
    }

    s.getLevel(3);
    s.readData();
    std::map<int, std::string> top10_3 = s.giveData();

    for (std::pair<int, std::string> pair: top10_3) {
        int points = pair.first;
        std::string name = pair.second;
        QVERIFY2(points >= 0, "Points less than zero");
        QVERIFY2(!name.empty(), "Name is empty");
    }

}

QTEST_APPLESS_MAIN(StatisticsUnitTest)

#include "StatisticsUnitTest.moc"
