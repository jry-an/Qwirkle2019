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
    int length = 0;
    Node* temp = head;
    while (temp->next != nullptr)
    {
        length++;
        temp = temp->next;
    }
    return length;
    
}

void LinkedList::addLast(Tile* tile)
{
    Node* newNode = new Node(tile, nullptr);

    //check if head exists
    if (head == nullptr)
    {
        head = newNode;
        return;
    }
    Node* temp = head;

    //check if head is only node
    if(length() == 1){
        head->next = newNode;
    }
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = newNode;


}

void LinkedList::addFirst(Tile * tile) {
    Node *newNode = new Node(tile, nullptr);
    if(head == nullptr) {
        head = newNode;
    }
    else {
        newNode->next = head;
    }
}

Tile* LinkedList::removeFirst()
{

}

Tile* LinkedList::removeTile(Tile* tile)
{

}

Tile* LinkedList::getTile(Colour c)
{

}


bool LinkedList::find(Colour color)
{

}

void LinkedList::replace(Tile* oldTile, Tile* newTile)
{

}


void LinkedList::clear()
{

}