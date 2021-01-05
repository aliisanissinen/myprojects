// Game15 (or puzzle 15)
//
// Program author
// Name: Aliisa Nissinen
// Student number: 291603
// UserID: kralni
// E-Mail: aliisa.nissinen@tuni.fi
//
// Instructions:
// This program generates a 15 puzzle. The board is the size of 4 x 4,
// and every round the player chooses a direction and a number tile,
// making the given tile to be moved to the given direction.
// Game will end when the numbers 1-15 (1-16) are in the ascending order,
// starting from top left and proceeding row by row.
// Empty space is represented by the number 16 in the code (constant EMPTY)
// and by dot when printing the game board.


#include "board.hh"
#include <random>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


const int NUMBERS = 16;
const unsigned int EMPTY = 16;


// Finds the number in a vector.
// Given parameters is a 1D vector and number to find.
// Return index of the number.
int findIndex(std::vector<unsigned int> oneDvector, int findNumber)
{
    std::vector<unsigned int>::iterator find =
            std::find(oneDvector.begin(), oneDvector.end(), findNumber);
    int index = std::distance(oneDvector.begin(), find);
    return index;
}


// Shuffles 1D vector numbers randomly by using seed as a seed value.
// Parameters 1D vector and a seed number.
// Returns nothing, edit 1D vector directly into randomInit function.
void myShuffle(std::vector<unsigned int>& oneDvector, int seed)
{
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, oneDvector.size() - 1);
    for(unsigned int i = 0; i < oneDvector.size(); ++i)
    {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = oneDvector.at(i);
        oneDvector.at(i) = oneDvector.at(random_index);
        oneDvector.at(random_index) = temp;
    }
}


// The function makes a 2D vector.
// Preset parameter a 1D vector that becomes a 2D vector (or returns
// empty if the player quits the game).
// Returns the 2D vector.
std::vector<std::vector<unsigned int>> make2Dvector(vector<unsigned int> oneDvector)
{
    std::vector<std::vector<unsigned int>> twoDvector(4);
    int row = 0;
    for(int i = 0; i < NUMBERS; ++i) {
            twoDvector.at(row).push_back(oneDvector.at(i));
        if ((i+1) % 4 == 0) {
            ++row;
        }
    }
    return twoDvector;
    }


// The function makes a 1D vector.
// Preset parameters a 2D vector that becomes a 1D vector
// and bool that tells if there is an old 2D vector (if not, then 2D vector is empty).
// Returns 1D vector.
std::vector<unsigned int> make1Dvector(std::vector<std::vector<unsigned int>> twoDvector={{}},
                                       bool oldVector=false)
{
    std::vector<unsigned int> oneDvector;

    if (not oldVector) {
        for (unsigned int i = 1; i <= NUMBERS; ++i) {
            oneDvector.push_back(i);
        }
    }
    else {
        int row = 0;
        while (row < 4){
            for (unsigned i = 0; i < twoDvector.at(row).size(); ++i) {
                oneDvector.push_back(twoDvector.at(row).at(i));
               }
        ++row;
        }
    }
    return oneDvector;
}

// Moves number at the game grid if possible (d = to the right, a = to the left,
// w = up, s = down). Player can also enter q, if he wants to end the game, then
// game stops immediatly.
// Parameter is a 2D vector with the game grid numbers.
// Return a 2D vector (or empty vector if player quits the game).
std::vector< std::vector<unsigned int>> prompt(std::vector<std::vector<unsigned int>> twoDvector)
{
   std::cout << "Dir (command, number): ";
   string dir;
   getline(std::cin, dir);
   std::string::size_type b = dir.find_first_of(" ");
   string command = dir.substr(0, b);

   if (command == "q") {
       return {};
   }

   dir.erase(0,b);
   int number = stoi(dir);

   if (command != "a" and command != "d" and command != "s" and command != "w") {
       cout << "Unknown command: " << command <<endl;
       return twoDvector;
   }
   else if (1 > number or number > 16) {
       cout << "Invalid number: " << number <<endl;
       return twoDvector;
   }
   else {
       std::vector<unsigned int> oneDvector = make1Dvector(twoDvector, true);

       // Finds given number at the game grid
       int indexnumberFind = findIndex(oneDvector, number);
       // Finds an empty at the game grid
       int indexemptyFind = findIndex(oneDvector, EMPTY);

       struct CommandsNumber {
           string letter;
           int letterNumber;
       };
       // All possible directions to move and how much vector element has to
       // move at 1D vector
       const std::vector<CommandsNumber> commands =
       {{"a", 1}, {"d", (-1)}, {"w", 4}, {"s", (-4)}};

       for (auto s : commands) {
            if (s.letter == command) {
                try
                {
                if (oneDvector.at(indexnumberFind) ==
                        oneDvector.at(indexemptyFind+s.letterNumber)) {
                    std::swap(oneDvector.at(indexnumberFind),oneDvector.at(indexemptyFind));
                    twoDvector = make2Dvector(oneDvector);
                    return twoDvector;
                }
                }
                catch (const std::out_of_range& e) {
                    cout << "Impossible direction: " << command <<endl;
                    return twoDvector;
                }
            }
       }
  cout << "Impossible direction: " << command <<endl;
  return twoDvector;
   }
}


