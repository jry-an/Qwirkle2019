#ifndef ASSIGN2_PLAY_H
#define ASSIGN2_PLAY_H

#include <iostream>
#include <string>
#include <vector>

#include "LinkedList.h"
#include "Tile.h"

class Player {

public:
    Player(std::string name);
    Player();
    ~Player();

    int getScore();
    void setScore(int s);
    std::string getName();
    LinkedList* getDeck();
    void setDeck(LinkedList* d);
    void setName(std::string name);

private:
    int score;
    std::string name;
    LinkedList* deck;
};

#endif