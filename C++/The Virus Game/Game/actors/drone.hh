#ifndef DRONE_HH
#define DRONE_HH

#include "windows/gamewindow.hh"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

class Drone : public QGraphicsItem
{
public:

    /**
     * @brief Constructor
     */
    Drone(int x, int y);

    /**
     * @brief Deconstructor
     */
    ~Drone();

    /**
     * @brief Creates the right size bounding rect
     * @return Bounding rect
     */
    QRectF boundingRect() const;

    /**
     * @brief Sets drone to the right coordinates
     * @pre  x > 0 && x < 1095, y > 0 && y < 592
     * @post Exception guarantee: basic.
     */
    void setCoord(int x, int y);

    /**
     * @brief Sets the picture of the drone
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    /**
     * @brief Drone's gun's coordinates
     * @pre  x > 0 && x < 1095, y > 0 && y < 592
     * @returns Pair with x and y coordinates, the gun's coordinates in the map
     * @post pair.first > 0 && pair.first < 1095, pair.second > 0 && pair.second < 592
     */
    std::pair<int, int> gunCoords();

    /**
     * @brief Move the drone
     * @pre  where > 0 && where <= 3
     * @post Drone moves or stays in the same place, exception guarantee: strong
     */
    void move(int where);

private:

    int x_;
    int y_;
    int height_;
    int width_;

    // Gun's coordinates, the red part
    std::pair<int, int> gun_;
    QImage image = QImage(":/Pics/Pics/drone.png");

    int windowWidth_ = 1095;
    int windowHeight_ = 592;

};

#endif // DRONE_HH
