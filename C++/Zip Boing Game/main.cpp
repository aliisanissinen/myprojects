#include <iostream>

using namespace std;

int main()
{
    int number = 0;
    std::cout << "How many numbers would you like to have? ";
    cin >> number;

    for ( int luku = 1; luku <= number; ++luku) {
        if ( (luku % 3) == 0 and (luku % 7) == 0) {
            cout << "zip boing" << endl;
    }
        else if ( (luku % 3) == 0) {
                cout << "zip" << endl;
    }
        else if ( (luku % 7) == 0) {
                cout << "boing" << endl;
    }
        else {
            cout << luku << endl;
    }
    }

}
