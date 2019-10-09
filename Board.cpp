#include "Board.h"

Board::Board()
{
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            array[row][col] = new Tile;
        }
    }
    // Used to check if anyone has placed a tile on
    // the board already for the first tile placement.
    this->boardSize = 0;

    //Initialise alphabet
    char letters[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    for (int i = 0; i < 26; i++) {
        alphabet[i] = letters[i];
    }
}

int Board::getBoardSize()
{
    return this->boardSize;
}

void Board::setBoardSize(int size)
{
    this->boardSize = size;
}

void Board::printBoard()
{
    std::map<Colour, std::string> color_map;
    color_map[RED] = "\033[31m";
    color_map[ORANGE] = "\033[91m";
    color_map[GREEN] = "\033[32m";
    color_map[BLUE] = "\033[34m";
    color_map[YELLOW] = "\033[33m";
    color_map[PURPLE] = "\033[35m";
    color_map[' '] = "\033[37m";

    int size = boardSize;

    // Check if board size is 0 (no tile placed yet)
    if (boardSize == 0) {
        size = 7;
    }

    // Print numbers at top. 0, 2, 4...
    cout << "     ";
    for (int i = 0; i <= size; i++) {
        //check if even number
        if (i % 2 == 0) {
            cout << i;
            if (i >= 10) {
                //one less space
                cout << "   ";
            }
            else {
                cout << "    ";
            }
        }
    }
    cout << endl;

    // Print -
    cout << "   ";
    for (int i = 0; i <= size; i++) {
        //check if even number
        if (i % 2 == 0) {
            cout << "-----";
        }
    }
    if (size % 2 == 0) {
        cout << "-";
    }
    else {
        cout << "----";
    }
    cout << endl;

    // Print Board with A, B, C...
    for (int i = 0; i <= size; i++) {
        cout << alphabet[i] << "  ";
        // Iterate through tiles in current row
        if (i % 2 == 0) {
            cout << "|";
            for (int j = 0; j <= size; j++) {
                if (j % 2 == 0) {
                    if (!array[i][j]->isEmpty()) {
                        std::cout << " ";
                        std::cout << color_map[array[i][j]->getColour()];
                        std::cout << array[i][j]->getTileCode();
                        std::cout << color_map[' '] << " |";
                    }
                    else {
                        std::cout << "  "
                                  << "  |";
                    }
                }
            }
        }
        else if (i % 2 == 1) {
            cout << "   |";
            for (int j = 0; j <= size; j++) {
                if (j % 2 == 1) {
                    if (!array[i][j]->isEmpty()) {
                        std::cout << " ";
                        std::cout << color_map[array[i][j]->getColour()];
                        std::cout << array[i][j]->getTileCode();
                        std::cout << color_map[' '] << " |";
                    }
                    else {
                        std::cout << "  "
                                  << "  |";

                    } // could be j before i, not sure until we implement
                }
            }
        }
        cout << endl;
    }

    // Print -
    cout << "   --";
    for (int i = 0; i <= size; i++) {
        //check if odd number
        if (i % 2 == 1) {
            cout << "-----";
        }
    }
    if (size % 2 == 0) {
        cout << "----";
    }
    else {
        cout << "--";
    }
    cout << endl;

    // Print numbers at bottom. 1, 3, 5...
    cout << "        ";
    for (int i = 0; i <= size; i++) {
        //check if odd number
        if (i % 2 == 1) {
            cout << i;
            if (i >= 10) {
                //one less space
                cout << "   ";
            }
            else {
                cout << "    ";
            }
        }
    }
    cout << endl;
}

bool Board::tileOnALocation(int row, int col)
{
    bool placeableLocation = false;
    if (row % 2 == 0 && col % 2 == 0) {
        placeableLocation = true;
    }
    else {
        if (row % 2 != 0 && col % 2 != 0) {
            placeableLocation = true;
        }
    }
    return placeableLocation;
}

