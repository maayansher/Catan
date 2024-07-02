//Maayan1sher@gmail.com

#include <iostream>
#include <string>
#include <iomanip>
#include "tile.hpp"
#include "board.hpp"

using namespace std;

Board::Board()
{
    initializeBoard();
    Card::initializeDevelopmentDeck();
}

void Board::initializeBoard()
{
    const vector<pair<ResourceType, int>> tileConfigs = {
        {ResourceType::Ore, 6},
        {ResourceType::Sheep, 5},
        {ResourceType::Ore, 9}, // Top row (3 tiles)
        {ResourceType::Wheat, 4},
        {ResourceType::Ore, 3},
        {ResourceType::Wheat, 8},
        {ResourceType::Brick, 10}, // Second row (4 tiles)
        {ResourceType::Sheep, 6},
        {ResourceType::Wood, 5},
        {ResourceType::Desert, -1},
        {ResourceType::Wood, 9},
        {ResourceType::Wood, 12}, // Third row (5 tiles)
        {ResourceType::Wheat, 3},
        {ResourceType::Brick, 2},
        {ResourceType::Wheat, 10},
        {ResourceType::Brick, 11}, // Fourth row (4 tiles)
        {ResourceType::Sheep, 11},
        {ResourceType::Wood, 4},
        {ResourceType::Sheep, 8} // Bottom row (3 tiles)
    };

    int edgeCounter = 0;
    int vertexCounter = 0;
    int tileIndex = 0;

    for (const auto &config : tileConfigs)
    {
        auto tile = make_shared<Tile>(config.first, config.second);
        tile->setIndex(tileIndex);
        tileIndex++;

        for (int i = 0; i < 6; ++i)
        {
            tile->edges.push_back(createEdge(edgeCounter++));
        }

        for (int i = 0; i < 6; ++i)
        {
            auto vertex = createVertex(vertexCounter++);
            tile->vertcies.push_back(vertex);
        }

        tiles.push_back(tile);
    }
    /**
     * Manually link the shared edges and verices between adjacent tiles
     * this will ensure that tiles share the same edges/vertices where they meet
     * */

    linkTiles();
}
vector<shared_ptr<Tile>> Board::getTiles() const
{
    return tiles;
}

shared_ptr<Edge> Board::getEdge(int id) const
{
    for (const auto &tile : tiles)
    {
        for (const auto &edge : tile->edges)
        {
            if (edge->id == id)
            {
                return edge;
            }
        }
    }
    return nullptr;
}

shared_ptr<Vertex> Board::getVertex(int id) const
{
    for (const auto &tile : tiles)
    {
        for (const auto &vertex : tile->vertcies)
        {
            if (vertex->id == id)
            {
                return vertex;
            }
        }
    }
    cout << "vertex " << id << "not found " << endl;
    return nullptr;
}

shared_ptr<Edge> Board::createEdge(int id)
{
    return make_shared<Edge>(id);
}

shared_ptr<Vertex> Board::createVertex(int id)
{
    return make_shared<Vertex>(id);
}

