/* TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Tetris game
 * ----------
 *
 * Last edited (11.5.2020)
 * Name: Aliisa Nissinen
 *
 * */


#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH


#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>
#include <QVector>
#include <QString>
#include <random>


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    /**
     * @brief game_end_check
     * Checks if the game platform is full, if it is
     * the the game ends, otherwise game continues.
     */
    void game_end_check();

    /**
     * @brief add_score
     * Adds score and checks if the score is enough to the next level
     * (score must be 30), at the next level timer is 0.05 seconds faster
     */
    void add_score();

    /**
     * @brief line_down
     * @param y coordinate of the deleted full line
     * Moves tetromino rows one step down, if full line is deleted
     * under them.
     */
    void line_down(int y);

    /**
     * @brief full_line
     * Checks if there a full line of tetrominoes in the game platform.
     */
    void full_line();

    /**
     * @brief move_horizontal
     * Moves tetrominoes horizontal in the game platform
     * @param the direction of the movement, nagative if left and
     * positive if right
     */
    void move_horizontal(int left_or_right);

    /**
     * @brief move_down
     * Moves tetrominoes down in the game platform, work with timer
     */
    void move_down();

    /**
     * @brief new_shape
     * Makes new tetromino shape randomly
     */
    void new_shape();

    /**
     * @brief seconds_go
     * Calculates the game time, work with timer
     */
    void seconds_go();

    /**
     * @brief on_startButton_clicked
     * Starts the game, when the player clicks the start button
     */
    void on_startButton_clicked();

    /**
     * @brief on_pauseButton_clicked
     * Pauses the game, when the player clicks the pause button
     */
    void on_pauseButton_clicked();

    /**
     * @brief on_continueButton_clicked
     * Continues the game, when the player clicks the continue button.
     * Works after the pause button are clicked before.
     */
    void on_continueButton_clicked();

    /**
     * @brief on_rightButton_clicked
     * Move horizontal to the right (with move_horizontal function), when
     * the player clicks the right button.
     */
    void on_rightButton_clicked();

    /**
     * @brief on_leftButton_clicked
     * Move horizontal to the left (with move_horizontal function), when
     * the player clicks the left button.
     */
    void on_leftButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene_;

    // Vector includes all tetrominoes, that move at the moment
    QVector <QGraphicsRectItem*> rectvector_;
    // Vector includes all tetrominoes, that are set in the game platform
    QVector <QGraphicsItem*> set_rectvector_;

    // Constants describing scene coordinates
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480; // 260; (in moving circle)
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240; // 680; (in moving circle)

    // Number of tetrominoes
    const int NUMBER_OF_TETROMINOS = 7;
    // Size of a tetromino component
    const int SQUARE_SIDE = 16;

    // Number of horizontal cells (places for tetromino components)
    const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
    // Number of vertical cells (places for tetromino components)
    const int ROWS = BORDER_DOWN / SQUARE_SIDE;

    // For randomly selecting the next dropping tetromino
    std::default_random_engine random_eng;
    std::uniform_int_distribution<int> distr;

    // Timer for moving tetrominoes down
    QTimer* timer_;
    // Timer for calculating the game time
    QTimer* timer_seconds_;

    // Game time in seconds, score and level in the current game
    // Level number is smaller the further go (change timer time)
    int seconds_;
    int score_;
    int level_;

    // If the key press is possible
    bool key_press_active_;
};

#endif // MAINWINDOW_HH
