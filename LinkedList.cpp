#include "LinkedList.h"
#include "TileCodes.h"

LinkedList::LinkedList()
{
    head = nullptr;
    length = 0;
}

LinkedList::~LinkedList()
{
    this->clear();
}

int LinkedList::size()
{
    return length;
}

void LinkedList::addLast(Tile* tile)
{
    Node* newNode = new Node(tile, nullptr);

    //check if head exists
    if (head == nullptr)
    {
        head = newNode;
    } else {
        Node* temp = head;
    
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;

    }

    length++;
}

Tile* LinkedList::get(int i) {
    int counter = 0;
    Node* node = head;

    //check if linked list empty
    if (head == nullptr) {
        return nullptr;
    }
    //check if bigger than linked list size
    if (i>=length) {
        return nullptr;
    }
    //base case
    if (i==0) {
        return head->tile;
    }
    //return Tile at position i    
    while (counter!=i) {
        node = node->next;
        counter++;
    }
    Tile* tile = node->tile;
    return tile;
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
    length++;
}

Tile* LinkedList::removeFirst()
{
    if (head == nullptr) {
        return nullptr;
    }
    Node* temp = head; 
    head = head->next;
  
    length--;
    return temp->tile;
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
        if(temp->tile->getColour() == c){
            return new Tile(temp->tile->getColour(),temp->tile->getShape());
        }
        temp = temp->next;
    }
    return nullptr;
}

bool LinkedList::find(Tile* t) {
    Node* tmp = head;
    //base case if head is the desired tile
    if (head->tile->isEqual(t)) {
        return true;
    }
    while (tmp->next != nullptr) {
        if (tmp->next->tile->isEqual(t)) {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

bool LinkedList::find(Colour color)
{
    bool found = false;
    if (head == nullptr) {
        return found;
    }
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

// void LinkedList::replace(Tile* _old, Tile* _new)
// {
//     Node* tmp = head;
//     if (tmp->next!=nullptr){
//         while (tmp->next) {
//             if (tmp->next->tile->is_equal(_old)) {
//                 tmp->next->tile->colour = _new->colour;
//                 tmp->next->tile->shape = _new->shape;
//                 return;
//             }
//             tmp = tmp->next;
//         }
//     }
// }


void LinkedList::clear()
{
    if (head != nullptr) {
        Node * temp = head->next;

        while(temp != nullptr){
            Node* next = temp->next;
            temp = nullptr;
            delete temp;
            temp = next;
        }
        head = nullptr;
    }    
}

bool LinkedList::isEmpty() {
    return (head == nullptr);
}

void LinkedList::shuffle()
{
    std::vector<Tile*> nodes;
    Node* node = head;
    while (node->next != nullptr) {
        nodes.push_back(node->next->tile);
        node = node->next;
    }
    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(nodes), std::end(nodes), rng);
    node = head->next;
    for (size_t i = 0; i < nodes.size(); i++) {
        node->tile = new Tile(nodes[i]->getColour(), nodes[i]->getShape());
        node = node->next;
    }
}