void Board::linkTiles()
{ // Tile 0
    tiles[0]->edges[1] = tiles[1]->edges[4];
    tiles[0]->edges[2] = tiles[4]->edges[5];
    tiles[0]->edges[3] = tiles[3]->edges[0];

    // Tile 1
    tiles[1]->edges[1] = tiles[2]->edges[4];
    tiles[1]->edges[2] = tiles[5]->edges[5];
    tiles[1]->edges[3] = tiles[4]->edges[0];

    // Tile 2
    tiles[2]->edges[2] = tiles[6]->edges[5];
    tiles[2]->edges[3] = tiles[5]->edges[0];

    // Tile 3
    tiles[3]->edges[1] = tiles[4]->edges[4];
    tiles[3]->edges[2] = tiles[8]->edges[5];
    tiles[3]->edges[3] = tiles[7]->edges[0];

    // Tile 4
    tiles[4]->edges[1] = tiles[5]->edges[4];
    tiles[4]->edges[2] = tiles[9]->edges[5];
    tiles[4]->edges[3] = tiles[8]->edges[0];

    // Tile 5
    tiles[5]->edges[1] = tiles[6]->edges[4];
    tiles[5]->edges[2] = tiles[10]->edges[5];
    tiles[5]->edges[3] = tiles[9]->edges[0];

    // Tile 6
    tiles[6]->edges[2] = tiles[11]->edges[5];
    tiles[6]->edges[3] = tiles[10]->edges[0];

    // Tile 7
    tiles[7]->edges[1] = tiles[8]->edges[4];
    tiles[7]->edges[2] = tiles[12]->edges[5];

    // Tile 8
    tiles[8]->edges[1] = tiles[9]->edges[4];
    tiles[8]->edges[2] = tiles[13]->edges[5];
    tiles[8]->edges[3] = tiles[12]->edges[0];

    // Tile 9
    tiles[9]->edges[1] = tiles[10]->edges[4];
    tiles[9]->edges[2] = tiles[14]->edges[5];
    tiles[9]->edges[3] = tiles[13]->edges[0];

    // Tile 10
    tiles[10]->edges[1] = tiles[11]->edges[4];
    tiles[10]->edges[2] = tiles[15]->edges[5];
    tiles[10]->edges[3] = tiles[14]->edges[0];

    // Tile 11
    tiles[11]->edges[3] = tiles[15]->edges[0];

    // Tile 12
    tiles[12]->edges[1] = tiles[13]->edges[4];
    tiles[12]->edges[2] = tiles[16]->edges[5];

    // Tile 13
    tiles[13]->edges[1] = tiles[14]->edges[4];
    tiles[13]->edges[2] = tiles[17]->edges[5];
    tiles[13]->edges[3] = tiles[16]->edges[0];

    // Tile 14
    tiles[14]->edges[1] = tiles[15]->edges[4];
    tiles[14]->edges[2] = tiles[18]->edges[5];
    tiles[14]->edges[3] = tiles[17]->edges[0];

    // Tile 15
    tiles[15]->edges[3] = tiles[18]->edges[0];

    // Tile 16
    tiles[16]->edges[1] = tiles[17]->edges[4];

    // Tile 17
    tiles[17]->edges[1] = tiles[18]->edges[4];

    // Linking vertcies

    tiles[0]->vertcies[1] = tiles[1]->vertcies[5];
    tiles[0]->vertcies[2] = tiles[4]->vertcies[0];
    tiles[0]->vertcies[3] = tiles[4]->vertcies[5];
    tiles[0]->vertcies[4] = tiles[3]->vertcies[0];
    tiles[1]->vertcies[1] = tiles[2]->vertcies[5];
    tiles[1]->vertcies[2] = tiles[5]->vertcies[0];
    tiles[1]->vertcies[3] = tiles[5]->vertcies[5];
    tiles[1]->vertcies[4] = tiles[4]->vertcies[0];
    tiles[2]->vertcies[2] = tiles[6]->vertcies[0];
    tiles[2]->vertcies[3] = tiles[6]->vertcies[5];
    tiles[2]->vertcies[4] = tiles[5]->vertcies[0];
    tiles[3]->vertcies[1] = tiles[4]->vertcies[5];
    tiles[3]->vertcies[2] = tiles[8]->vertcies[0];
    tiles[3]->vertcies[3] = tiles[8]->vertcies[5];
    tiles[3]->vertcies[4] = tiles[7]->vertcies[0];
    tiles[4]->vertcies[1] = tiles[5]->vertcies[5];
    tiles[4]->vertcies[2] = tiles[9]->vertcies[0];
    tiles[4]->vertcies[3] = tiles[9]->vertcies[5];
    tiles[4]->vertcies[4] = tiles[8]->vertcies[0];
    tiles[5]->vertcies[1] = tiles[6]->vertcies[5];
    tiles[5]->vertcies[2] = tiles[10]->vertcies[0];
    tiles[5]->vertcies[3] = tiles[10]->vertcies[5];
    tiles[5]->vertcies[4] = tiles[9]->vertcies[0];
    tiles[6]->vertcies[2] = tiles[11]->vertcies[0];
    tiles[6]->vertcies[3] = tiles[11]->vertcies[5];
    tiles[6]->vertcies[4] = tiles[10]->vertcies[0];
    tiles[7]->vertcies[1] = tiles[8]->vertcies[5];
    tiles[7]->vertcies[2] = tiles[12]->vertcies[0];
    tiles[7]->vertcies[3] = tiles[12]->vertcies[5];
    tiles[8]->vertcies[1] = tiles[9]->vertcies[5];
    tiles[8]->vertcies[2] = tiles[13]->vertcies[0];
    tiles[8]->vertcies[3] = tiles[13]->vertcies[5];
    tiles[8]->vertcies[4] = tiles[12]->vertcies[0];
    tiles[9]->vertcies[1] = tiles[10]->vertcies[5];
    tiles[9]->vertcies[2] = tiles[14]->vertcies[0];
    tiles[9]->vertcies[3] = tiles[14]->vertcies[5];
    tiles[9]->vertcies[4] = tiles[13]->vertcies[0];
    tiles[10]->vertcies[1] = tiles[11]->vertcies[5];
    tiles[10]->vertcies[2] = tiles[15]->vertcies[0];
    tiles[10]->vertcies[3] = tiles[15]->vertcies[5];
    tiles[10]->vertcies[4] = tiles[14]->vertcies[0];
    tiles[11]->vertcies[3] = tiles[15]->vertcies[1];
    tiles[11]->vertcies[4] = tiles[15]->vertcies[0];
    tiles[12]->vertcies[1] = tiles[13]->vertcies[5];
    tiles[12]->vertcies[2] = tiles[16]->vertcies[0];
    tiles[12]->vertcies[3] = tiles[16]->vertcies[5];
    tiles[13]->vertcies[1] = tiles[14]->vertcies[5];
    tiles[13]->vertcies[2] = tiles[17]->vertcies[0];
    tiles[13]->vertcies[3] = tiles[17]->vertcies[5];
    tiles[13]->vertcies[4] = tiles[16]->vertcies[0];
    tiles[14]->vertcies[1] = tiles[15]->vertcies[5];
    tiles[14]->vertcies[2] = tiles[18]->vertcies[0];
    tiles[14]->vertcies[3] = tiles[18]->vertcies[5];
    tiles[14]->vertcies[4] = tiles[17]->vertcies[0];
    tiles[15]->vertcies[3] = tiles[18]->vertcies[1];
    tiles[15]->vertcies[4] = tiles[18]->vertcies[0];
    tiles[16]->vertcies[1] = tiles[17]->vertcies[5];
    tiles[16]->vertcies[2] = tiles[17]->vertcies[4];
    tiles[17]->vertcies[1] = tiles[18]->vertcies[5];
    tiles[17]->vertcies[2] = tiles[18]->vertcies[4];

    // for (const auto &tile : tiles)
    // {
    //     cout << "Tile " << tile->getIndex() << " has linked vertices: ";
    //     for (const auto &vertex : tile->vertcies)
    //     {
    //         cout << vertex->id << " ";
    //     }
    //     cout << endl;
    // }

    // cout << "board as been created" << endl;
}

