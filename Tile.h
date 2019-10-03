#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>
#include <iostream>

// Define a Colour type
typedef char Colour;
// Define a Shape type
typedef int Shape;

class Tile {

public:


public:
   Tile();
   Tile(Colour c, Shape s);
   bool isEmpty();
   bool isEqual(Tile*);
   Colour getColour();
   Shape getShape();
   std::string getTileCode();
   void setColour(Colour colour);
   void setShape(Shape s);



   private:
   Colour colour;
   Shape shape;
   std::string tileCode;
};

#endif // ASSIGN2_TILE_H