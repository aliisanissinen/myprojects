#ifndef BUSITEM_H
#define BUSITEM_H

#include "actoritem.h"


class BusItem : public ActorItem
{
public:
    /**
     * @brief Constructor
     */
    BusItem(int x, int y, int type, std::shared_ptr<QImage> image_ptr,
            std::shared_ptr<Interface::IActor> actor);

    /**
     * @brief Deconstructor
     */
     ~BusItem();

    /**
     * @brief Returns the pointer to IActor class, there is information about bus
     * @return The pointer
     * @post Exception guarantee: nothrow.
     */
    std::shared_ptr<Interface::IActor> give_actor_ptr();


private:

    std::shared_ptr<Interface::IActor> actor_ptr_;
    QImage image;


};

#endif // BUSITEM_H