string Board::resourceToString(ResourceType type)
{
    {
        switch (type)
        {
        case ResourceType::Ore:
            return "Ore";
        case ResourceType::Wood:
            return "Wood";
        case ResourceType::Brick:
            return "Brick";
        case ResourceType::Wheat:
            return "Wheat";
        case ResourceType::Desert:
            return "Desert";
        case ResourceType::Sheep:
            return "Sheep";
        default:
            return "Unkown";
        }
    }
}

void Board::printBoard()
{
    vector<vector<int>> rows = {{0, 1, 2}, {3, 4, 5, 6}, {7, 8, 9, 10, 11}, {12, 13, 14, 15}, {16, 17, 18}};
    vector<string> indentations = {
        "                ",
        "       ",
        "  ",
        "       ",
        "                "};

    for (unsigned int i = 0; i < rows.size(); ++i)
    {
        cout << indentations[i];
        for (unsigned int j = 0; j < rows[i].size(); ++j)
        {
            auto tileIndex = static_cast<vector<shared_ptr<Tile>>::size_type>(rows[i][j]);
            string resource = resourceToString(tiles[tileIndex]->getResource());
            int number = tiles[tileIndex]->getNum();
            cout << setw(15) << resource << "(" << number << ")";
            if (j < rows[i].size() - 1)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}

// void Board::checkAdjacent(int tileIndex, int vertexId)
// {
//     auto tile = tiles[static_cast<size_t>(tileIndex)];
//     auto vertex = tile->vertcies[static_cast<size_t>(vertexId)];

//     cout << "Checking adjacent vertices for tile " << tileIndex << ", Vertex " << vertexId << " ID: " << vertex->id << endl;

//     int prevVertexIndex = (vertexId == 0) ? 5 : vertexId - 1;
//     int nextVertexIndex = (vertexId == 5) ? 0 : vertexId + 1;

//     auto prevVertex = tile->vertcies[static_cast<size_t>(prevVertexIndex)];
//     auto nextVertex = tile->vertcies[static_cast<size_t>(nextVertexIndex)];

//     if (prevVertex->taken || nextVertex->taken)
//     {
//         cout << "Cannot place settlement on this vertex since one of their neighbors is taken" << endl;
//         return;
//     }
//     // Now after we checked the neighbors vertices of the same tile we procced to check the vertex on the neihber tile
// }

vector<shared_ptr<Tile>> Board::getAdjacentTiles(int vertexId) const
{
    vector<shared_ptr<Tile>> adjacentTiles;
    for (const auto &tile : tiles)
    {
        for (const auto &vertex : tile->vertcies)
        {
            if (vertex->id == vertexId)
            {
                adjacentTiles.push_back(tile);
                break;
            }
        }
    }
    return adjacentTiles;
}

// Method to get tile by index
shared_ptr<Tile> Board::getTile(int tileIndex) const
{
    // Check if the index is valid
    if (tileIndex >= 0 && static_cast<size_t>(tileIndex) < tiles.size())
    {
        return tiles[static_cast<size_t>(tileIndex)];
    }
    else
    {
        return nullptr; // Return nullptr if index is out of range
    }
}



int Board::getVertexId(int tileIndex, int vertexPosition) const
{
    auto tile = getTile(tileIndex);
    if (!tile)
    {
        return -1;
    }

    if (vertexPosition < 0 || vertexPosition > 6)
    {
        return -1;
    }

    return tile->vertcies[static_cast<size_t>(vertexPosition)]->id;
}

int Board::getEdgeId(int tileIndex, int edgePosition) const
{
    auto tile = getTile(tileIndex);
    if (!tile)
    {
        return -1;
    }

    if (edgePosition < 0 || edgePosition > 6)
    {
        return -1;
    }

    return tile->edges[static_cast<size_t>(edgePosition)]->id;
}

void Board::distributeResources(int diceRoll, vector<shared_ptr<Player>> &players)
{
    for (const auto &tile : tiles)
    {
        if (tile->getNum() == diceRoll)
        {
            for (const auto &vertex : tile->vertcies)
            {
                if (vertex->taken)
                {
                    for (auto &player : players)
                    {
                        if (player->getName() == vertex->takenBy)
                        {
                            player->addResourceCard(tile->getResource());
                            cout << player->getName() << " Recived " << resourceToString(tile->getResource()) << endl;

                            if(vertex->hasCity){
                                player->addResourceCard(tile->getResource());
                            }
                        }
                    }
                }
            }
        }
    }
}