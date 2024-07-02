// Maayan1sher@gmail.com

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "board.hpp"
#include "card.hpp"
#include "tile.hpp"

using namespace std;

class Board;

class Player
{
    string name;
    unordered_set<int> settlements;
    unordered_set<int> roads;
    int points;
    int initialSettlementCount;
    int knightCount;
    vector<Card> developmentCards;
    unordered_map<Card::ResourceCard, int> resourceCards;

public:
    Player(const string name);
    int rollDice(Board &board, vector<shared_ptr<Player>> &players);
    string getName() const;
    bool placeInitialSettlement(Board &board, int tileIndex, int vertexId);
    bool placeInitialRoad(Board &board, int tileIndex, int edgeId);
    bool placeRoad(Board &board, int tileIndex, int edgeId);
    bool placeSettlement(Board &board, int tileIndex, int vertexId);
    bool placeCity(Board &board, int tileIndex, int vertexId);
    void recivePoint();
    int getPoints();

    // Development cards use methods

    void useRoadBuilding(Board &board);
    void useYearOfPlenty();
    void useMonopoly(vector<shared_ptr<Player>> &players);
    void useKnight();
    void useVictoryPoint();


    // Resource and Development card managment
    // Check if a player have the needed materials
    bool canAfford(const unordered_map<Card::ResourceCard, int> &cost) const;
    bool purchaseDevelopmentCard(Board &board, vector<shared_ptr<Player>> &players);
    // Add resource card to the player,with paramter Card or parametr ResourceType
    void addResourceCard(Card::ResourceCard resource);
    void addResourceCard(ResourceType resource);
    bool removeResourceCard(Card::ResourceCard resource);
    void addDevelopmentCard(const Card &card);
    Card drawDevelopmentCard();
    void listResources() const;

    // method to trade with other player to exchange 1 resource for 1 resource
    void tradeResource(Player &otherPlayer, Card::ResourceCard giveResource, Card::ResourceCard getResource);
};

#endif