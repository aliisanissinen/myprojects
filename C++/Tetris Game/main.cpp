/* TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Tetris game
 * ----------
 *
 * The Tetris game, where the player can move tetrominoes horizontal and down.
 * Tetromino also moves down by themselves. The purpose of the game is to make
 * full rows of rectangles. After that, the full lines disappear and
 * the player gets points (15) and more available space int the game platform.
 * The game ends when the column of tetrominoes grows to the top of
 * the game platform.
 *
 * Last edited (11.5.2020)
 * Name: Aliisa Nissinen
 *
 * */


#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
