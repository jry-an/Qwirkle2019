#include <iostream>

#include "Tile.h"

Tile::Tile()
{
    this->colour = ' ';
    this->shape = -1;
    this->tileCode += colour;
    this->tileCode += " ";
}

Tile::Tile(Colour colour, Shape shape)
{
    this->colour = colour;
    this->shape = shape;
    this->tileCode = colour + shape;
}

bool Tile::isEmpty()
{
    return (this->colour == ' ' && this->shape == -1);
}

bool Tile::isEqual(Tile* t)
{
    return (t->colour == this->colour && t->shape == this->shape);
}

Colour Tile::getColour(){
    return colour;
}

void Tile::setColour(Colour colour){

}

Shape Tile::getShape(){
    return shape;
}

void Tile::setShape(Shape s){
    shape = s;
}

 std::string Tile::getTileCode(){
     return tileCode;
 }
