// Initial class with main method
// Used to initialise the game
#include "Qwirkle.h"
#include <iostream>

#define EXIT_SUCCESS 0

int main()
{
    cout << endl << "Welcome to Qwirkle." << endl << endl;

    Qwirkle *qwirkleGame = new Qwirkle();
    qwirkleGame->start();

    delete qwirkleGame;

    return EXIT_SUCCESS;
}