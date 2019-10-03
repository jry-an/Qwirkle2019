
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include <map>

class LinkedList {

public:
    LinkedList();
    ~LinkedList();

    int size();
    std::string toString(bool);
    void addLast(Tile* tile);
    void addFirst(Tile* tile);
    Tile* removeFirst();
    Tile* removeTile(Tile* tile);
    Tile* getTile(Colour c);
    Tile* get(int i);
    bool find(Colour);
    bool find(Shape);
    bool find(Tile* t);
    bool isEmpty();
    void replace(Tile* oldTile, Tile* newTile);
    void shuffle();
    void clear();

private:
    Node* head;
    int length;
};

#endif // ASSIGN2_LINKEDLIST_H