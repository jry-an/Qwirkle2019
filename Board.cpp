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
    char letters[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    for (int i=0; i<26; i++) {
        alphabet[i] = letters[i];
    }

}

void Board::printBoard() 
{

    std::map<Colour, std::string> color_map;
    color_map[RED] = "\033[31m";
    color_map[ORANGE] = "\033[33m";
    color_map[GREEN] = "\033[32m";
    color_map[BLUE] = "\033[34m";
    color_map[YELLOW] = "\033[33m";
    color_map[PURPLE] = "\033[35m";
    color_map[' '] = "\033[37m";


    int size = boardSize;
    
    // Check if board size is 0 (no tile placed yet)
    if(boardSize == 0) {
        size = 6;
    }

    // Print numbers at top. 0, 2, 4...
    cout << "     ";
    for(int i=0; i<=size; i++) {
        //check if even number
        if (i%2 == 0) {
            cout << i;
            if (i>=10) {
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
    for(int i=0; i<=size; i++) {
        //check if even number
        if (i%2 == 0) {
            cout << "-----";
        }
    }
    if (size%2 == 0) {
        cout << "-";
    }
    else {
        cout << "----";
    }
    cout << endl;

    // Print Board with A, B, C...
    for (int i=0; i<=size; i++) {
        cout << alphabet[i] << "  "; 
        // Iterate through tiles in current row
        if (i%2 == 0) {
            cout << "|";
            for (int j=0; j<=size; j++) {
                if (j%2 == 0) {
                 cout << " " << array[i][j]->getTileCode() << " |";
                }
            }
        }
        else if (i%2 == 1) {
            cout << "   |";
            for (int j=0; j<=size; j++) {
                if (j%2 == 1) {
                    cout << " " << array[i][j]->getTileCode() << " |"; // could be j before i, not sure until we implement
                }
            }
        }
        cout << endl;
    }

    // Print -
    cout << "   --";
    for(int i=0; i<=size; i++) {
        //check if odd number
        if (i%2 == 1) {
            cout << "-----";
        }
    }
    if (size%2 == 0) {
        cout << "----";
    }
    else {
        cout << "--";
    }
    cout << endl;

    // Print numbers at bottom. 1, 3, 5...
    cout << "        ";
    for(int i=0; i<=size; i++) {
        //check if odd number
        if (i%2 == 1) {
            cout << i;
            if (i>=10) {
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

bool Board::makeMove(Player& player, int row, int col, Tile* tile) {
    //check if valid move (able to place tile there)
    //if location is empty
    //if surrounding have tile
    //get tile shape and color
    //if shape or color is equal, return true
    bool success = false;

    if (array[row][col]->isEmpty()){
        //left
        if(row>=1 && !array[row-1][col-1]->isEmpty()){
            if(array[row-1][col-1]->getColour() == tile->getColour() || array[row-1][col-1]->getShape() == tile->getShape()){
                this->setTile(row,col,tile->getColour(),tile->getShape());
                success = true;
                std::cout << "left true" << std::endl;
            }
        }


        //right
        else if(row<= ROWS && !array[row-1][col+1] -> isEmpty()){
            if(array[row-1][col+1]->getColour() == tile->getColour() || array[row-1][col+1]->getShape() == tile->getShape()){
                this->setTile(row,col,tile->getColour(),tile->getShape());
                success = true;
                std::cout << "right true" << std::endl;

            }
        }


        //up
        else if(col>=1 && !array[row+1][col-1] -> isEmpty()){
             if(array[row+1][col-1]->getColour() == tile->getColour() || array[row+1][col-1]->getShape() == tile->getShape()){
                this->setTile(row,col,tile->getColour(),tile->getShape());
                success = true;
                std::cout << "up true" << std::endl;
            }
        }


        //down
        else if(row<=ROWS && !array[row+1][col+1] -> isEmpty()){
             if(array[row+1][col+1]->getColour() == tile->getColour() || array[row+1][col+1]->getShape() == tile->getShape()){
                this->setTile(row,col,tile->getColour(),tile->getShape());
                success = true;
                std::cout << "down true" << std::endl;

            }
        }
        //if there are no tiles on the board, place the tile at [row][col]
        else if(firstTurn()){
            this->setTile(row,col,tile->getColour(),tile->getShape());
            success = true;
            std::cout << "first turn placed" << std::endl;
        }
    }
        int score = getMovePoints();
        player.setScore(score);
        if (score == 6) {
            std::cout << "\nQwirkle!!!\n";
            player.setScore(score);
        }
        return success;
    }

int Board::getMovePoints()
{
    //TODO
    return 0;
}

Tile* Board::getTile(int row, int col) {
    return array[row][col];
}

void Board::setTile(int row, int col, Colour colour, Shape shape) {
    array[row][col] = new Tile(colour, shape);
}

bool Board::isEmpty()
{
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++) {
            if (array[i][j]->isEmpty())
                return true;
        }
    return false;
}

bool Board::firstTurn(){
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if(!array[row][col]->isEmpty()){
                return false;
            }
        }
    }
    return true;
}