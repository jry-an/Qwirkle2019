#ifndef BOARD_H
#define BOARD_H

#include "Player.h"
#include "TileCodes.h"
#include <algorithm>
#include <map>
using std::vector;

const int ROWS = 26;
const int COLS = 26;

class Board {
    public:
    Board();

private:
    Tile* array[ROWS][COLS];
    int turnCount;


};

#endif