bool Board::makeMove(Player& player, int row, int col, Tile* tile)
{
    //check if valid move (able to place tile there)
    //if location is empty
    //if surrounding have tile
    //get tile shape and color
    //if shape or color is equal, return true
    bool success = false;
    int score = 0;
    if ((row < 7 && col < 7) && boardSize == 7) {
        boardSize = 7;
    }
    else if (row == 25 || col == 25) {
        //dont expand
        boardSize = 25;
    }
    else {
        //board size check
        if (row >= boardSize) {
            boardSize = row + 1;
        }
        if (col >= boardSize) {
            boardSize = col + 1;
        }
    }

    //check if tile place is in bounds
    if (row >= 0 && col >= 0 && row < ROWS && col < COLS) {
        //check if tile spot if empty
        if (array[row][col]->isEmpty()) {
            if (!notMatchingTile(row, col, tile) && notTileInLine(row, col, tile) && rowTilesMatch(row, col, tile) && tileOnALocation(row, col)) {

                //up-left
                if (row >= 1 && col >= 1) {
                    if (!array[row - 1][col - 1]->isEmpty()) {
                        if (array[row - 1][col - 1]->getColour() == tile->getColour() || array[row - 1][col - 1]->getShape() == tile->getShape()) {
                            this->setTile(row, col, tile->getColour(), tile->getShape());
                            success = true;
                        }
                    }
                }

                //up-right
                if (row >= 1 && col < COLS) {
                    if (!array[row - 1][col + 1]->isEmpty()) {
                        if (array[row - 1][col + 1]->getColour() == tile->getColour() || array[row - 1][col + 1]->getShape() == tile->getShape()) {
                            this->setTile(row, col, tile->getColour(), tile->getShape());
                            success = true;
                        }
                    }
                }

                //down left
                if (row < ROWS && col >= 1) {
                    if (!array[row + 1][col - 1]->isEmpty()) {
                        if (array[row + 1][col - 1]->getColour() == tile->getColour() || array[row + 1][col - 1]->getShape() == tile->getShape()) {
                            this->setTile(row, col, tile->getColour(), tile->getShape());
                            success = true;
                        }
                    }
                }

                //down right
                if (row < ROWS && col < COLS) {
                    if (!array[row + 1][col + 1]->isEmpty()) {
                        if (array[row + 1][col + 1]->getColour() == tile->getColour() || array[row + 1][col + 1]->getShape() == tile->getShape()) {
                            this->setTile(row, col, tile->getColour(), tile->getShape());
                            success = true;
                        }
                    }
                }
                //if there are no tiles on the board, place
                if (firstTurn()) {
                    this->setTile(row, col, tile->getColour(), tile->getShape());
                    success = true;
                }
                if (success) {
                    score = getMovePoints(row, col);
                    if (score >= 6) {
                        std::cout << "\nQwirkle!!!\n";
                        score = score + 6;
                    }
                    player.setScore(score);
                }
                return success;
            }
        }
    }
    return success;
}

int Board::getMovePoints(int placedRow, int placedCol)
{
    int movePoints = 1;
    int tempRow = placedRow;
    int tempCol = placedCol;
    //up left
    if (placedRow >= 1 && placedCol >= 1) {
        while (!array[tempRow - 1][tempCol - 1]->isEmpty()) {
            movePoints++;
            tempRow = tempRow - 1;
            tempCol = tempCol - 1;
            if (tempRow < 1 || tempCol < 1) {
                break;
            }
        }

        tempRow = placedRow;
        tempCol = placedCol;
    }


    //up right
    if (placedRow <= ROWS && placedCol >= 1) {
        while (!array[tempRow + 1][tempCol - 1]->isEmpty()) {
            movePoints++;
            tempRow = tempRow + 1;
            tempCol = tempCol - 1;
            if (tempRow >= ROWS - 1 || tempCol < 1) {
                break;
            }
        }
        tempRow = placedRow;
        tempCol = placedCol;
    }

    //down left
    if (placedRow >= 1 && placedCol <= COLS) {
        while (!array[tempRow - 1][tempCol + 1]->isEmpty()) {
            movePoints++;
            tempRow = tempRow - 1;
            tempCol = tempCol + 1;
            if (tempRow < 1 || tempCol >= COLS - 1) {
                break;
            }
        }
        tempRow = placedRow;
        tempCol = placedCol;
    }

    //down right
    if (placedRow <= ROWS && placedCol <= COLS) {
        while (!array[tempRow + 1][tempCol + 1]->isEmpty()) {
            movePoints++;
            tempRow = tempRow + 1;
            tempCol = tempCol + 1;
            if (tempRow >= ROWS - 1 || tempCol >= COLS - 1) {
                break;
            }
        }
    }

    std::cout << "You got: " << movePoints << " points" << std::endl;
    return movePoints;
}

