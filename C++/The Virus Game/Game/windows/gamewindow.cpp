#include "gamewindow.hh"
#include "ui_gamewindow.h"


const int PADDING = 10;

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::GameWindow), s_(new Statistics)
{
    ui->setupUi(this);
    ui->gameView->setFixedSize(width_ +1, height_ + 25);
    ui->centralwidget->setFixedSize(width_ + PADDING + 235,
                                    height_ + PADDING + 140);
    ui->gameviewWidget->setFixedSize(width_ + 1, height_);
    ui->buttonWidget->move(1120, 20);

    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0,width_,height_);
    resize(minimumSizeHint());

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, map, &QGraphicsScene::advance);
    gameTime_ = new QTimer(0);   
    connect(gameTime_, &QTimer::timeout, this, &GameWindow::showTime);
    connect(gameTime_, &QTimer::timeout, this, &GameWindow::randomVaccine);
    randomTime_ = new QTimer(0);
    connect(randomTime_, &QTimer::timeout, this, &GameWindow::randomVirus);
    timer->start(tick_);

    ui->startButton->setEnabled(true);
    ui->pauseButton->setEnabled(false);
    ui->stopButton->setEnabled(true);

    addDrone();
    drone_->setEnabled(false);
}

GameWindow::~GameWindow()
{
    delete ui;
    delete s_;
    delete drone_;

    for (auto actor : actors_) {
        delete actor;
    }
}

void GameWindow::setSize(int w, int h)
{
    width_ = w;
    height_ = h;
}

void GameWindow::setTick(int t)
{
    tick_ = t;
}

void GameWindow::getInfo(std::pair<QString, int> info)
{
    s_->getName(info.first);
    s_->getLevel(info.second);

    ui->nameLabel->setText(info.first);
    level_ = info.second;

    if (level_ == 1) {
        levelTime_ = 15;
    }
    else if (level_ == 2) {
        levelTime_ = 30;
    }
    else if (level_== 3) {
        levelTime_ = 60;
    }

    top5();
}

void GameWindow::showTime()
{
    ++gameSeconds_;
    ui->lcdNumber->display(gameSeconds_);

    if (gameSeconds_ == levelTime_) {
        gameEnd();
    }
}

void GameWindow::top5()
{
    s_->readData();  
    std::map<int, std::string> data = s_->giveData();

    std::vector<QLabel*> names = {ui->top1Label, ui->top2Label, ui->top3Label,
                                  ui->top4Label, ui->top5Label};
    std::vector<QLabel*> points = {ui->top1pointsLabel, ui->top2pointsLabel,
                                   ui->top3pointsLabel, ui->top4pointsLabel,
                                   ui->top5pointsLabel};

    std::set<std::pair<int, std::string>,
            std::greater<std::pair<int, std::string>>> GreaterOrderedSet;

    for (std::pair<int, std::string> bestToWorse : data) {
        GreaterOrderedSet.insert(bestToWorse);
    }

    int i = 0;
    for (auto pair : GreaterOrderedSet) {
        names.at(i)->setText(QString::fromStdString(pair.second));
        points.at(i)->setText(QString::number(pair.first));
        i++;
        if (i == 5){
            break;
        }
    }
}

void GameWindow::addActor(int locX, int locY, int type,
                          std::shared_ptr<Interface::IActor> actor)
{
    std::shared_ptr<QImage> image_ptr;

    if (type == bus) {
        image_ptr = std::make_shared<QImage>(busImage);
        BusItem* nActor = new BusItem(locX, locY, type, image_ptr, actor);
        map->addItem(nActor);
        nActor->setZValue(2);
        busses_.push_back(nActor);
        last_ = nActor;
    }
    else if (type == passenger) {
        image_ptr = std::make_shared<QImage>(passengerImage);
        PassengerItem* nActor =
                new PassengerItem(locX, locY, type, image_ptr, actor);
        map->addItem(nActor);
        nActor->setZValue(1);
        passengers_.push_back(nActor);
        last_ = nActor;
    }
    else if (type == vaccine) {
        image_ptr = std::make_shared<QImage>(vaccineImage);
        Vaccine* nActor = new Vaccine(locX, locY, type, image_ptr);
        map->addItem(nActor);
        nActor->setZValue(4);
        vaccine_ = nActor;
    }
}

void GameWindow::addStop(int locX, int locY, int type,
                         std::shared_ptr<Interface::IStop> new_stop)
{
    std::shared_ptr<QImage> image_ptr;

    image_ptr = std::make_shared<QImage>(stopImage);
    StopItem* nActor = new StopItem(locX, locY, type, image_ptr, new_stop);
    map->addItem(nActor);
    nActor->setZValue(0);
    stops_.push_back(nActor);
}

void GameWindow::addDrone()
{
    // Coordinates to the big background, coordinates must be proportional
    // Drone starts the game from the center of the map
    drone_ = new Drone(480, 260);
    map->addItem(drone_);
    drone_->setZValue(5);
}

void GameWindow::updateCoords(int nX, int nY)
{
    last_->setCoord(nX, nY);
}

