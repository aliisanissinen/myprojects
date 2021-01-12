#include "tampere.h"


Tampere::Tampere(GameWindow &w) : w_(&w)
{

}

Tampere::~Tampere()
{
    delete  w_;
}

void Tampere::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    bigPicture_ = bigbackground;
    smallPicture_ = basicbackground;
    w_->setPicture(bigPicture_);
}

void Tampere::setClock(QTime clock)
{
    time_ = clock;
}

void Tampere::addStop(std::shared_ptr<IStop> new_stop)
{
    stops_.push_back(new_stop);
    // Coordinates to the big background, coordinates must be proportional
    int xCor = new_stop->getLocation().giveX() + 350;
    int yCor = 500 - new_stop->getLocation().giveY() + 50;
    w_->addStop(xCor,yCor, stop, new_stop);
}

void Tampere::startGame()
{

}

void Tampere::addActor(std::shared_ptr<IActor> newactor)
{
    // Coordinates to the big background, coordinates must be proportional
    int xCor = newactor->giveLocation().giveX() + 350;
    int yCor = 500 - newactor->giveLocation().giveY() + 50;

    if (dynamic_cast<CourseSide::Nysse*>(newactor.get())) {
        busses_.push_back(newactor);
        w_->addActor(xCor,yCor, bus, newactor);
    }
    // If passengers are too far away, they are removed,
    // otherwise those slow down the program
    else if(0 >= xCor || xCor >= 1100  || 0 >= yCor || yCor >= 600) {
        actorRemoved(newactor);
    }
    else if (dynamic_cast<CourseSide::Passenger*>(newactor.get())){
        passengers_.push_back(newactor);
        w_->addActor(xCor,yCor, passenger, newactor);
    }
    else {
        qDebug() << "addActor ei ole bussi tai matkustaja?";
    }
}


void Tampere::removeActor(std::shared_ptr<IActor> actor)
{
    if (findActor(actor)) {
        w_->removeActor();
    }
    else{
        qDebug() << "removeActor: Actor ei löytynyt. precond löytyy";
    }
}

void Tampere::actorRemoved(std::shared_ptr<IActor> actor)
{
    actor->remove();
}

bool Tampere::findActor(std::shared_ptr<IActor> actor) const
{
     return w_->findVisualActor(actor);
}

void Tampere::actorMoved(std::shared_ptr<IActor> actor)
{
    // Coordinates to the big background, coordinates must be proportional
    int xCor = actor->giveLocation().giveX() + 350;
    int yCor = 500 - actor->giveLocation().giveY() + 50;
    findActor(actor);
    w_->updateCoords(xCor, yCor);
}

std::vector<std::shared_ptr<IActor> > Tampere::getNearbyActors(Location loc) const
{
    std::vector<std::shared_ptr<IActor> > nearbyActors;

    for (std::shared_ptr<IActor> a: busses_) {
        if(a->giveLocation().isClose(loc, 10)) {
            nearbyActors.push_back(a);
        }
    }

    for (std::shared_ptr<IActor> a: passengers_) {
        if(a->giveLocation().isClose(loc, 10)) {
            nearbyActors.push_back(a);
        }
    }

    return nearbyActors;
}

std::vector<std::shared_ptr<IStop> > Tampere::getNearbyStops(Location loc) const
{
    std::vector<std::shared_ptr<IStop> > nearbyStops;
    for (std::shared_ptr<IStop> s: stops_) {
        if(s->getLocation().isClose(loc)) {
            nearbyStops.push_back(s);
        }
    }

    return nearbyStops;
}

bool Tampere::isGameOver() const
{
    return gameOver;
}

void Tampere::endGame(bool end)
{
    gameOver = end;
}
