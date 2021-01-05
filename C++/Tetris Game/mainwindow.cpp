/* TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Tetris game
 * ----------
 *
 * Last edited (11.5.2020)
 * Name: Aliisa Nissinen
 *
 * */

#include "mainwindow.hh"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer_(new QTimer(this)),
    timer_seconds_(new QTimer(this)),
    seconds_(0),
    score_(0),
    level_(500),
    key_press_active_(false)
{
    ui->setupUi(this);

    // Graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);

    // The graphicsViewTetris object is placed on the window
    // at the following coordinates
    int left_margin = 40; // x coordinate
    int top_margin = 50; // y coordinate

    // The width of the graphicsViewTetris is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsViewTetris->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsViewTetris->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Setting random engine ready for the first real call.
    int seed = time(0);
    random_eng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(random_eng); // Wiping out the first random number (which is almost always 0)

    // Connecting timer to right functions
    connect(timer_seconds_, SIGNAL(timeout()), this, SLOT(seconds_go()));
    connect(timer_, SIGNAL(timeout()), this, SLOT(move_down()));

    // At the beginning of the game, only the start button  and quit button are available
    ui->pauseButton->setDisabled(true);
    ui->continueButton->setDisabled(true);
    ui->leftButton->setDisabled(true);
    ui->rightButton->setDisabled(true);
}


// Deconstructor
MainWindow::~MainWindow()
{
    delete ui;
}


// The tetromino can be moved with buttons or with a computer keyboard.
void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (key_press_active_) {
        // Right
        if (event->key() == Qt::Key_D) {
            move_horizontal(1);
        }
        // Left
        if (event->key() == Qt::Key_A) {
            move_horizontal(-1);
        }
        // Down
        if (event->key() == Qt::Key_S) {
            move_down();
        }
    }
}


// Checks if the game ground is full. If it's full then the game stops.
void MainWindow::game_end_check()
{
    bool end = false;

    for (QGraphicsItem* set : set_rectvector_) {
        if (set->y() <= 0) {
            end = true;
        }
    }

    // When the game ends, only the quit button is available
    if (end) {
        ui->pauseButton->setDisabled(true);
        ui->leftButton->setDisabled(true);
        ui->rightButton->setDisabled(true);
        timer_seconds_->stop();
        ui->endLabel->setText("GAME OVER");
        ui->endScoreLabel->setText("SCORE: " + QString::number(score_));
    }
    else {
        rectvector_.clear();
        key_press_active_ = true;
        new_shape();
    }
}


// Adds score and checks if the score is enough to the next
// level (score must be 30). At the next level, timer is 0.05 seconds faster
void MainWindow::add_score()
{
    score_ += 15;
    ui->scoreLcd->display(score_);

    if (score_ >= 30) {
        level_ = level_ - 50;
    }
}


// After removing a full line (full_line function), other lines
// that are before the removed line must be dropped one line down.
// Given parameter: the y coordinate of the removed line
void MainWindow::line_down(int y)
{
    for (QGraphicsItem* set : set_rectvector_) {
        if (set->y() < (y*SQUARE_SIDE)) {
            set->moveBy(0, SQUARE_SIDE);
        }
    }
}


// Checks if the row is full of rectangles (15 rectangles). If it's
// full then the row is removed.
void MainWindow::full_line()
{
    QTransform deviceTransform;
    // Calculates the rectangles at the row, the full line is 15
    // rectangles (COLUMNS)
    int rectangles = 0;

    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLUMNS+1; ++x) {
            QGraphicsItem* item = scene_->itemAt(QPointF(x*SQUARE_SIDE+1,
                                            y*SQUARE_SIDE+1), deviceTransform);
            if (item != nullptr) {
                ++rectangles;
            }
        }
        if (rectangles == COLUMNS) {
            // Remove the rectangles from the field and from the vector that
            // includes the set rectangles
            for (int x = 0; x < COLUMNS; ++x) {
                for (QGraphicsItem* set : set_rectvector_) {
                    if (set->x() == x*SQUARE_SIDE and
                            set->y() == y*SQUARE_SIDE) {
                        int index = set_rectvector_.indexOf(set);
                        set_rectvector_.remove(index);
                        delete set;
                    }
                }
            }
            // The full line gets player a 15 points
            add_score();
            line_down(y);
        }
        rectangles = 0;
    }
}


// Moves tetromino horizontal if possible, work with right and left
// buttons or with keyboards A and D
// Given parameter: 1 if moving right and -1 if moving left
void MainWindow::move_horizontal(int left_or_right)
{
    QRectF board = scene_->sceneRect();
    QTransform deviceTransform;
    // The length of one step
    qreal deltaX = static_cast<qreal>(SQUARE_SIDE * left_or_right);
    // Is it possible to move to that direction, true if not and false if yes
    bool excess = false;

    for (QGraphicsRectItem* rect : rectvector_) {
        qreal current_x = rect->x();
        qreal current_y = rect->y();
        current_x += deltaX;

        // Tetrominoes cannot go over the game platform
        if (!board.contains(current_x, current_y)) {
            excess=true;
            break;
        }
        // Tetrominoes cannot overlap
        QGraphicsItem* item = scene_->itemAt(QPointF(current_x+1, current_y+1),
                                             deviceTransform);
        if (item != nullptr) {
            for (QGraphicsItem* set : set_rectvector_) {
                if (set->x() == item->x() and set->y() == item->y()) {
                    excess=true;
                    break;
                }
            }
        }
    }

    if (!excess) {
        for (QGraphicsRectItem* rect : rectvector_) {
            rect->moveBy(deltaX, 0);
        }
    }
}


