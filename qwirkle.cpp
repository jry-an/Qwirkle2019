
#include "Qwirkle.h"

Qwirkle::Qwirkle()
{
   tileBag = new LinkedList;
}

Qwirkle::~Qwirkle()
{
   delete tileBag;
}

int Qwirkle::inputNumPlayers() {
   //todo
   std::string line;
   int players = 0;

   while (players<2 || players>4) {
      cout << "How many players? (2-4)" << endl;
      cout << "> ";
      
      std::getline(std::cin, line);

      if (std::cin.eof()) {
         cout << "Goodbye." << endl;
         exit(EXIT_SUCCESS);
      }
      try {
         players = stoi(line);

         if (players<2 || players>4) {
               cout << "Invalid input. There may only be 2-4 players." << endl << endl;
         }
      }
      catch(...){
         cout << "Invalid input. There may only be 2-4 players." << endl << endl;
      }
   }
   return players;
}

void Qwirkle::start()
{
   int input = 0;
   std::string line;

   // While the user is playing the game - print the menu
   // and get the input for
   while (input != QUIT)
   {
      //print menu
      printMenu();

      //get input from user
      cout << "> ";
      std::getline(std::cin, line);
      std::stringstream input_stream(line);
      try {
         input = stoi(line);
      }
      catch(...){
         input = 0;
      }
      cout << endl;

      if (std::cin.eof())
      {
         cout << endl
              << "Goodbye." << endl;
         exit(0);
      }

      if (input == NEW_GAME)
      { //1
         maxPlayers = inputNumPlayers();
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
         cout << "Goodbye. \n"
              << endl;
      }
      else
      {
         cout << "Invalid Input. \n"
              << endl;
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
   cout << "5. Quit" << endl
        << endl;
}

LinkedList *Qwirkle::getNewDeck()
{
   LinkedList *list = new LinkedList;
   for (int i = 0; i < 6; i++)
   {
      list->addLast(tileBag->removeFirst());
   }
   return list;
}

void Qwirkle::newGame()
{
   Colour colourList[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
   Shape shapeList[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

   // Clear tilebag incase new game is being started
   // without previous game having finished.
   tileBag->clear();

   // Initialise tileBag (unshuffled)
   for (int t = 0; t < 2; t++)
   {
      for (int i = 0; i < 6; i++)
      {
         for (int j = 0; j < 6; j++)
         {
            Tile *tempTile = new Tile(colourList[i], shapeList[j]);
            tileBag->addLast(tempTile);
         }
      }
   }
   //call tileBag shuffle method, which shuffles the contents of the tileBag
   tileBag->shuffle();

   //get new players
   players.clear();
   for (int i = 0; i < maxPlayers; i++)
   {
      cout << "Enter a name for Player " << i + 1 << ":" << endl;
      Player *tempPlayer = getNewPlayer();
      players.push_back(tempPlayer);
   }
   //get new hands for players
   for (int i = 0; i < maxPlayers; i++)
   {
      Player *tempPlayer = players.at(i);
      //create a new hand for player
      LinkedList *newHand = new LinkedList();
      for (int i = 0; i < HAND_SIZE; i++)
      {
         Tile *t = tileBag->removeFirst();
         newHand->addLast(t);
      }
      tempPlayer->setDeck(newHand);
   }
   //clear cin buffer (ready for gameplay)
   std::cin.ignore(INT_MAX, '\n');

   //set whos turn it is. (Player1 for new games)
   currentPlayer = 0;

   //start the game
   playGame();
}

void Qwirkle::playGame()
{
   bool gameOver = false;

   while (!gameOver)
   {
      Player *objCurPlayer = players.at(currentPlayer);
      // Print current player and scores

      cout << endl
           << endl
           << objCurPlayer->getName() << ", it's your turn." << endl
           << endl;

      for (int i = 0; i < maxPlayers; i++)
      {
         cout << "Score for " << players.at(i)->getName() << ": \t" << players.at(i)->getScore() << endl;
      }
      cout << endl;

      // Print the game board
      board.printBoard();

      //Print current players hand
      std::cout << "\nYour hand is\n";
      std::cout << objCurPlayer->getDeck()->toString(true);
      ;
      cout << endl
           << endl;

      takeTurn();

      currentPlayer += 1;
      //check if back to player 1's turn
      if (currentPlayer % maxPlayers == 0)
      {
         currentPlayer = 0;
      }

      // //temporary call to end while
      // gameOver = true;
   }
}

void Qwirkle::takeTurn()
{
   Player &player = *players.at(currentPlayer);
   std::string line;
   bool is_end = true; // whether the stream is end
   bool flag = false;  // whether the input is end

   std::cin.clear();
   cout << "> ";
   while (!flag && std::getline(std::cin, line))
   {
      try
      {
         std::stringstream input_stream(line);
         std::string prompt;
         input_stream >> prompt;

         // place ** at **/***
         if (prompt == "place")
         {
            if (line.length() != 14 && line.length() != 15)
            {
               cout << "Wrong format! Type 'help' for the list of commands.\n\n> ";
               continue;
            }
            std::string tile = line.substr(6, 2);
            std::string location;
            // check length illegal
            if (line.length() == 14)
            {
               location = line.substr(12, 2);
            }
            else
            {
               location = line.substr(12, 3);
            }
            // check tile illegal
            if (tile[0] != 'R' && tile[0] != 'O' && tile[0] != 'Y' && tile[0] != 'G' && tile[0] != 'B' && tile[0] != 'P')
            {
               cout << "The color of the tile is invalid!\n\n> ";
               continue;
            }
            if (!(tile[1] - '0' >= 1 && tile[1] - '0' <= 6))
            {
               cout << "The shape of the tile is invalid!\n\n> ";
               continue;
            }
            // check location illegal
            if (location.length() == 2)
            {
               if (!(location[0] - 'A' >= 0 && location[0] - 'A' <= 25 && location[1] - '0' >= 0 && location[1] - '0' <= 9))
               {
                  cout << "The location is illegal!\n\n> ";
                  continue;
               }
            }
            else
            {
               if (!(location[0] - 'A' >= 0 && location[0] - 'A' <= 25 && ((location[1] - '0') * 10 + (location[2] - '0')) >= 10 && ((location[1] - '0') * 10 + (location[2] - '0')) <= 25))
               {
                  cout << "The location is illegal!\n\n> ";
                  continue;
               }
            }
            Tile *oldTile = new Tile(tile[0], (tile[1] - '0'));
            // check if the tile exists
            if (!player.getDeck()->find(oldTile))
            {
               cout << "This tile is not in you hand!\n\n> ";
               continue;
            }
            int row = location[0] - 'A';
            int col = std::stoi(std::string(location.begin() + 1, location.end()));
            if (!board.makeMove(player, row, col, oldTile))
            {
               cout << "Invalid move. Try again.\n\n> ";
               continue;
            }
            if (!tileBag->Empty())
            {
               Tile *newTile = tileBag->removeFirst();
               player.placeTile(oldTile, newTile);
            }
            else
            {
               player.placeTile(oldTile, nullptr);
            }
            is_end = false;
            flag = true;
         }
         else if (prompt == "replace")
         {
            // replace **
            if (line.length() != 10)
            {
               cout << "Wrong format! Type 'help' for the list of commands.\n\n> ";
               continue;
            }
            std::string tile;
            input_stream >> tile;
            Tile *oldTile = new Tile(tile[0], tile[1] - '0');
            if (!player.getDeck()->find(oldTile))
            {
               cout << "This tile is not in your hand!\n\n> ";
               continue;
            }

            //GameOver
            if (tileBag->Empty())
            {
               cout << "Bag is empty and you can't replace\n\n> ";
               continue;
            }
            player.replaceTile(oldTile, tileBag->removeFirst());
            tileBag->addLast(oldTile);
           // tileBag->shuffle();
            is_end = false;
            flag = true;
         }

         else if (prompt == "done" )
         {
            std::cout << "Game Over"<< std::endl;
            displayPlayersScore();
            std::cout << "Player "<< getWinningPlayer()->getName() + " won! " << std::endl;
            std::cout << "\nGoodbye. " << std::endl;
            exit(EXIT_SUCCESS);

            continue;
         }

         // Executes when Tilebag has no more tiles AND the players hand is empty
         else if (tileBag->Empty() && playersHandEmpty() )
         {
            std::cout << "Game Over"<< std::endl;
            displayPlayersScore();
            std::cout << "Player "<< getWinningPlayer()->getName() + " won! " << std::endl;
            std::cout << "\nGoodbye. " << std::endl;
            exit(EXIT_SUCCESS);
            continue;
         }
         else if (prompt == "save")
         {
            saveGame();
            continue;
         }
         else if (prompt == "help")
         {
            helpMenu();
            cout << "> ";
            continue;
         }
         else
         {
            cout << "This command is not found! \n";
            cout << "You can use 'help' to ask for help.\n\n> ";
            continue;
         }
      }
      catch (std::invalid_argument &)
      {
         std::cin.clear();
         cout << "Location is invalid\n"
              << "> ";
      }
   }
   if (is_end)
   {
      cout << "\nGoodbye.\n";
      exit(EXIT_SUCCESS);
   }
}

Player *Qwirkle::getNewPlayer()
{
   bool badInput = true;
   std::string name;

   while (badInput)
   {
      //get input for name

      cout << "> ";
      std::cin >> name;
      if (std::cin.eof())
      {
         cout << endl
              << "Goodbye." << endl;
         exit(EXIT_SUCCESS);
      }
      //check that input contains only letters
      badInput = std::find_if(name.begin(), name.end(), non_alpha()) != name.end();

      if (badInput == true)
      {
         cout << "Invalid input for player name. Must contain letters only. \n"
              << endl;
      }
   }
   std::transform(name.begin(), name.end(), name.begin(), ::toupper);

   Player *player = new Player(name);
   //NOTE: Input for player names must be letters only

   return player;
}

void Qwirkle::loadGame() {
   std::string line = "";
   std::ifstream loadFile;
   std::string filename;
   bool validFileName = false;

   cout << "Enter the name of the save game to load: " << 
      endl << "'exit' to return to menu." << endl;

   while (!validFileName) {
      std::cin.clear();
      std::getline(std::cin, line);
      std::stringstream input_stream(line);
      input_stream >> filename;

      
      if (filename == "exit") {
         return;
      }
      loadFile.open("saves/"+filename+".save");
      if (!loadFile) {
         cout << "Could not find this saved game. 'exit to return to menu." << endl;
      }
      else {
         validFileName = true;
      }
      
   }
   //get maxPlayers
   std::getline(loadFile, line);
   std::istringstream iss(line);
   if (!(iss >> maxPlayers)) {
      cout << "Error loading game, file corrupt." << endl << endl;
      return; 
   }

   // delete old players
   if (players.size()!=0) {
      for (int i=0; i<players.size(); i++) {
         delete players.at(i);
      }
   }
   players.clear();

   //for all the players get 3 related lines from load file and create player object for each 
   for (int i=0; i!=maxPlayers; i++){
      std::string name;
      int points;
      LinkedList* hand;

      //create player object
      std::getline(loadFile, line);
      std::stringstream input_stream(line);
      input_stream >> name;
      Player* player = new Player(name);
      players.push_back(player);

      //add points
      std::getline(loadFile, line);
      std::istringstream iss(line);
      if (!(iss >> points)) {
         cout << "Error loading game, file corrupt." << endl << endl;
         return; 
      }
      player->setScore(points);

      //read in hand
      std::getline(loadFile, line);
      char colour;
      int shape;
      hand = new LinkedList();
      for (unsigned int j = 0; j != 6; j++)
      {
         int numTiles = (line.length() + 1) / 3;
         if (j<numTiles)
         {
            colour = line[3 * j];
            shape = line[3 * j + 1] - '0';
            hand->addLast(new Tile(colour, shape));
         }
      }
      player->setDeck(hand);
   }

   //load board
   std::getline(loadFile, line);
   std::getline(loadFile, line);

   std::vector<Tile*> tiles;
   std::vector<char> locationX;
   std::vector<char> locationY;

   board = Board();
   std::getline(loadFile, line);
   if (line[3] != '-') { //check to see if reached start of board
      int rows = 0;

      while (line[3]!='-') {
         for (unsigned int i = 4; i != line.length(); i++) {
            if (line[i] > 'A' && line[i] < 'Z')
            {
               char colour = line[i];
               int shape = line[i + 1] - '0';
               Tile *tile = new Tile(colour, shape);
               tiles.push_back(tile); //list of tiles found

               // find tiles corresponding row and col and add to board
               int tileRow = line[0] - 'A';
               int tileCol = 0;
               for (int j=1; j<i; j++) {
                  if (line[j]== '|') {
                     tileCol++;
                  }
               }
               tileCol*=2;
               if(tileRow%2==0){
                  tileCol=tileCol-2;
               }
               else {
                  tileCol--;
               }
               cout << "adding tile " << colour << shape << " to pos " << tileRow << "," << tileCol << endl;
               board.setTile(tileRow, tileCol, colour, shape);

            }
         }
         ++rows;
         getline(loadFile, line);
      }
      getline(loadFile, line);

      //set boardsize
      if (rows>=24 ) {
         rows=26;
      }
      board.setBoardSize(rows-1);
   }
   else {
      cout << "Error loading game, file corrupt." << endl << endl;
      return; 
   }

   //read in tilebag
   std::getline(loadFile, line);
   char colour;
   int shape;
   this->tileBag = new LinkedList();
   int numTiles = (line.length() + 1) / 3;

   for (unsigned int j = 0; j != numTiles; j++)
   {
      colour = line[3 * j];
      shape = line[3 * j + 1] - '0';
      tileBag->addLast(new Tile(colour, shape));
   }

   //check whos turn
   std::getline(loadFile, line);
   for (int i=0; i<players.size(); i++) {
      std::string name;
      std::stringstream input_stream(line);
      input_stream >> name;   
      if (players.at(i)->getName() == name) {
         currentPlayer = i;
      }
   }


   //successfully loaded file
   cout << "Successfully loaded game. Starting game..." << endl << endl;
   loadFile.close();

   //call playGame
   playGame();
}
void Qwirkle::saveGame()
{
   int size = board.getBoardSize();

   //open file for saving
   std::string filename;
   std::string line;
   std::cout << "Enter the name of the file to save as:" << std::endl;
   std::cout << "> ";
   std::getline(std::cin, line);
   std::stringstream input_stream(line);
   input_stream >> filename;

   if (!std::cin.eof())
   {
      filename += ".save";
      std::ofstream outFile;
      outFile.open("saves/"+filename);

      //save player info
      outFile << maxPlayers << std::endl;
      for (int p = 0; p != maxPlayers; p++)
      {
         outFile << players[p]->getName() << std::endl;
         outFile << players[p]->getScore() << std::endl;
         std::string hand = players[p]->getDeck()->toString(false);
         outFile << hand;
      }

      // save board
      // Print numbers at top
      outFile << "     ";
      for (int i = 0; i <= size; i++)
      {
         //check if even number
         if (i % 2 == 0)
         {
            outFile << i;
            if (i >= 10)
            {
               //one less space
               outFile << "   ";
            }
            else
            {
               outFile << "    ";
            }
         }
      }
      outFile << endl;
      // Print -
      outFile << "   ";
      for (int i = 0; i <= size; i++)
      {
         //check if even number
         if (i % 2 == 0)
         {
            outFile << "-----";
         }
      }
      if (size % 2 == 0)
      {
         outFile << "-";
      }
      else
      {
         outFile << "----";
      }
      outFile << endl;

      for (int i = 0; i <= size; i++)
      {
         // print Alphabets
         outFile << (char)('A' + i) << "  ";
         if (i % 2 == 0)
         {
            // Measure line
            outFile << "|";
            for (int j = 0; j <= size; j++)
            {
               if (j % 2 == 0)
               {
                  if (board.getTile(i, j)->getShape() != -1)
                  {
                     outFile << " ";

                     // Obtain tile colour and shape
                     outFile << board.getTile(i, j)->getColour() << board.getTile(i, j)->getShape() << " |";
                  }
                  else
                  {
                     outFile << "  "
                             << "  |";
                  }
               }
            }
         }
         else if (i % 2 == 1)
         {
            outFile << "   |";
            for (int j = 0; j <= size; j++)
            {
               if (j % 2 == 1)
               {
                  if (board.getTile(i, j)->getShape() != -1)
                  {
                     outFile << " ";

                     // Obtain colour and shapes
                     outFile << board.getTile(i, j)->getColour() << board.getTile(i, j)->getShape() << " |";
                  }
                  else
                  {
                     outFile << "  "
                             << "  |";
                  }
               }
            }
         }
         outFile << endl;
      }

      // Print -
      outFile << "   --";
      for (int i = 0; i <= size; i++)
      {
         //check if odd number
         if (i % 2 == 1)
         {
            outFile << "-----";
         }
      }
      if (size % 2 == 0)
      {
         outFile << "----";
      }
      else
      {
         outFile << "--";
      }
      outFile << endl;

      outFile << "        ";
      for (int i = 0; i <= size; i++)
      {
         //check if odd number
         if (i % 2 == 1)
         {
            outFile << i;
            if (i >= 10)
            {
               //one less space
               outFile << "   ";
            }
            else
            {
               outFile << "    ";
            }
         }
      }
      outFile << endl;

      //save tilebag
      outFile << tileBag->toString(false);

      //save currentplayers name
      outFile << players.at(currentPlayer)->getName() << endl;

      cout << "Succesfully saved game. '" << filename << "'\n\n> ";
   }
   else {
      cout << endl
         << "Goodbye." << endl;
      exit(0);
   }
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
   cout << "Student ID: s3666603" << endl;
   cout << "Email: s3666603@student.rmit.edu.au \n"
        << endl;

   cout << "Name: Tharvind Kalaiarasan" << endl;
   cout << "Student ID: s3654959" << endl;
   cout << "Email: s3654959@student.rmit.edu.au \n"
             << endl;

   cout << "Name: Thien Nguyen" << endl;
   cout << "Student ID: s3714217" << endl;
   cout << "Email: s3714217@student.rmit.edu.au" << endl;
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
   cout << "'save' eg: save" << endl
   << "          'filename'\n";
   cout << "'done' Finish Game\n";
   cout << "'Ctrl+D' Exit Immediately\n";
   cout << endl;

}


// Displaying all players score
void Qwirkle::displayPlayersScore()
{
    for (int playerNum = 0; playerNum < maxPlayers; ++playerNum)
    {
        std::cout << "Score for " << players[playerNum]->getName() << ": " << players[playerNum]->getScore() << std::endl;
    }
}

//checks to see if the playersHand is empty to end the game
bool Qwirkle::playersHandEmpty()
{
    bool isEmpty = false;
    for (int i = 0; i < maxPlayers; i++)
    {
        if (players[i]->getDeck()->size() == 0)
        {
            isEmpty = true;
        }
    }
    return isEmpty;
}

//returns the winning player after the game is over
Player *Qwirkle::getWinningPlayer()
{
    int highestScore = 0;
    Player *winningPlayer;
    for (int i = 0; i < maxPlayers; i++)
    {
        if (players[i]->getScore() > highestScore)
        {
            highestScore = players[i]->getScore();
            winningPlayer = players[i];
        }
    }
    return winningPlayer;
}
