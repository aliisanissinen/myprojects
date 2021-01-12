#include "busitem.h"

BusItem::BusItem(int x, int y, int type, std::shared_ptr<QImage> image_ptr,
                 std::shared_ptr<Interface::IActor> actor) :
    ActorItem(x, y, type, image_ptr)
{
    actor_ptr_ = actor;
}

BusItem::~BusItem()
{

}

std::shared_ptr<Interface::IActor> BusItem::give_actor_ptr()
{
    return actor_ptr_;
}
