#include "Player.h"

Player::Player(std::string name)
{
    this->name = name;
    this->score = 0;
}

Player::Player()
{
    this->name = nullptr;
    this->score = 0;
}

Player::~Player()
{
}

int Player::getScore()
{
    return score;
}

void Player::setScore(int s)
{
    this->score += s;
}

std::string Player::getName()
{
    return name;
}

void Player::setName(std::string name)
{
    this->name = name;
}

LinkedList* Player::getDeck()
{
    return deck;
}

void Player::setDeck(LinkedList* d)
{
    this->deck = d;
}

void Player::replaceTile(Tile* oldTile, Tile* newTile) {
    this->deck->replace(oldTile, newTile);
}

void Player::placeTile(Tile* oldTile, Tile* newTile) {
    //TODO
}