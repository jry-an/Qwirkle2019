#include "Board.h"

Board::Board()
{
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLS; column++) {
            array[row][column] = new Tile;
        }
    }
    turnCount = 0;
}