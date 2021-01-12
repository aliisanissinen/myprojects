#include "passengeritem.h"

PassengerItem::PassengerItem(int x, int y, int type, std::shared_ptr<QImage> image_ptr,
                             std::shared_ptr<Interface::IActor> actor) :
    ActorItem(x, y, type, image_ptr)
{
    actor_ptr_ = actor;
}

PassengerItem::~PassengerItem()
{

}

std::shared_ptr<Interface::IActor> PassengerItem::give_actor_ptr()
{
    return actor_ptr_;
}
