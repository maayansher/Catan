//Maayan1sher@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#ifndef BOARD_HPP
#define BOARD_HPP

#include <memory>
#include <vector>
#include "player.hpp"

using namespace std;

class Tile;
class Edge;
class Vertex;
class Player;
enum class ResourceType;


class Board
{
    vector<shared_ptr<Tile>> tiles;
    void initializeBoard();
    void linkTiles();

public:
    Board();
    void printBoard();
    string resourceToString(ResourceType type);
    shared_ptr<Edge> createEdge(int id);
    shared_ptr<Vertex> createVertex(int id);
    shared_ptr<Vertex> getVertex(int id) const;
    shared_ptr<Edge> getEdge(int id) const;
    shared_ptr<Tile> getTile(int tileIndex) const;
    vector<shared_ptr<Tile>> getTiles()const;
    int getVertexId(int tileIndex, int vertexPosition) const;
    int getEdgeId(int tileIndex, int edgePosition) const;
    // void checkAdjacent(int tileIndex, int vertexId);

    // a method to check the adjacent tile of specific vertex
    vector<shared_ptr<Tile>> getAdjacentTiles(int vertexId)const;
    void distributeResources(int diceRoll, vector<shared_ptr<Player>> &players);
};

#endif