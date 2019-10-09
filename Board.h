#ifndef BOARD_H
#define BOARD_H

#include "Player.h"
#include "TileCodes.h"
#include <algorithm>
#include <map>
using std::vector;
using std::endl;
using std::cout;

const int ROWS = 27;
const int COLS = 27;

class Board {
public:
    //constructor
    Board();
    //print board to console
    void printBoard();
    //returns board size
    int getBoardSize();
    //sets the board size
    void setBoardSize(int size);
    //checks critera for move and calls other functions for criteria
    bool makeMove(Player& player, int row, int col, Tile* tile);
    //checks if tile is on a valid location, not a line
    bool tileOnALocation(int row, int col);
    //set a board tile 
    void setTile(int row, int col, Colour colour, Shape shape);
    //get tile at position(row,col)
    Tile* getTile(int row, int col);

    //returns the amount of points for a tile placed in (row,col)
    int getMovePoints(int placedRow, int placedCol);

    bool firstTurn();

    bool notMatchingTile(int row, int col, Tile* tile);

    //checks if there is an identical tile in the same line
    bool notTileInLine(int placedRow,int placedCol, Tile* tile);
    //checks the row that the tile is in and that it either matches colour or shape
    bool rowTilesMatch(int placedRow, int placedCol,Tile* tile);

    bool rowTilesMatching;
    
private:
    Tile* array[ROWS][COLS];
    int boardSize;
    char alphabet[26];
};

#endif