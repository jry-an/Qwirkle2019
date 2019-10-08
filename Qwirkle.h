/*  Main Qwirkle class which will store core
    functionality of the game
*/
#ifndef QWIRKLE_H
#define QWIRKLE_H

#include <algorithm>
#include <cctype>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <sstream>

#include "Board.h"
#include "Player.h"
#include "Tile.h"
#include "TileCodes.h"

struct non_alpha {
    bool operator()(char c)
    {
        return !std::isalpha(c);
    }
};

const int NEW_GAME = 1;
const int LOAD_GAME = 2;
const int STUDENT_INFO = 3;
const int HELP = 4;
const int QUIT = 5;
const int HAND_SIZE = 6;

class Qwirkle {
public:
    //constructor and deconstructor (if needed)
    Qwirkle();
    ~Qwirkle();

    int inputNumPlayers();
    Player* getNewPlayer();
    void newGame();
    void loadGame();
    void saveGame();
    void showInfo();
    void helpMenu();
    void printMenu();
    void playGame();
    LinkedList* getNewDeck();
    void start();
    void takeTurn();
    void displayPlayersScore();
    Player* getWinningPlayer();

    LinkedList* tileBag;
    Board board;
private:
    std::vector<Player*> players;
    int maxPlayers;
    int currentPlayer;
    bool playersHandEmpty();
};

#endif