#ifndef GAMEWINDOW_HH
#define GAMEWINDOW_HH

#include "actors/drone.hh"
#include "interfaces/iactor.hh"
#include "actors/busitem.h"
#include "actors/passengeritem.h"
#include "actors/stopitem.h"
#include "actors/vaccine.h"
#include "dialog.hh"
#include "statistics.hh"
#include "tampere.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsItem>
#include <QWidget>
#include <QTime>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QDebug>

class Drone;
class Tampere;

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
    * @brief Constructor
    */
    explicit GameWindow(QWidget *parent = 0);

    /**
    * @brief Deconstructor
    */
    ~GameWindow();

    /**
    * @brief Set window size
    * @pre w > o && h > 0
    * @post Exception guarantee: basic.
    */
    void setSize(int w, int h);

    /**
    * @brief Set tick
    * @pre t > 0
    * @post Exception guarantee: basic.
    */
    void setTick(int t);

    /**
    * @brief Gets info from dialog, the player name and level
    * @pre pair.second > 0 && pair.second <=3
    * @post Exception guarantee: basic.
    */
    void getInfo(std::pair<QString, int> info);

    /**
    * @brief Show time in the gamewindow
    * @post Exception guarantee: strong.
    */
    void showTime();

    /**
    * @brief Show top5 in the gamewindow
    * @post Exception guarantee: basic.
    */
    void top5();

    /**
    * @brief Add actors to map, passengers and busses
    * @pre type > 0 && type <=2
    * @post Exception guarantee: basic.
    */
    void addActor(int locX, int locY, int type,
                  std::shared_ptr<Interface::IActor> actor);

    /**
    * @brief Add stops to map
    * @pre type == 3
    * @post Exception guarantee: basic.
    */
    void addStop(int locX, int locY, int type,
                 std::shared_ptr<Interface::IStop> stop);

    /**
    * @brief Add drone to map
    * @post Exception guarantee: basic.
    */
    void addDrone();

    /**
    * @brief Updates actors coordinates in the map
    * @pre nX > 0 && nX < 1095, nY > 0 && nY < 592
    * @post Exception guarantee: basic.
    */
    void updateCoords(int nX, int nY);

    /**
    * @brief Gets city from the engine class
    * @pre t_ is Tampere class
    * @post Exception guarantee: basic.
    */
    void getCity(std::shared_ptr<Tampere> t_);

    /**
    * @brief Sets picture to the map
    * @pre Image pointer to Tampere picture
    * @post Exception guarantee: strong.
    */
    void setPicture(QImage &img);

    /**
    * @brief Find actor from the map and put it to the last_
    * @pre Actor pointer is not nullptr
    * @return True if found, else false
    * @post Exception guarantee: strong.
    */
    bool findVisualActor(std::shared_ptr<Interface::IActor> actor);

    /**
    * @brief Removes actor from the map
    * @post Exception guarantee: basic.
    */
    void removeActor();

    /**
    * @brief Randomly turn actors into viruses
    * @post Exception guarantee: basic.
    */
    void randomVirus();

    /**
    * @brief Randomly puts vaccine to map
    * @post Exception guarantee: basic.
    */
    void randomVaccine();

    /**
    * @brief Drone shoots
    * @post Exception guarantee: basic.
    */
    void shoot();

    /**
    * @brief The game ends, all Timers stop, and the end game label shows up
    * @post Exception guarantee: strong.
    */
    void gameEnd();

signals:
    void gameStarted();

private slots:

    void on_startButton_clicked();
    void on_pauseButton_clicked();
    void on_stopButton_clicked();


private:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

    Ui::GameWindow *ui;
    Statistics *s_;
    QGraphicsScene *map;
    QTimer *timer;
    QVector<ActorItem*> actors_;
    ActorItem* last_;
    Drone *drone_;

    QVector<BusItem*> busses_;
    QVector<PassengerItem*> passengers_;
    QVector<StopItem*> stops_;
    QVector<ActorItem*>viruses_;
    Vaccine* vaccine_ = nullptr;

    // All images here, otherwise there will be memory problems
    const QImage busImage = QImage(":/Pics/Pics/bus.png");
    const QImage stopImage = QImage(":/Pics/Pics/stop3.png");
    const QImage passengerImage = QImage(":/Pics/Pics/human.png");
    const QImage vaccineImage = QImage(":/Pics/Pics/vaccine.png");

    int width_ = 1095;
    int height_ = 592;
    int tick_ = 500;

    QTimer *gameTime_;
    QTimer* randomTime_;
    int gameSeconds_ = 0;
    std::shared_ptr<Tampere> city_;
    bool keyPressActive = false;
    int level_;
    int levelTime_;
};

#endif // GAMEWINDOW_HH
