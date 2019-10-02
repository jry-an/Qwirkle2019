
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <string>

class LinkedList {

public:
    LinkedList();
    ~LinkedList();

    int size();
    std::string toString(bool);
    int length();
    void addLast(Tile* tile);
    void addFirst(Tile* tile);
    Tile* removeFirst();
    Tile* removeTile(Tile* tile);
    Tile* getTile(Colour c);
    Tile* getTileByIndex(int i);
    bool find(Colour);
    bool isEmpty();
    void replace(Tile* oldTile, Tile* newTile);
    void shuffle();
    void clear();
    void print();

private:
    Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H