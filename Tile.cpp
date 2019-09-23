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
    return (this->colour == 'W' && this->shape == -1);
}

bool Tile::isEqual(Tile* t)
{
    return (t->colour == this->colour && t->shape == this->shape);
}

std::string Tile::getTileCode() 
{
    return tileCode;
}