#include "Player.h"

Player::Player()
{
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