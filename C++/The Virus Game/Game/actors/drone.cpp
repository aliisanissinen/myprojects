#include "drone.hh"

#include <QDebug>

Drone::Drone(int x, int y) : x_(x), y_(y)
{
    height_ = 45;
    width_ = 145;
    // The gun's x and y coordinates
    gun_.first = width_/2;
    gun_.second = height_ - 10;
    setCoord(x_, y_);
}

Drone::~Drone()
{

}

QRectF Drone::boundingRect() const
{
    return QRectF(0, 0, width_, height_);
}

void Drone::setCoord(int x, int y)
{
    if (x + width_/2 >= windowWidth_) {
        x = windowWidth_ - width_/2;
    }
    if (x <= 0 - width_/2) {
        x = 0 - width_/2;
    }
    if (y + height_ >= windowHeight_) {
        y = windowHeight_ - height_;
    }
    if (y <= 0 - height_ + 1) {
        y = 0 - height_ + 1;
    }
    x_ = x;
    y_ = y;
    setX( x );
    setY( y );
}

void Drone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
    QRectF bounds = boundingRect();
    painter->drawImage(bounds, image);

    // unused
    (void)option;
    (void)widget;
}

std::pair<int, int> Drone::gunCoords()
{
    std::pair<int, int> gunCoords;
    gunCoords.first = gun_.first + x_;
    gunCoords.second = gun_.second + y_;
    return gunCoords;
}

void Drone::move(int where)
{
    enum direction { up, left, down, right};

    if (where == up) {
        y_ = y_ - 4;
    }
    else if (where == left) {
        x_ = x_ - 4;
    }
    else if (where == down) {
        y_ = y_ + 4;
    }
    else if (where == right) {
        x_ = x_ + 4;
    }

    setCoord(x_, y_);
}


                