// Moves the tetromino down one step. Works with timer. It is on always when
// the game continues. Stops, when the player clicked the pause button or
// the game ends.
void MainWindow::move_down()
{    
    QRectF board = scene_->sceneRect();
    QTransform deviceTransform;
    // The length of one step
    qreal deltaY = static_cast<qreal>(SQUARE_SIDE);
    // Is it possible to move down, true if not and false if yes
    bool excess = false;

    for (QGraphicsRectItem* rect : rectvector_) {
        qreal current_x = rect->x();
        qreal current_y = rect->y();
        current_y += deltaY;

        // Tetrominoes cannot go over the game platform
        if (!board.contains(current_x, current_y)) {
            excess=true;
            break;
        }
        // Tetrominoes cannot overlap
        QGraphicsItem* item = scene_->itemAt(QPointF(current_x+1, current_y+1),
                                             deviceTransform);
        if (item != nullptr) {
            for (QGraphicsItem* set : set_rectvector_) {
                if (set->x() == item->x() and set->y() == item->y()) {
                    excess=true;
                    break;
                }
            }
        }
    }

    if (!excess) {
        for (QGraphicsRectItem* rect : rectvector_) {
            rect->moveBy(0, deltaY);
        }
    }
    else {
        timer_->stop();
        // Stopped tetrominoes insert to vector, that includes set rectangles
        for (QGraphicsRectItem* rect : rectvector_) {
            set_rectvector_.append(rect);
        }
        key_press_active_ = false;
        full_line();
        game_end_check();
    }
}


// The function creates random tetromino. Tetromino contains four
// rectangles that will be placed in the vector. Each tetoamino
// has own colour.
void MainWindow::new_shape()
{
    // random generator, a number between 1-7
    int shape = distr(random_eng);
    static constexpr int coordsTable[7][4][2] = {
            { { 6, -1 }, { 7, -1 }, { 8, -1 }, { 9, -1 } },   // HORIZONTAL
            { { 7, -1 }, { 7, 0 }, { 8, 0 }, { 9, 0 } },      // LEFT_CORNER
            { { 7, 0 }, { 8, 0 }, { 9, 0 }, { 9, -1 } },      // RIGHT_CORNER
            { { 7, 0 }, { 8, 0 }, { 7, -1 }, { 8, -1 } },     // SQUARE
            { { 7, 0 }, { 8, 0 }, { 8, -1 }, { 9, -1 } },     // STEP_UP_RIGHT
            { { 7, 0 }, { 8, 0 }, { 9, 0 }, { 8, -1 } },      // PYRAMID
            { { 8, 0 }, { 9, 0 }, { 7, -1 }, { 8, -1 } } };   // STEP_UP_LEFT

    static constexpr QRgb colorTable[8] = { 0x00ced1,       // HORIZONTAL
                                            0x1e90ff,       // LEFT_CORNER
                                            0xff6347,       // RIGHT_CORNER
                                            0xffd700,       // SQUARE
                                            0x7cfc00,       // STEP_UP_RIGHT
                                            0xba55d3,       // PYRAMID
                                            0xdc143c };     // STEP_UP_LEFT

    QBrush brush(colorTable[int(shape)]);
    QPen pen(Qt::black);
    pen.setWidth(1);

    int coords[4][2];
    for (int i = 0; i < 4 ; i++) {
        for (int j = 0; j < 2; ++j) {
            coords[i][j] = coordsTable[shape][i][j];
        }
    }

    // After adding rectangle to the vector, each rectangle is moved to the center of
    // the game ground.
    for (int i = 0; i < 4; ++i) {
        rectvector_.append(scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, pen, brush));
        rectvector_.last()->moveBy(coords[i][0]*SQUARE_SIDE, coords[i][1]*SQUARE_SIDE);
    }

    timer_->start(level_);
}


// Calculates the game seconds, how long player has
// played the same game.
void MainWindow::seconds_go()
{
    ++seconds_;
    ui->timeLcd->display(seconds_);
}


// Start button starts the game. It can be clicked once.
// The game can be paused with the pause button after.
void MainWindow::on_startButton_clicked()
{
    timer_seconds_->start(1000);
    // All buttons are available, except the start button and
    // the continue button
    ui->startButton->setDisabled(true);
    ui->pauseButton->setDisabled(false);
    ui->leftButton->setDisabled(false);
    ui->rightButton->setDisabled(false);
    key_press_active_ = true;

    new_shape();
}


// Pause button can be clicked after the start button.
// Stops the game, but the game can be continued later with
// continue button.
void MainWindow::on_pauseButton_clicked()
{
    timer_->stop();
    timer_seconds_->stop();
    // None of the buttons are available, except the continue button and
    // quit button
    ui->continueButton->setDisabled(false);
    ui->pauseButton->setDisabled(true);
    ui->leftButton->setDisabled(true);
    ui->rightButton->setDisabled(true);
    key_press_active_ = false;
}


// Continue button can be clicked after the pause button.
// Continues the previous game.
void MainWindow::on_continueButton_clicked()
{
    timer_->start(level_);
    timer_seconds_->start(1000);
    // All buttons are available, except the start button and
    // the continue button
    ui->continueButton->setDisabled(true);
    ui->pauseButton->setDisabled(false);
    ui->leftButton->setDisabled(false);
    ui->rightButton->setDisabled(false);
    key_press_active_ = true;
}


// Moves tetromino to the right horizontal, with move_horizontal function
void MainWindow::on_rightButton_clicked()
{
    move_horizontal(1);
}


// Moves tetromino to the left horizontal, with move_horizontal function
void MainWindow::on_leftButton_clicked()
{
    move_horizontal(-1);
}
