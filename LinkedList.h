
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <string>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <time.h>

class LinkedList {

public:
    LinkedList();
    ~LinkedList();

    int size();
    void addLast(Tile* tile);
    void addFirst(Tile* tile);
    Tile* removeFirst();
    void removeTile(Tile* tile);
    Tile* getTile(Colour c);
    Tile* get(int i);
    bool find(Colour);
    bool find(Shape);
    bool find(Tile* t);
    bool Empty();
    void replace(Tile* oldTile, Tile* newTile);
    void shuffle();
    void clear();
    std::string toString(bool is_console);

private:
    Node* head;
    int length;
};

#endif // ASSIGN2_LINKEDLIST_H