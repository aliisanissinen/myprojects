// Game15 (or puzzle 15)

// Program author
// Name: Aliisa Nissinen
// Student number: 291603
// UserID: kralni
// E-Mail: aliisa.nissinen@tuni.fi
//
// Builds a two-dimensional grid for puzzle 15, that contains numbers 1-15 
// and a dot (represents a blank box, number 16 in a vector).
// Also checks if the game is won.

#ifndef BOARD_HH
#define BOARD_HH
#include <vector>

const int SIZE = 4;

using namespace std;


class Board
{
public:

    Board(std::vector< std::vector<unsigned int>> grid);

    // Prints the game grid
    void print();

    // Changes grid with a new vector, empty place and one number change
    // places
    void changeGrid(std::vector< std::vector<unsigned int>> twoDvector);

    // Checks if the player has won, numbers 1-16 must be in the right order and empty space
    // must be the last
    bool winningGrid();

private:

    // Game grid for the 15 puzzle, 2D vector that includes integers
    std::vector< std::vector<unsigned int>> grid_;

};

#endif // BOARD_HH
