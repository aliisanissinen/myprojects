#include "actoritem.h"



ActorItem::ActorItem(int x, int y, int type, std::shared_ptr<QImage> image_ptr):
    x_(x), y_(y), type_(type), image(*image_ptr)
{
    setPos(mapToParent(x_, y_ ));
    if (type == bus) {
            height_ = 20;
            width_ = 15;
            zVal_ = 2;
    }
    else if (type == stop) {
        height_ = 40;
        width_ = 20;
    }
    else if (type == passenger) {
        height_ = 20;
        width_ = 10;
        zVal_ = 1;
    }

}

ActorItem::~ActorItem()
{

}

void ActorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    QRectF bounds = boundingRect();
    painter->drawImage(bounds, image);

    // unused
    (void)option;
    (void)widget;
}

QRectF ActorItem::boundingRect() const
{
    return QRectF(0, 0, width_, height_);
}

void ActorItem::setCoord(int x, int y)
{
    setX( x );
    setY( y );
}

bool ActorItem::isInfected()
{
    return infected_;
}

void ActorItem::infectionStatus(int level, bool inf)
{
    // If the level is 1, then viruses are size large.
    int factor = 1;
    if (level == 1) {
        factor = 2;
    }

    if (inf) {
        oldImage = image;
        image = QImage(":/Pics/Pics/virus2.png");
        width_= width_ * 2 * factor;
        height_ = height_ * 2 * factor;
        setZValue(3);
        infected_ = true;
    }
    else {
        qDebug() << "Infektio poistetaan";
        image = oldImage;

        width_= width_ / (2*factor);
        height_ = height_ / (2*factor);
        setZValue(zVal_);
        infected_ = false;
    }

}


