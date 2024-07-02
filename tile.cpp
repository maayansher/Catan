//Maayan1sher@gmail.com

#include "tile.hpp"

Tile::Tile(ResourceType resouce, int num) : resource(resouce), num(num) {}

ResourceType Tile::getResource() const
{
    return this->resource;
}

int Tile::getNum() const
{
    return this->num;
}
void const Tile::setIndex(int index)
{
    this->index = index;
}

int Tile::getIndex() const
{
    return this->index;
}