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

enum Turn { PLAYER1,
    PLAYER2 };

const int NEW_GAME = 1;
const int LOAD_GAME = 2;
const int STUDENT_INFO = 3;
const int HELP = 4;
const int QUIT = 5;

class Qwirkle {

public:
    //constructor and deconstructor (if needed)
    Qwirkle();
    ~Qwirkle();

    void shuffleTileBag();
    void newGame();
    void loadGame();
    void saveGame(std::string filename, Player player);
    void showInfo();
    void helpMenu();
    void printMenu();
    
    void start();

    LinkedList* tileBag;
    Player playerOne;
    Player playerTwo;
    Board board;
    Turn turn;
};

#endif