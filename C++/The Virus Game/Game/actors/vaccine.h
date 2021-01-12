#ifndef VACCINE_H
#define VACCINE_H

#include "actoritem.h"
#include "core/location.hh"


class Vaccine : public ActorItem
{
public:
    /**
     * @brief Constructor
     */
    Vaccine(int x, int y, int type, std::shared_ptr<QImage> image_ptr);

    /**
     * @brief Deconstructor
     */
    ~Vaccine();

    /**
     * @brief Returns the location of vaccine
     * @return Location
     * @post Exception guarantee: nothrow.
     */
     Interface::Location giveLoc();


private:

    Interface::Location vaccineLoc_;
};

#endif // VACCINE_H
