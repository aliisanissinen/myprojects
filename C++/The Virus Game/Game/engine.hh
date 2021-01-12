#ifndef ENGINE_HH
#define ENGINE_HH

#include "core/logic.hh"
#include "tampere.h"
#include "windows/gamewindow.hh"
#include "windows/dialog.hh"
#include "statistics.hh"

#include <QApplication>
#include <memory>


class Engine : public QObject
{
public:
    /**
    * @brief Constructor
    */
    Engine(QObject *parent = 0);

    /**
    * @brief Deconstructor
    */
    ~Engine();

    /**
    * @brief Starts the game
    */
    void start();

public slots:

    void openGameWindow();
    /**
    * @brief Builds the game with logic class
    */
    void buildGame();

private:
    GameWindow *w_;
    Dialog *d_;
    CourseSide::Logic *l_;
    std::shared_ptr<Tampere> t_;
};

#endif // ENGINE_HH
