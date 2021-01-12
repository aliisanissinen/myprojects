#ifndef STOPITEM_H
#define STOPITEM_H

#include "actoritem.h"


class StopItem : public ActorItem
{
public:
    /**
    * @brief Constructor
    */
    StopItem(int x, int y, int type, std::shared_ptr<QImage> image_ptr,
             std::shared_ptr<Interface::IStop> actor);

    /**
     * @brief Deconstructor
     */
    ~StopItem();

    /**
     * @brief Returns the pointer to IStop class, there is information about stop
     * @return The pointer
     * @post Exception guarantee: nothrow.
     */
    std::shared_ptr<Interface::IStop> give_stop_ptr();

private:

    std::shared_ptr<Interface::IStop> stop_ptr_;
    QImage image;

};

#endif // STOPITEM_H
