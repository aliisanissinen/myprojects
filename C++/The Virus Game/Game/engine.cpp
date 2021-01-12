#include "engine.hh"


Engine::Engine(QObject *parent) : QObject(parent), w_(new GameWindow),
    d_(new Dialog), l_(new CourseSide::Logic)
{

}

Engine::~Engine()
{
    delete w_;
    delete d_;
    delete l_;
}

void Engine::start()
{
    QImage pieni_kartta(":/offlinedata/offlinedata/kartta_pieni_500x500.png");
    QImage iso_kartta(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    t_ = std::make_shared<Tampere> (*w_);
    t_->setBackground(pieni_kartta, iso_kartta);

    d_->show();

    connect(d_, &Dialog::okClicked, this, &Engine::openGameWindow);
}

void Engine::openGameWindow()
{
    w_->getInfo(d_->giveInfo());
    w_->getCity(t_);
    w_->show();
    connect(w_, &GameWindow::gameStarted, this, &Engine::buildGame);
}

void Engine::buildGame()
{
    l_->fileConfig();
    l_->takeCity(t_);
    l_->finalizeGameStart();
}
