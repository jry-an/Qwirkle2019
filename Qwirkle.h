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

enum Turn { PLAYER1,
PLAYER2 };

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
    Qwirkle(int numPlayers);
    ~Qwirkle();

    Player* getNewPlayer();
    void newGame();
    void loadGame();
    void saveGame(std::string filename, Player player);
    void showInfo();
    void helpMenu();
    void printMenu();
    void playGame();
    LinkedList* getNewDeck();
    void start();
    void takeTurn();

    LinkedList* tileBag;
    Board board;
    Turn turn;

private:
    Board *gameBoard;
    std::vector<Player*> players;
    int maxPlayers;
    int currentPlayer;
};

#endif