//you want this to return false, check if surrounding tiles are exact match
bool Board::notMatchingTile(int row, int col, Tile* tile)
{
    bool notMatchingTile = false;

    if (row >= 0 && col >= 0 && row < ROWS && col < COLS) {
        //upleft
        if (row >= 1 && col >= 1) {
            if (!array[row - 1][col - 1]->isEmpty()) {
                if (array[row - 1][col - 1]->getColour() != tile->getColour() && array[row - 1][col - 1]->getShape() != tile->getShape()) {
                    notMatchingTile = true;
                }
            }
        }

        //up-right
        if (row >= 1 && col < COLS) {
            if (!array[row - 1][col + 1]->isEmpty()) {
                if (array[row - 1][col + 1]->getColour() != tile->getColour() && array[row - 1][col + 1]->getShape() != tile->getShape()) {
                    notMatchingTile = true;
                }
            }
        }

        //down left
        if (row < ROWS && col >= 1) {
            if (!array[row + 1][col - 1]->isEmpty()) {
                if (array[row + 1][col - 1]->getColour() != tile->getColour() && array[row + 1][col - 1]->getShape() != tile->getShape()) {
                    notMatchingTile = true;
                }
            }
        }
        //down right
        if (row < ROWS && col < COLS) {
            std::cout << array[row + 1][col + 1]->getTileCode() << endl;
            if (!array[row + 1][col + 1]->isEmpty()) {
                if (array[row + 1][col + 1]->getColour() != tile->getColour() && array[row + 1][col + 1]->getShape() != tile->getShape()) {
                    notMatchingTile = true;
                }
            }
        }
    }
    return notMatchingTile;
}

bool Board::notTileInLine(int placedRow, int placedCol, Tile* tile)
{
    bool notInLine = true;
    bool emptyFound = false;

    //upleft
    if (placedRow >= 1 && placedCol >= 1) {
        for (int r = placedRow - 1; r > 0; r--) {
            for (int c = placedCol - 1; c > 0; c--) {
                  if (emptyFound == false) {
                if (!array[r][c]->isEmpty() && array[r][c]->isEqual(tile)) {
                    notInLine = false;
                }
                if (array[r][c]->isEmpty()) {
                            emptyFound = true;
                        }
                    }
            }
        }
    }
        emptyFound = false;

    //upright
    if (placedRow <= ROWS && placedCol > 0) {
        for (int r = placedRow + 1; r < ROWS; r++) {
            for (int c = placedCol - 1; c > 0; c--) {
                                    if (emptyFound == false) {

                if (!array[r][c]->isEmpty() && array[r][c]->isEqual(tile)) {
                    notInLine = false;
                }
                if (array[r][c]->isEmpty()) {
                            emptyFound = true;
                        }
                    }
            }
        }
    }
        emptyFound = false;


    //downleft
    if (placedRow > 0 && placedCol <= COLS) {
        for (int r = placedRow - 1; r > 0; r--) {
            for (int c = placedCol + 1; c < ROWS; c++) {
                                    if (emptyFound == false) {
                if (!array[r][c]->isEmpty() && array[r][c]->isEqual(tile)) {
                    notInLine = false;
                }
                if (array[r][c]->isEmpty()) {
                            emptyFound = true;
                        }
                    }
            }
        }
    }
        emptyFound = false;


    //down right
    if (placedRow <= ROWS && placedCol <= COLS) {
        for (int r = placedRow + 1; r < ROWS; r++) {
            for (int c = placedCol + 1; c < ROWS; c++) {
                                    if (emptyFound == false) {

                if (!array[r][c]->isEmpty() && array[r][c]->isEqual(tile)) {
                    notInLine = false;
                }
                if (array[r][c]->isEmpty()) {
                            emptyFound = true;
                        }
                    }
            }
        }
    }
        emptyFound = false;


    return notInLine;
}

