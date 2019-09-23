
#include "Qwirkle.h"
#include <fstream>
#include <map>
#include <sstream>

Qwirkle::Qwirkle()
{
   tileBag = new LinkedList();
}

Qwirkle::~Qwirkle()
{
   delete tileBag;
}

void Qwirkle::start()
{
   int input = 0;

   // While the user is playing the game - print the menu
   // and get the input for
   while (input != QUIT)
   {
      //print menu
      printMenu();

      //get input from user
      std::cin >> input;
      std::cout << std::endl;

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
    std::cout << "Menu" << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Show student information" << std::endl;
    std::cout << "4. Help!" << std::endl;
    std::cout << "5. Quit" << std::endl;
}

void Qwirkle::newGame()
{

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
    std::cout << "Email: sXXXXXXX@student.rmit.edu.au" << std::endl;
    std::cout << "-------------------------------- \n"
              << std::endl;

    std::cout << "Name: Tharvind Kalaiarasan" << std::endl;
    std::cout << "Student ID: sXXXXXXX" << std::endl;
    std::cout << "Email: sXXXXXXX@student.rmit.edu.au" << std::endl;
    std::cout << "-------------------------------- \n"
              << std::endl;

}

void Qwirkle::helpMenu()
{

}
