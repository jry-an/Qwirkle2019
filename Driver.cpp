// Initial class with main method
// Used to initialise the game
#include "Qwirkle.h"
#include <iostream>

#define EXIT_SUCCESS 0

int main()
{
    cout << "Welcome to Qwirkle." << endl << endl;

    int players = 2;
    Qwirkle *qwirkleGame = new Qwirkle(players);
    cout << "OOPS";
    qwirkleGame->start();

    delete qwirkleGame;

    return EXIT_SUCCESS;
}