bool Board::rowTilesMatch(int placedRow, int placedCol, Tile* tile)
{
    rowTilesMatching = true;
    bool emptyFound = false;

    //upleft colour
    if (placedRow >= 1 && placedCol >= 1) {
        if (array[placedRow - 1][placedCol - 1]->getColour() == tile->getColour()) {

            for (int r = placedRow - 1; r > 0; r--) {
                for (int c = placedCol - 1; c > 0; c--) {
                    if (emptyFound == false) {
                        if (!array[r][c]->isEmpty() && array[r][c]->getColour() != tile->getColour()) {
                            rowTilesMatching = false;
                        }
                        if (array[r][c]->isEmpty()) {
                            emptyFound = true;
                        }
                    }
                }
            }
        }
    }
    emptyFound = false;
    //upleft shape
    if (placedRow >= 1 && placedCol >= 1) {
        if (array[placedRow - 1][placedCol - 1]->getColour() == tile->getShape()) {
            for (int r = placedRow - 1; r > 0; r--) {
                for (int c = placedCol - 1; c > 0; c--) {
                    if (emptyFound == false) {
                        if (!array[r][c]->isEmpty() && array[r][c]->getShape() != tile->getShape()) {
                            rowTilesMatching = false;
                        }
                        if (array[r][c]->isEmpty()) {
                            emptyFound = true;
                        }
                    }
                }
            }
        }
    }
    emptyFound = false;

    //upright colour
    if (placedRow >= 1 && placedCol <= COLS) {
        if (array[placedRow - 1][placedCol + 1]->getColour() == tile->getColour()) {

            for (int r = placedRow - 1; r > 0; r--) {
                for (int c = placedCol + 1; c < COLS; c++) {
                    if (emptyFound == false) {
                        if (!array[r][c]->isEmpty() && array[r][c]->getColour() != tile->getColour()) {
                            rowTilesMatching = false;
                        }
                        if (array[r][c]->isEmpty()) {
                            emptyFound = true;
                        }
                    }
                }
            }
        }
    }
    emptyFound = false;

    //upright shape
    if (placedRow >= 1 && placedCol <= COLS) {
        if (array[placedRow - 1][placedCol + 1]->getShape() == tile->getShape()) {

            for (int r = placedRow - 1; r > 0; r--) {
                for (int c = placedCol + 1; c < COLS; c++) {
                    if (emptyFound == false) {
                        if (!array[r][c]->isEmpty() && array[r][c]->getShape() != tile->getShape()) {
                            rowTilesMatching = false;
                        }
                        if (array[r][c]->isEmpty()) {
                            emptyFound = true;
                        }
                    }
                }
            }
        }
    }
    emptyFound = false;

    //downleft colour
    if (placedRow > 0 && placedCol <= COLS) {
        if (array[placedRow - 1][placedCol + 1]->getColour() == tile->getColour()) {
            for (int r = placedRow - 1; r > 0; r--) {
                for (int c = placedCol + 1; c < ROWS; c++) {
                    if (emptyFound == false) {
                        if (!array[r][c]->isEmpty() && array[r][c]->getColour() != tile->getColour()) {
                            rowTilesMatching = false;
                        }
                        if (array[r][c]->isEmpty()) {
                            emptyFound = true;
                        }
                    }
                }
            }
        }
    }

    emptyFound = false;

    //downleft shape
    if (placedRow > 0 && placedCol <= COLS) {
        if (array[placedRow - 1][placedCol + 1]->getShape() == tile->getShape()) {
            for (int r = placedRow - 1; r > 0; r--) {
                for (int c = placedCol + 1; c < ROWS; c++) {
                    if (emptyFound == false) {
                        if (!array[r][c]->isEmpty() && array[r][c]->getShape() != tile->getShape()) {
                            rowTilesMatching = false;
                        }
                        if (array[r][c]->isEmpty()) {
                            emptyFound = true;
                        }
                    }
                }
            }
        }
    }
    emptyFound = false;
    //downright colour
    if (placedRow <= ROWS && placedCol <= COLS) {
        if (array[placedRow + 1][placedCol + 1]->getColour() == tile->getColour()) {
            for (int r = placedRow + 1; r < ROWS; r++) {
                for (int c = placedCol + 1; c < ROWS; c++) {
                    if (emptyFound == false) {
                        if (!array[r][c]->isEmpty() && array[r][c]->getColour() != tile->getColour()) {
                            rowTilesMatching = false;
                        }
                        if (array[r][c]->isEmpty()) {
                            emptyFound = true;
                        }
                    }
                }
            }
        }
    }
    emptyFound = false;

    if (placedRow <= ROWS && placedCol <= COLS) {
        if (array[placedRow + 1][placedCol + 1]->getShape() == tile->getShape()) {
            for (int r = placedRow + 1; r < ROWS; r++) {
                for (int c = placedCol + 1; c < ROWS; c++) {
                    if (emptyFound == false) {
                        if (!array[r][c]->isEmpty() && array[r][c]->getShape() != tile->getShape()) {
                            rowTilesMatching = false;
                        }
                        if (array[r][c]->isEmpty()) {
                            emptyFound = true;
                        }
                    }
                }
            }
        }
    }
    return rowTilesMatching;
}

Tile* Board::getTile(int row, int col)
{
    return array[row][col];
}

void Board::setTile(int row, int col, Colour colour, Shape shape)
{
    array[row][col] = new Tile(colour, shape);
}

bool Board::firstTurn()
{
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (!array[row][col]->isEmpty()) {
                return false;
            }
        }
    }
    return true;
}