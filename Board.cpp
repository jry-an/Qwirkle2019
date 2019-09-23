#include "Board.h"

Board::Board()
{
    for (int row = 0; row < ROWS; row++) {
        for (int column = 0; column < COLS; column++) {
            array[row][column] = new Tile;
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
    int size = boardSize;
    
    // Check if board size is 0 (no tile placed yet)
    if(boardSize == 0) {
        size = 17;
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
    cout << "   --";
    for(int i=0; i<=size; i++) {
        //check if even number
        if (i%2 == 0) {
            cout << "-----";
        }
    }
    cout << "--" << endl;

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
    cout << "--" << endl;

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