// Checks if the game can be solved. The game can be solved if
// the sum of the inversions of the game grid numbers is even.
// Given parameter is 2D vector with the game grid numbers.
// Returns true if solvable, if not solvable then false.
bool isSolvable(std::vector<std::vector<unsigned int>> const& twoDvector)
{
    std::vector<unsigned int> oneDvector = make1Dvector(twoDvector, true);

    // Finds an empty at the game grid
    int indexnumberFind = findIndex(oneDvector, EMPTY);

    // K helps with how many rows have to go down, transferred empty to down row
    int k = (indexnumberFind / 4);
    for (int n=1; n < (4 - k); ++n) {
        std::swap(oneDvector.at(indexnumberFind),oneDvector.at(indexnumberFind+4));
        indexnumberFind= indexnumberFind + 4;
    }

    // Calculates the inversions
    int inversion = 0;
    for (int i=1; i < NUMBERS; ++i) {
        int indexordernumberFind = findIndex(oneDvector, i);
        for (int afterI = (indexordernumberFind+1); afterI < NUMBERS; ++afterI) {
            if (oneDvector.at(indexordernumberFind) > oneDvector.at(afterI)) {
                ++inversion;
            }
        }
    }

    if (inversion % 2 == 0) {
        cout << "Game is solvable: Go ahead!" <<endl;
        return true;
    }
    else {
        cout << "Game is not solvable. What a pity." <<endl;
        return false;
    }
}


// The player has chosen not random initialization and must enter numbers 1-16
// in the desired order. Entered numbers are turned into 1D vector
// and then this function calls the function that makes a 2D vector.
// Returns the 2D vector to the main function or an empty vector if some number
// between 1-16 is missed.
std::vector< std::vector<unsigned int>> notrandomInit()
{
    std::cout << "Enter the numbers 1-16 in a desired order (16 means empty):" <<endl;

    string string_integers;
    std::vector<unsigned int> oneDvector;
    std::string::size_type b = 0;

    while (oneDvector.size() != 16) {
        getline(std::cin, string_integers);

        // Moves integers from string to vector
        while ((b = string_integers.find_first_of(" ")) != std::string::npos) {
            if (b==0) {
                string_integers.erase(0, b+1);
            }
            else {
            oneDvector.push_back(stoi(string_integers.substr(0, b)));
            string_integers.erase(0, b+1);
            }
        }

        // Next "if" helps, if player enters empty rows between numbers
        if  (string_integers.size() != 0) {
            oneDvector.push_back(stoi(string_integers));
        }
    }

    // Checks that vector has all numbers 1-16
    for (unsigned int i=1; i < NUMBERS; ++i) {
          if (std::find(oneDvector.begin(), oneDvector.end(), i) != oneDvector.end()) {
              continue;
          }
          else {
              cout << "Number " << i << " is missing" <<endl;
              return {};
          }
    }

    std::vector<std::vector<unsigned int>> twoDvector = make2Dvector(oneDvector);
    return twoDvector;
}


// The player has chosen random initialization, numbers will be shuffled randomly
// by using a seed value that the player can enter. This function calls the function
// that makes a 1D vector and then the function that shuffles that 1D vector. Then
// 1D vector change to 2D vector in the function make2Dvector.
// Returns the 2D vector to the main function.
std::vector< std::vector<unsigned int>> randomInit()
{
    std::cout << "Enter a seed value (or an empty line): ";
    string seedString;
    getline(std::cin, seedString);
    int seed;

    if (seedString == "") {
        seed = time(NULL);
    }
    else {
        seed = stoi(seedString);
    }

    std::vector<unsigned int> oneDvector = make1Dvector();
    myShuffle(oneDvector, seed);
    std::vector<std::vector<unsigned int>> twoDvector = make2Dvector(oneDvector);
    return twoDvector;
}


// The Player can choose random initialization or not random initialization.
// Returns true or false, depends on initialization type.
bool initializationQuestions()
{
    while (true) {
        std::cout << "Random initialization (y/n): ";
        std::string random_initialization;
        getline(std::cin, random_initialization);

        if (random_initialization == "y" or random_initialization == "Y") {
            return true;
        }
        else if (random_initialization == "n" or random_initialization == "N") {
            return false;
        }
        else {
            cout << "Unknown choice: " << random_initialization <<endl;
            continue;
        }
    }
}


int main()
{
    bool random = initializationQuestions();
    std::vector<std::vector<unsigned int>> game15vector;

    if (random) {
        game15vector = randomInit();
    }
    else {
        game15vector = notrandomInit();
        // If one number between 1-16 is missed, the game stops.
        if  (game15vector.size() == 0) {
            return EXIT_FAILURE;
        }
    }

    if (isSolvable(game15vector)) {
        Board start(game15vector);

        while (true) {
            start.print();
            if (start.winningGrid()) {
                cout << "You won!" <<endl;
                return false;
            }
            // Moves number at the game grid, if possible
            game15vector = prompt(game15vector);
            // Player has quit the game
            if  (game15vector.size() == 0) {
                return false;
            }
            start.changeGrid(game15vector);
        }
    }
    return EXIT_SUCCESS;
}
