#include "stopitem.h"

StopItem::StopItem(int x, int y, int type, std::shared_ptr<QImage> image_ptr,
                   std::shared_ptr<Interface::IStop> busStop) :
    ActorItem(x, y, type, image_ptr)
{
    stop_ptr_ = busStop;
}

StopItem::~StopItem()
{

}

std::shared_ptr<Interface::IStop> StopItem::give_stop_ptr()
{
    return stop_ptr_;
}
