
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
      cout << endl;

      if(std::cin.eof()) {
         cout << endl << "Goodbye." << endl;
         exit(0); 
      }

      if (input == NEW_GAME) { //1
         newGame();
      }
      else if (input == LOAD_GAME) { //2
         loadGame();
      }
      else if (input == STUDENT_INFO) { //3
         showInfo();
      }
      else if (input == HELP) { //4
         helpMenu();
      }
      else if (input == QUIT) { //5
         cout << "Goodbye. \n" << endl;
      } else {
         cout << "Invalid Input. \n" << endl;
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
      cout << "Enter a name for Player " << i+1 << ":" << endl;
      Player* tempPlayer = getNewPlayer();
      players.push_back(tempPlayer);
   }
   //get new hands for players
   for (int i=0; i<maxPlayers; i++) {
      Player* tempPlayer = players.at(i);
      //create a new hand for player
      LinkedList* newHand = new LinkedList();
      for (int i=0; i<HAND_SIZE; i++) {
         Tile* t = tileBag->removeFirst();
         newHand->addLast(t);
      }
      tempPlayer->setDeck(newHand);
   }

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
      board.printBoard();

      //Print current players hand
      cout << endl << "Your hand is:" << endl;
      LinkedList* hand = objCurPlayer->getDeck();
      for (int i=0; i<hand->size(); i++) {
         cout << hand->get(i)->getTileCode();
         if (i!=hand->size()-1) {
            cout << ", ";
         }
      }
      cout << endl << endl;
      
      takeTurn();

      currentPlayer+=1;
      //check if back to player 1's turn
      if (currentPlayer%maxPlayers == 0) {
         currentPlayer = 0;
      }

      // //temporary call to end while
      // gameOver = true;
   }
}

void Qwirkle::takeTurn() {
   Player& player = *players.at(currentPlayer);
   std::string line;
   bool is_end = true; // whether the stream is end
   bool flag = false; // whether the input is end

   std::cin.clear();
   std::cin.ignore(INT_MAX,'\n');
   cout << "> ";
   while (!flag && std::getline(std::cin, line)) {
      try {
         std::stringstream input_stream(line);
         std::string prompt;
         input_stream >> prompt;

         // place ** at **/***
         if (prompt == "place") {
            if (line.length() != 14 && line.length() != 15) {
               cout << "Wrong format! Type 'help' for the list of commands.\n> ";
               continue;
            }
            std::string tile = line.substr(6, 2);
            std::string location;
            // check length illegal
            if (line.length() == 14) {
               location = line.substr(12, 2);
            } else {
               location = line.substr(12, 3);
            }
            // check tile illegal
            if (tile[0] != 'R' && tile[0] != 'O' && tile[0] != 'Y' && tile[0] != 'G' && tile[0] != 'B' && tile[0] != 'P') {
               cout << "The color of the tile is invalid!\n> ";
               continue;
            }
            if (!(tile[1] - '0' >= 1 && tile[1] - '0' <= 6)) {
               cout << "The shape of the tile is invalid!\n> ";
               continue;
            }
            // check location illegal
            if (location.length() == 2) {
               if (!(location[0] - 'A' >= 0 && location[0] - 'A' <= 25 && location[1] - '0' >= 0 && location[1] - '0' <= 9)) {
                  cout << "The location is illegal!\n> ";
                  continue;
               }
            } else {
               if (!(location[0] - 'A' >= 0 && location[0] - 'A' <= 25 && ((location[1] - '0') * 10 + (location[2] - '0')) >= 10 && ((location[1] - '0') * 10 + (location[2] - '0')) <= 25)) {
                  cout << "The location is illegal!\n> ";
                  continue;
               }
            }
            Tile* oldTile = new Tile(tile[0], (tile[1] - '0'));
            cout << oldTile->getColour() << oldTile->getShape() << endl;
            // check if the tile exists
            if (!player.getDeck()->find(oldTile)) {
               cout << "This tile is not in you hand!\n> ";
               continue;
            }
            int row = location[0] - 'A';
            int col = std::stoi(std::string(location.begin() + 1, location.end()));
            if (!board.makeMove(player, row, col, oldTile)) {
               cout << "The location is occupied\n> ";
               continue;
            }
            if (!tileBag->isEmpty()) {
               Tile* newTile = tileBag->removeFirst();
               player.placeTile(oldTile, newTile);
            } else {
               player.placeTile(oldTile, nullptr);
            }
            is_end = false;
            flag = true;
         } else if (prompt == "replace") {
            // replace **
            if (line.length() != 10) {
               cout << "Wrong format! Type 'help' for the list of commands.\n> ";
               continue;
            }
            std::string tile;
            input_stream >> tile;
            Tile* oldTile = new Tile(tile[0], tile[1] - '0');
            if (!player.getDeck()->find(oldTile)) {
               cout << "This tile is not in your hand!\n\n> ";
               continue;
            }
            if (tileBag->isEmpty()) {
               cout << "Bag is empty and you can't replace\n\n> ";
               continue;
            }
            player.replaceTile(oldTile, tileBag->removeFirst());
            tileBag->addLast(oldTile);
            is_end = false;
            flag = true;
         } else if (prompt == "save") {
               // TODO
               // std::string file;
               // if (line.length() < 6) {
               //    throw std::string(
               //       "Filename not specified. Game save failed.");
               // }
               // file = line.substr(5);
               // //saveGame(file, player); //TODO
               continue;
         } else if (prompt == "help") {
               helpMenu();
               cout << "> ";
               continue;
         } else {
               cout << "This command is not found! \n";
               cout << "You can use 'help' to ask for help.\n> ";
               continue;
         }
      } catch (std::invalid_argument ex) {
         std::cin.clear();
         cout << "Location is invalid\n"
                     << "> ";
      }
   }
   if (is_end) {
      cout << "\nGoodbye.\n";
      exit(EXIT_SUCCESS);
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
         cout << "Invalid input for player name. Must contain letters only. \n"
                   << endl;
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
   cout << "--------------------------------" << endl;
   cout << "Name: Dylan Gutbier" << endl;
   cout << "Student ID: s3660481" << endl;
   cout << "Email: s3660481@student.rmit.edu.au \n"
             << endl;

   cout << "Name: Jack Ryan" << endl;
   cout << "Student ID: s3655960" << endl;
   cout << "Email: s3655960@student.rmit.edu.au \n"
             << endl;

   cout << "Name: Aaron Chan" << endl;
   cout << "Student ID: sXXXXXXX" << endl;
   cout << "Email: sXXXXXXX@student.rmit.edu.au \n" 
             << endl;

   cout << "Name: Tharvind Kalaiarasan" << endl;
   cout << "Student ID: sXXXXXXX" << endl;
   cout << "Email: sXXXXXXX@student.rmit.edu.au \n"
             << endl;

   cout << "Name: Thien Nguyen" << endl;
   cout << "Student ID: sXXXXXXX" << endl;
   cout << "Email: sXXXXXXX@student.rmit.edu.au" << endl;
   cout << "-------------------------------- \n"
             << endl;

}

void Qwirkle::helpMenu()
{
   //TODO Milestone 3
   cout << "Help Menu - List of Commands:\n";
   cout << "--------------------------\n";
   cout << "'replace' eg: replace O6\n";
   cout << "'place' eg: place O6 at A0\n";
   cout << "'save' eg: save filename\n";
   cout << "'Ctrl+D' Exit Immediately\n";
   cout << endl;
}
