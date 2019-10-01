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
        //point to new head node
        head = newNode;
    }
}

void LinkedList::removeFirst()
{
    Node* temp = head;
    head = head->next;
    delete temp;
}

Tile* LinkedList::removeTile(Tile* tile)
{
    Tile* tempTile = nullptr;

    if (head->next->tile == tile) {
        tempTile = head->next->tile;
        head->next = head->next->next;
        return tempTile;
    }

    Node* temp = head;

    while (temp->next != nullptr && temp->next->next != nullptr) {
        if (temp->next->next->tile == tile) {
            tempTile = temp->next->next->tile;
            temp->next->next = temp->next->next->next;
        }
        temp = temp->next;
    }
    return tempTile;
}

Tile* LinkedList::getTile(Colour c)
{
    Node* temp = head;
    while (temp->next)
    {
        if(temp->tile->getColour == c){
            return new Tile(temp->tile->getColour(),temp->tile->getShape());
        }
        temp = temp->next;
    }
    return nullptr;
}


bool LinkedList::find(Colour color)
{
    bool found = false;
    Node* temp = head;
    while (temp->next)
    {
        if(temp->tile->getColour() == color){
            return found = true;
        }
        temp = temp->next;
    }
    return found;
}

void LinkedList::replace(Tile* oldTile, Tile* newTile)
{
    Node* temp = head;
    while (temp->next != nullptr)
    {
        if(temp->next->tile == oldTile){
            temp->next->tile->setColour(newTile->getColour());
            temp->next->tile->setShape(newTile->getShape());
            return;
        }
        temp = temp->next;
    }
}


void LinkedList::clear()
{
    Node * temp = head->next;
    while(temp != nullptr){
        Node* next = temp->next;
        temp = nullptr;
        delete temp;
        temp = next;
    }
    head = nullptr;
}