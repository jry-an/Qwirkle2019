// Initial class with main method
// Used to initialise the game
#include "Qwirkle.h"
#include <iostream>

#define EXIT_SUCCESS 0

int main()
{
    std::string line;
    int players = 0;
    cout << "Welcome to Qwirkle." << endl << endl;

    while (players<2 || players>4) {
        cout << "How many players? (2-4)" << endl;
        cout << "> ";
        
        std::getline(std::cin, line);

        if (std::cin.eof()) {
            cout << "Goodbye." << endl;
            exit(EXIT_SUCCESS);
        }
        try {
            players = stoi(line);

            if (players<2 || players>4) {
                cout << "Invalid input. There may only be 2-4 players." << endl << endl;
            }
        }
        catch(...){
            cout << "Invalid input. There may only be 2-4 players." << endl << endl;
        }
    }

    Qwirkle *qwirkleGame = new Qwirkle(players);
    qwirkleGame->start();

    delete qwirkleGame;

    return EXIT_SUCCESS;
}