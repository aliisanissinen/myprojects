#include "vaccine.h"

Vaccine::Vaccine(int x, int y, int type, std::shared_ptr<QImage> image_ptr) :
    ActorItem(x, y, type, image_ptr)
{
    Interface::Location loc(1 ,1);
    loc.setXY(x ,y);
    vaccineLoc_ = loc;
}

Vaccine::~Vaccine()
{

}

Interface::Location Vaccine::giveLoc()
{
    return vaccineLoc_;
}
