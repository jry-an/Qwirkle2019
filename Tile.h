
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>

// Define a Colour type
typedef char Colour;
// Define a Shape type
typedef int Shape;

class Tile {
private:
   Colour colour;
   Shape shape;
   std::string tileCode;

public:
   Tile();
   Tile(Colour c, Shape s);
   bool isEmpty();
   bool isEqual(Tile*);
   std::string getTileCode();
};

#endif // ASSIGN2_TILE_H