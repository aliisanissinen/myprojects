#ifndef ACTORITEM_H
#define ACTORITEM_H

#include "actors/nysse.hh"
#include "actors/passenger.hh"
#include "actors/stop.hh"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>

enum actors {bus, passenger, stop, vaccine};


class ActorItem : public QGraphicsItem
{
public:
    /**
     * @brief Constructor
     */
    ActorItem(int x, int y, int type, std::shared_ptr<QImage> image_ptr);

    /**
     * @brief Deconstructor
     */
    virtual ~ActorItem();

    /**
     * @brief Creates the right size bounding rect
     * @return Bounding rect
     */
    QRectF boundingRect() const;

    /**
     * @brief Sets acoritem to the right coordinates
     * @pre  x > 0 && x < 1095, y > 0 && y < 592
     * @post Exception guarantee: basic.
     */
    void setCoord(int x, int y);

    /**
     * @brief Infects or heals the actor, depends on the given bool parameter
     * @pre level <=3 && level > 0, inf == true or not given
     * @post Exception guarantee: basic
     */
    void infectionStatus(int level, bool inf=false);

    /**
     * @brief Returns information on whether the actor is infected or not
     * @return True if infected, else false
     * @post Exception guarantee: nothrow.
     */
    bool isInfected();

    /**
     * @brief Sets the picture of the actor
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);


private:

    int x_;
    int y_;
    int type_;
    int height_ = 20;
    int width_ = 20;
    int zVal_;
    bool infected_ = false;

    QImage image;
    QImage oldImage;

};

#endif // ACTORITEM_H
