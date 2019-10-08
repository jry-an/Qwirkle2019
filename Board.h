#ifndef BOARD_H
#define BOARD_H

#include "Player.h"
#include "TileCodes.h"
#include <algorithm>
#include <map>
using std::vector;
using std::endl;
using std::cout;

const int ROWS = 26;
const int COLS = 26;

class Board {
    public:
    Board();
    void printBoard();
    bool makeMove(Player& player, int row, int col, Tile* tile);
    bool isEmpty();
    void setTile(int row, int col, Colour colour, Shape shape);
    Tile* getTile(int row, int col);
    int getMovePoints(int placedRow, int placedCol);
    bool firstTurn();
    bool notMatchingTile(int row, int col, Tile* tile);

private:
    Tile* array[ROWS][COLS];
    int boardSize;
    char alphabet[26];


};

#endif