#ifndef PASSENGERITEM_H
#define PASSENGERITEM_H

#include "actoritem.h"


class PassengerItem : public ActorItem
{
public:
    /**
     * @brief Constructor
     */
    PassengerItem(int x, int y, int type, std::shared_ptr<QImage> image_ptr,
                  std::shared_ptr<Interface::IActor> actor);

    /**
     * @brief Deconstructor
     */
     ~PassengerItem();

    /**
     * @brief Returns the pointer to IActor class, there is information about passenger
     * @return The pointer
     * @post Exception guarantee: nothrow.
     */
    std::shared_ptr<Interface::IActor> give_actor_ptr();

private:

    std::shared_ptr<Interface::IActor> actor_ptr_;
    QImage image;

};

#endif // PASSENGERITEM_H