void GameWindow::getCity(std::shared_ptr<Tampere> t_)
{
    city_ = t_;
}

void GameWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
}

bool GameWindow::findVisualActor(std::shared_ptr<Interface::IActor> actor)
{
    for (PassengerItem* visualActor : passengers_){
        std::shared_ptr<Interface::IActor> ptr =
                visualActor->give_actor_ptr();
        if (ptr == actor){
            last_ = visualActor;
            return true;
        }

    }
    for (BusItem* visualActor : busses_){
        std::shared_ptr<Interface::IActor> ptr =
                visualActor->give_actor_ptr();
        if (ptr == actor){
            last_ = visualActor;
            return true;
        }
    }
    return false;
}

void GameWindow::removeActor()
{
    for (int i = 0; i < actors_.size(); i++) {
        if(actors_.at(i) == last_){
            actors_.remove(i);
            delete last_;
            last_ = nullptr;
            break;
        }
    }
}

void GameWindow::randomVirus()
{
    int randActor = rand()%(0-2);

    if (randActor == 0) {
        int randIndx = rand()%(0-busses_.size() + 1);
        BusItem* random = busses_.at(randIndx);

        if (!random->isInfected()) {
            random->infectionStatus(level_, true);
            viruses_.push_back(random);
        }
    }

    else if (randActor == 1) {
        int randIndx = rand()%(0-passengers_.size() + 1);
        PassengerItem* random = passengers_.at(randIndx);
        if (!random->isInfected()) {
            random->infectionStatus(level_, true);
            viruses_.push_back(random);
        }
    }
}

void GameWindow::randomVaccine()
{
    if (vaccine_ == nullptr) {
        int randTime = rand()% ((levelTime_ - gameSeconds_)+1) + gameSeconds_;
        if (gameSeconds_ == randTime) {
            qDebug() << "Rokote luotu";
            int randX = rand()%(10-1000);
            int randY = rand()%(10-500);
            addActor(randX ,randY, vaccine, nullptr);
        }
    }
}

void GameWindow::shoot()
{
    std::pair<int, int> coords = drone_->gunCoords();
    Interface::Location shootLoc(coords.first, coords.second);
    shootLoc.setXY(coords.first, coords.second);

    int limit = 20;
    // If the level 1, viruses are bigger and it's easier to shoot them
    if (level_ == 1) {
        limit += 50;
    }

    // Vaccine removes all the viruses
    if (vaccine_ != nullptr) {
        if ( shootLoc.isClose(vaccine_->giveLoc(), limit)) {
            for (ActorItem* act : viruses_) {
                act->infectionStatus(level_);
                s_->addPoints(1);
            }
            delete vaccine_;
            vaccine_ = nullptr;
            viruses_.clear();
        }
    }

    for (ActorItem* act : viruses_) {
        QPointF virusCoord = act->scenePos();
        int x = virusCoord.x();
        int y = virusCoord.y();
        Interface::Location virusLoc(x, y);
        virusLoc.setXY(x, y);

        if ( virusLoc.isClose(shootLoc, limit)) {
            act->infectionStatus(level_);
            s_->addPoints(5);
            viruses_.erase(std::remove(viruses_.begin(), viruses_.end(), act),
                                        viruses_.end());
        }
    }
    ui->pointsLCD->display(s_->givePoints());
}

void GameWindow::gameEnd()
{
    city_->endGame(true);

    gameTime_->stop();
    randomTime_->stop();
    keyPressActive = false;

    ui->startButton->setEnabled(false);
    ui->pauseButton->setEnabled(false);

    ui->nameLabel->setText("GAME OVER\nPOINTS: " + QString::number(s_->givePoints()));

    s_->writeData();
}

void GameWindow::on_startButton_clicked()
{
    qDebug() << "Start clicked";
    emit gameStarted();

    city_->endGame(false);

    ui->startButton->setEnabled(false);
    ui->pauseButton->setEnabled(true);

    gameTime_->start(1000);
    randomTime_->start(750);
    keyPressActive = true;

    ui->pointsLCD->display(s_->givePoints());
}

void GameWindow::on_pauseButton_clicked()
{
    qDebug() << "Pause clicked";

    ui->startButton->setEnabled(true);
    ui->pauseButton->setEnabled(false);

    city_->endGame(true);

    gameTime_->stop();
    randomTime_->stop();
    keyPressActive = false;
}


void GameWindow::on_stopButton_clicked()
{
    qDebug() << "Stop clicked";
    this->close();
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if (keyPressActive) {
        // Right
        if (event->key() == Qt::Key_W) {
            drone_->move(0);
        }
        // Left
        if (event->key() == Qt::Key_A) {
            drone_->move(1);
        }
        // Down
        if (event->key() == Qt::Key_S) {
            drone_->move(2);
        }
        // Up
        if (event->key() == Qt::Key_D) {
            drone_->move(3);
        }
        // Shoot
        if (event->key() == Qt::Key_P) {
            shoot();
        }
    }
}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
    if(keyPressActive){
        if(event->button() == Qt::LeftButton){
            shoot();
        }
    }


}
