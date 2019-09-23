#include "LinkedList.h"
#include "TileCodes.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include <map>

LinkedList::LinkedList()
{
    head = nullptr;
    head = new Node;
}

LinkedList::~LinkedList()
{
    this->clear();
}

int LinkedList::length()
{
    return 0;
}

void LinkedList::addLast(Tile* tile)
{

}

void LinkedList::addFirst(Tile * tile) {

}

Tile* LinkedList::removeFirst()
{
    return nullptr;
}

Tile* LinkedList::removeTile(Tile* tile)
{
    return nullptr;
}

Tile* LinkedList::getTile(Colour c)
{
    return nullptr;
}


bool LinkedList::find(Colour color)
{
 return 0;
}

void LinkedList::replace(Tile* oldTile, Tile* newTile)
{

}


void LinkedList::clear()
{

}