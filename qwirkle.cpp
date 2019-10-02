
#include "Qwirkle.h"


Qwirkle::Qwirkle()
{
       tileBag = new LinkedList;
}

Qwirkle::Qwirkle(int numPlayers)
{
   maxPlayers = numPlayers;
   tileBag = new LinkedList();
}

Qwirkle::~Qwirkle()
{
   delete tileBag;
}

void Qwirkle::start()
{
   //Player* players = new Player[2];
   int input = 0;

   // While the user is playing the game - print the menu
   // and get the input for
   while (input != QUIT)
   {
      //print menu
      printMenu();

      //get input from user
      cout << "> ";
      std::cin >> input;
      std::cout << std::endl;

      if(std::cin.eof()) {
         cout << endl << "Goodbye." << endl;
         exit(0); 
      }

      if (input == NEW_GAME)
      { //1
         newGame();
      }
      else if (input == LOAD_GAME)
      { //2
         loadGame();
      }
      else if (input == STUDENT_INFO)
      { //3
         showInfo();
      }
      else if (input == HELP)
      { //4
         helpMenu();
      }
      else if (input == QUIT)
      { //5
         std::cout << "Goodbye. \n"
                   << std::endl;
      }
      else
      {
         std::cout << "Invalid Input. \n"
                   << std::endl;
         start();
      }
   }
}

void Qwirkle::printMenu()
{
    cout << "Menu" << endl;
    cout << "----" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Show student information" << endl;
    cout << "4. Help!" << endl;
    cout << "5. Quit" << endl << endl;
}

void Qwirkle::shuffleTileBag() 
{
   //TODO Tharvind 
}

LinkedList* Qwirkle::getNewDeck()
{
    LinkedList* list = new LinkedList;
    for (int i = 0; i < 6; i++) {
        list->addLast(tileBag->removeFirst());
    }
    return list;
}


void Qwirkle::newGame()
{
   gameBoard = new Board();
   Colour colourList[] = { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE };
   Shape shapeList[] = { CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER };
   
   // Clear tilebag incase new game is being started 
   // without previous game having finished.
   tileBag->clear();
   
   // Initialise tileBag (unshuffled)
   for (int t=0; t<2; t++) {
      for (int i=0; i<6; i++) {
         for (int j=0; j<6; j++) {
            Tile* tempTile = new Tile(colourList[i], shapeList[j]);
            cout << tempTile->getColour() <<" " << tempTile->getShape()  << endl;
            tileBag->addLast(tempTile);
         }
      }
   }
   //call tileBag shuffle method, which shuffles the contents of the tileBag 
   shuffleTileBag();

   //get new players
   players.clear();
   for (int i=0; i<maxPlayers; i++) {
      cout << "Enter a name for Player" << i+1 << ":" << endl;
      Player* tempPlayer = getNewPlayer();
      players.push_back(tempPlayer);
   }

   //give each player a new hand
   //TODO

   //set whos turn it is. (Player1 for new games)
   currentPlayer = 0;
   
   //start the game
   playGame();

}

void Qwirkle::playGame() {
   bool gameOver = false;
   
   while (!gameOver) {
      Player* objCurPlayer = players.at(currentPlayer);
      // Print current player and scores

      cout << endl << endl
            << objCurPlayer->getName() << ", it's your turn." << endl << endl;
      
      for (int i=0; i<maxPlayers; i++) {
         cout << "Score for " << players.at(i)->getName() << ": \t" << players.at(i)->getScore() << endl;
      }
      cout << endl;

      // Print the game board
      gameBoard->printBoard();
      cout << "tileBag: ";
      tileBag->print();
      cout << endl;

      //TODO: (When linked list is ready)
      //Print current players hand
      cout << "Your hand is" << endl << objCurPlayer->getDeck() << endl;
      //LinkedList* deck = objCurPlayer->getDeck();
      
      //temporary call to end while
      gameOver = true;
   }
}

Player* Qwirkle::getNewPlayer() 
{
   bool badInput = true;
   std::string name;

   while (badInput) {
      //get input for name

      cout << "> ";
      std::cin >> name;
      if(std::cin.eof()) {
         cout << endl << "Goodbye." << endl;
         exit(0); 
      }
      //check that input contains only letters
      badInput = std::find_if(name.begin(), name.end(), non_alpha()) != name.end();

      if (badInput == true) {
         std::cout << "Invalid input for player name. Must contain letters only. \n"
                   << std::endl;
      }
   }
   std::transform(name.begin(), name.end(),name.begin(), ::toupper);
   
   Player* player = new Player(name);
   //NOTE: Input for player names must be letters only

   
   return player;
}

void Qwirkle::loadGame()
{

}
void Qwirkle::saveGame(std::string filename, Player player)
{

}

void Qwirkle::showInfo()
{
   std::cout << "--------------------------------" << std::endl;
   std::cout << "Name: Dylan Gutbier" << std::endl;
   std::cout << "Student ID: s3660481" << std::endl;
   std::cout << "Email: s3660481@student.rmit.edu.au \n"
             << std::endl;

   std::cout << "Name: Jack Ryan" << std::endl;
   std::cout << "Student ID: s3655960" << std::endl;
   std::cout << "Email: s3655960@student.rmit.edu.au \n"
             << std::endl;

   std::cout << "Name: Aaron Chan" << std::endl;
   std::cout << "Student ID: sXXXXXXX" << std::endl;
   std::cout << "Email: sXXXXXXX@student.rmit.edu.au \n" 
             << std::endl;

   std::cout << "Name: Tharvind Kalaiarasan" << std::endl;
   std::cout << "Student ID: sXXXXXXX" << std::endl;
   std::cout << "Email: sXXXXXXX@student.rmit.edu.au \n"
             << std::endl;

   std::cout << "Name: Thien Nguyen" << std::endl;
   std::cout << "Student ID: sXXXXXXX" << std::endl;
   std::cout << "Email: sXXXXXXX@student.rmit.edu.au" << std::endl;
   std::cout << "-------------------------------- \n"
             << std::endl;

}

void Qwirkle::helpMenu()
{
   //TODO Milestone 3
}
