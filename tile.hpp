//Maayan1sher@gmail.com

#ifndef TILE_HPP
#define TILE_HPP

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include "player.hpp"

using namespace std;

enum class ResourceType
{
    Brick,
    Wood,
    Sheep,
    Wheat,
    Ore,
    Desert
};

struct Edge
{
    int id;
    bool taken;
    string takenBy;

    Edge(int id) : id(id), taken(false) {}
};

struct Vertex
{
    int id;
    bool taken;
    bool hasCity;
    string takenBy;


    Vertex(int id) : id(id), taken(false) , hasCity(false) {}
};

class Tile
{
    ResourceType resource;
    int num;   // The number on the tile
    int index; // The place where the tile appears

public:
    Tile(ResourceType resource, int num);
    ResourceType getResource() const;
    int getNum() const;
    int getIndex() const;
    void const setIndex(int index);

    // Shared edges and vertices
    vector<shared_ptr<Edge>> edges;
    vector<shared_ptr<Vertex>> vertcies;
};

#endif