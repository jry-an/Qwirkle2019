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

void LinkedList::removeTile(Tile* tile)
{
    Node* temp = head;

    // base case (check if head is tile to be removed)
    if (head->tile->isEqual(tile)) {
        head = head->next;
        length--;
        return;
    }

    // check for all other
    while (temp->next != nullptr) {
        if (temp->next->tile->isEqual(tile)) {
            temp->next = temp->next->next;
            length--;
            return;
        }
        temp = temp->next;
    }
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

void LinkedList::replace(Tile* _old, Tile* _new)
{
    Node* temp = head;
    if (temp->tile!=nullptr){
        while (temp->next) {
            if (temp->tile->isEqual(_old)) {
                removeTile(_old);
                addLast(_new);
                return;
            }
            temp = temp->next;
        }
        if (temp->tile->isEqual(_old)) {
            removeTile(_old);
            addLast(_new);
        }
    }
}


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

bool LinkedList::Empty() {
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
    srand(time(0));
    int random = rand() % nodes.size(); 
    for (int i=0; i<random; i++) {
        std::random_shuffle(nodes.begin(), nodes.end());
    }
    
    node = head->next;
    for (size_t i = 0; i < nodes.size(); i++) {
        node->tile = new Tile(nodes[i]->getColour(), nodes[i]->getShape());
        node = node->next;
    }
}

int getRand(int i) {
    return std::rand()%i;
}

std::string LinkedList::toString(bool is_console)
{
    std::map<Colour, std::string> color_map;
    color_map[RED] = "\033[31m";
    color_map[ORANGE] = "\033[91m";
    color_map[GREEN] = "\033[32m";
    color_map[BLUE] = "\033[34m";
    color_map[YELLOW] = "\033[33m";
    color_map[PURPLE] = "\033[35m";
    color_map[' '] = "\033[37m";
    std::stringstream stream;

    for (int i=0; i<length; i++) {
        if (!is_console)
            stream << this->get(i)->getColour() << this->get(i)->getShape();
        else
            stream << color_map[this->get(i)->getColour()] << this->get(i)->getColour() << this->get(i)->getShape() << color_map[' '];
        if (i+1!=length)
            stream << ",";
    }
    stream << "\n";
    return stream.str();
}