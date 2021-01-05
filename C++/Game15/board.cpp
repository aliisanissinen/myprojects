// Game15 (or puzzle 15)
//
// Program author
//
// Builds a two-dimensional grid for puzzle 15, that contains numbers 1-15 
// and a dot (represents a blank box, number 16 in a vector).
// Also checks if the game is won.


#include "board.hh"
#include <iostream>
#include <iomanip>

const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;
const int NUMBERS = 16;

Board::Board(std::vector< std::vector<unsigned int>> grid):
    grid_(grid) {
}


// Prints the game grid with numbers
void Board::print()
{
    for(unsigned int row = 0; row < SIZE; ++row)
    {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int x = 0; x < SIZE; ++x)
        {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            if(grid_.at(row).at(x) != EMPTY)
            {
                std::cout << grid_.at(row).at(x);
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}


// Changes grid with a new vector, empty place and one number change
// places
// Parameter is a new 2D vector to the grid.
void Board::changeGrid(std::vector< std::vector<unsigned int>> newGridvector)
{
    grid_ = newGridvector;
}


// Checks if the player has won, numbers 1-16 must be in the right order and empty space
// must be the last.
// Returns true if the player has won, else returns false.
bool Board::winningGrid()
{
    int row = 0;
    int i = 0;
    for (unsigned int number=1; number <= NUMBERS; ++number) {
        if (grid_.at(row).at(i) != number) {
            return false;
        }
        if (number % 4 == 0) {
            ++row;
            i = 0;
        }
        else {
            ++i;
        }
    }
    return true;
}
