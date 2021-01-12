#ifndef TAMPERE_H
#define TAMPERE_H

#include "interfaces/icity.hh"
#include "interfaces/iactor.hh"
#include "interfaces/istop.hh"
#include "windows/gamewindow.hh"
#include "actors/nysse.hh"

#include <QTime>
#include <QDebug>

class GameWindow;

using namespace Interface;

class Tampere : public ICity
{
public:
    /**
    * @brief Constructor
    */
    Tampere(GameWindow &w);

    /**
    * @brief Deconstructor
    */
    ~Tampere();

    /**
    * @brief Sets background to the city, map
    * @pre -
    * @post Exception guarantee: basic.
    */
    void setBackground(QImage& basicbackground, QImage& bigbackground) override;

    /**
    * @brief Sets clock
    * @pre -
    * @post Exception guarantee: basic.
    */
    void setClock(QTime clock) override;

    /**
    * @brief Adds stops to the city
    * @pre stop is not nullptr
    * @post Exception guarantee: basic.
    */
    void addStop(std::shared_ptr<IStop> stop) override;

    /**
    * @brief Starts the game
    */
    void startGame() override;

    /**
    * @brief Adds actors to the city, passengers and busses
    * @pre newactor is not nullptr
    * @post Exception guarantee: basic.
    */
    void addActor(std::shared_ptr<IActor> newactor) override;

    /**
    * @brief Removes actors from the city
    * @pre actor is not nullptr
    * @post Exception guarantee: basic.
    */
    void removeActor(std::shared_ptr<IActor> actor) override;

    /**
    * @brief Actor need to be removed
    * @pre actor is not nullptr
    * @post Exception guarantee: basic.
    */
    void actorRemoved(std::shared_ptr<IActor> actor) override;

    /**
    * @brief Finds the actor from the city
    * @pre actor is not nullptr
    * @post Exception guarantee: basic.
    */
    bool findActor(std::shared_ptr<IActor> actor) const override;

    /**
    * @brief Moves the actor in the city
    * @pre actor is not nullptr
    * @post Exception guarantee: basic.
    */
    void actorMoved(std::shared_ptr<IActor> actor) override;

    /**
    * @brief Gets actors that are nearby
    * @pre location is made (class)
    * @post Exception guarantee: basic.
    */
    std::vector<std::shared_ptr<IActor>> getNearbyActors
    (Location loc) const override;

    /**
    * @brief Gets stops that are nearby
    * @pre location is made (class)
    * @post Exception guarantee: basic.
    */
    std::vector<std::shared_ptr<IStop> > getNearbyStops(Location loc) const;

    /**
    * @brief Tells if the game is over
    * @return True if the game is over, else false
    * @post Exception guarantee: nothrow.
    */
    bool isGameOver() const override;

    /**
    * @brief Ends the game, change the bool
    * @pre -
    * @post Exception guarantee: basic.
    */
    void endGame(bool end = false);

private:
    QImage bigPicture_;
    QImage smallPicture_;

    GameWindow *w_;
    QTime time_;
    bool gameOver = false;

    std::vector< std::shared_ptr<Interface::IStop> > stops_;
    std::vector< std::shared_ptr<Interface::IActor> > busses_;
    std::vector< std::shared_ptr<Interface::IActor> > passengers_;
};

#endif // TAMPERE_H
