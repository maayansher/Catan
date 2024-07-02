// Maayan1sher@gmail.com

#include "player.hpp"
#include "board.hpp"
#include "tile.hpp"

using namespace std;

Player::Player(string name)
{
    this->name = name;
    points = 0;
    initialSettlementCount = 0;
    knightCount = 0;
};

string Player::getName() const
{
    return this->name;
}

int Player::rollDice(Board &board, vector<shared_ptr<Player>> &players)
{

    int result = (rand() % 11) + 2;
    cout << this->name << " rolled " << result << endl;
    board.distributeResources(result, players);
    return result;
}

bool Player::canAfford(const unordered_map<Card::ResourceCard, int> &cost) const
{
    for (auto i = cost.begin(); i != cost.end(); ++i)
    {
        if (resourceCards.find(i->first) == resourceCards.end() || resourceCards.at(i->first) < i->second)
        {
            cout << "cannot afford" << endl;
            return false;
        }
    }
    return true;
}

bool Player::placeInitialSettlement(Board &board, int tileIndex, int vertexPosition)
{
    int vertexId = board.getVertexId(tileIndex, vertexPosition);
    if (vertexId == -1)
    {
        cout << "invalid tile index or vertex position" << endl;
        return false;
    }
    auto vertex = board.getVertex(vertexId);
    if (!vertex)
    {
        cout << "Vertex " << vertexId << " on Tile " << tileIndex << " doesn't exist" << endl;
        return false;
    }

    if (vertex->taken)
    {
        cout << "Vertex " << vertexId << " on Tile " << tileIndex << " is already taken" << endl;
        return false;
    }

    vertex->taken = true;
    vertex->takenBy = name;
    settlements.insert(vertexId);
    recivePoint();
    initialSettlementCount++;
    // after the player placed 2 initial settlements he gets the resources he stands on
    if (initialSettlementCount <= 2)
    {
        vector<shared_ptr<Tile>> adjacentTiles = board.getAdjacentTiles(vertexId);
        for (const auto &tile : adjacentTiles)
        {
            if (tile->getResource() != ResourceType::Desert)
            {
                addResourceCard(tile->getResource());
            }
        }
    }
    cout << name << " placed an initial settlement on Tile " << tileIndex << ", Vertex " << vertexId << endl;
    return true;
}

bool Player::placeInitialRoad(Board &board, int tileIndex, int edgePosition)
{
    int edgeId = board.getEdgeId(tileIndex, edgePosition);
    if (!edgeId)
    {
        cout << "invalid tile index or edge position" << endl;
        return false;
    }
    auto edge = board.getEdge(edgeId);
    if (edge->taken)
    {
        cout << "Edge " << edgeId << " is already taken" << endl;
        return false;
    }
    // Check if theres a road connected to this edge
    bool connectedToRoad = false;
    int previousEdgePosition = (edgePosition == 0) ? 5 : edgePosition - 1;
    int nextEdgePosition = (edgePosition == 5) ? 0 : edgePosition + 1;
    int previousEdgeId = board.getEdgeId(tileIndex, previousEdgePosition);
    int nextEdgeId = board.getEdgeId(tileIndex, nextEdgePosition);

    if (roads.find(previousEdgeId) != roads.end() || roads.find(nextEdgeId) != roads.end())
    {
        connectedToRoad = true;
    }
    // Before placing a road, we check if theres settelemnt so we can place a road from there
    int nextVertex = (edgePosition == 5) ? 0 : edgePosition++;
    int currentVertex = edgePosition;
    auto vertex1 = board.getVertex(board.getVertexId(tileIndex, currentVertex));
    auto vertex2 = board.getVertex(board.getVertexId(tileIndex, nextVertex));

    if (!connectedToRoad && (!vertex1->taken || vertex1->takenBy != name) && (!vertex2->taken || vertex2->takenBy != name))
    {
        cout << "Cannot place road on edge " << edgeId << " on Tile " << tileIndex << " because there is no connecting road or settlement owned by the player." << endl;
        return false;
    }

    edge->taken = true;
    edge->takenBy = name;
    roads.insert(edgeId);
    cout << name << " placed a road on edge " << endl;
    return true;
}

bool Player::placeSettlement(Board &board, int tileIndex, int vertexPosition)
{
    unordered_map<Card::ResourceCard, int> settlementCost = {
        {Card::ResourceCard::Wheat, 1},
        {Card::ResourceCard::Sheep, 1},
        {Card::ResourceCard::Wood, 1},
        {Card::ResourceCard::Brick, 1},
    };
    if (!canAfford(settlementCost))
    {
        cout << "Not enough resources to build a settlement " << endl;
        return false;
    }

    if (placeInitialSettlement(board, tileIndex, vertexPosition))
    {
        for (auto i = settlementCost.begin(); i != settlementCost.end(); ++i)
        {
            resourceCards[i->first] -= i->second;
        }
        cout << "settelment created " << endl;
    }
    return true;
}

bool Player::placeRoad(Board &board, int tileIndex, int edgePosition)
{
    unordered_map<Card::ResourceCard, int> roadCost = {
        {Card::ResourceCard::Wood, 1},
        {Card::ResourceCard::Brick, 1}};
    if (!canAfford(roadCost))
    {
        cout << "Not enough resources to build a road " << endl;
        return false;
    }
    if (placeInitialRoad(board, tileIndex, edgePosition))
    {
        for (auto i = roadCost.begin(); i != roadCost.end(); ++i)
        {
            resourceCards[i->first] -= i->second;
        }
        return true;
    }
    return false;
}

bool Player::placeCity(Board &board, int tileIndex, int vertexPosition)
{
    unordered_map<Card::ResourceCard, int> cityCost = {
        {Card::ResourceCard::Ore, 3},
        {Card::ResourceCard::Wheat, 2}};

    if (!canAfford(cityCost))
    {
        cout << "Not enough resources to build a city " << endl;
        return false;
    }

    int vertexId = board.getVertexId(tileIndex, vertexPosition);
    if (vertexId == -1)
    {
        cout << "invalid tile index or vertex position" << endl;
        return false;
    }
    auto vertex = board.getVertex(vertexId);

    if (vertex->takenBy != name || !vertex->taken)
    {
        cout << "Cannot build city here, that vertex is empty or someone else settelement" << endl;
        return false;
    }

    if (vertex->hasCity)
    {
        cout << "Vertex already has a city" << endl;
        return false;
    }
    // Make the payment
    for (auto i = cityCost.begin(); i != cityCost.end(); ++i)
    {
        resourceCards[i->first] -= i->second;
    }
    vertex->hasCity = true;
    recivePoint();

    cout << name << " Upgraded the settelement to city " << endl;
    return true;
}

bool Player::purchaseDevelopmentCard(Board &board, vector<shared_ptr<Player>> &players)
{
    unordered_map<Card::ResourceCard, int> developmentCardCost = {
        {Card::ResourceCard::Wheat, 1},
        {Card::ResourceCard::Sheep, 1},
        {Card::ResourceCard::Ore, 1}};

    if (!canAfford(developmentCardCost))
    {
        cout << "Not enough resources to purchase a development card." << endl;
        return false;
    }

    Card drawnCard = drawDevelopmentCard();
    addDevelopmentCard(drawnCard); // Add the card to the player's development cards
    for (auto i = developmentCardCost.begin(); i != developmentCardCost.end(); ++i)
    {
        resourceCards[i->first] -= i->second;
    }

    cout << name << " purchased a development card: " << endl;

    // Handle the speical card actions ( when drawing development card the player must use it immediatly)

    switch (drawnCard.getSpecialCard())
    {
    case Card::SpecialCard::Knight:
        knightCount++;
        cout << name << " received Knight card" << endl;
        if (knightCount == 3)
        {
            recivePoint();
            recivePoint();
            cout << name << " has played 3 knights and received 2 points!" << endl;
        }
        break;
    case Card::SpecialCard::VictoryPoint:
        cout << name << " received Victory Point card" << endl;
        recivePoint();
        break;
    case Card::SpecialCard::RoadBuilding:
        cout << name << " received Road Building card" << endl;
        useRoadBuilding(board);
        break;
    case Card::SpecialCard::Monopoly:
        cout << name << " received Monopoly card" << endl;
        useMonopoly(players);
        break;
    case Card::SpecialCard::YearOfPlenty:
        cout << name << " received Year of Plenty card" << endl;
        useYearOfPlenty();
        break;
    }

    return true;
}

void Player::addResourceCard(Card::ResourceCard resource)
{
    resourceCards[resource]++;
}

void Player::addResourceCard(ResourceType resource)
{
    Card::ResourceCard resourceCard;
    switch (resource)
    {
    case ResourceType::Wheat:
        resourceCard = Card::ResourceCard::Wheat;
        break;
    case ResourceType::Sheep:
        resourceCard = Card::ResourceCard::Sheep;
        break;
    case ResourceType::Wood:
        resourceCard = Card::ResourceCard::Wood;
        break;
    case ResourceType::Brick:
        resourceCard = Card::ResourceCard::Brick;
        break;
    case ResourceType::Ore:
        resourceCard = Card::ResourceCard::Ore;
        break;
    default:
        throw std::invalid_argument("Invalid ResourceType");
    }
    addResourceCard(resourceCard);
}

bool Player::removeResourceCard(Card::ResourceCard resource)
{
    if (resourceCards[resource] > 0)
    {
        resourceCards[resource]--;
        return true;
    }
    cout << "This player as no more " << endl;
    return false;
}

void Player::addDevelopmentCard(const Card &card)
{
    developmentCards.push_back(card);
}

Card Player::drawDevelopmentCard()
{
    return Card::drawDevelopmentCard();
}

void Player::listResources() const
{
    cout << "Resources of " << name << ":" << endl;
    for (const auto &pair : resourceCards)
    {
        std::string resourceName;
        switch (pair.first)
        {
        case Card::ResourceCard::Wheat:
            resourceName = "Wheat";
            break;
        case Card::ResourceCard::Sheep:
            resourceName = "Sheep";
            break;
        case Card::ResourceCard::Wood:
            resourceName = "Wood";
            break;
        case Card::ResourceCard::Brick:
            resourceName = "Brick";
            break;
        case Card::ResourceCard::Ore:
            resourceName = "Ore";
            break;
        }
        cout << resourceName << ": " << pair.second << endl;
    }
}

void Player::recivePoint()
{
    points++;
    if (points == 10)
    {
        cout << "The winner is: " << name << "!" << endl;
    }
    else
    {
        if (points > 8)
        {
            cout << name << " now has " << points << " points!" << endl;
        }
    }
}

int Player::getPoints()
{
    cout << points << endl;
    return points;
}

// the two roads are placing randomly next to a settelement owned by the player
void Player::useRoadBuilding(Board &board)
{
    int roadsPlaced = 0;

    for (const auto &tile : board.getTiles())
    {
        for (const auto &vertex : tile->vertcies)
        {
            if (vertex->taken && vertex->takenBy == name)
            {
                for (const auto &edge : tile->edges)
                {
                    if (!edge->taken)
                    {
                        edge->taken = true;
                        edge->takenBy = name;
                        roads.insert(edge->id);
                        cout << name << " place a road on edge" << edge->id << endl;
                        roadsPlaced++;
                        break;
                    }
                }
            }
            if (roadsPlaced == 2)
            {
                cout << name << " succsessfully placed 2 roads" << endl;
                return;
            }
        }
    }
    if (roadsPlaced < 2)
    {
        cout << "coudlnt find place to set the 2 roads" << endl;
    }
}

void Player::useMonopoly(vector<shared_ptr<Player>> &players)
{
    for (auto &otherPlayer : players)
    {
        if (otherPlayer->name == name)
        {
            continue;
        }

        for (auto &resource : otherPlayer->resourceCards)
        {
            if (resource.second > 0)
            {
                // took the first resource the loop interact from other player to the player who use the monoploy
                resource.second--;
                resourceCards[resource.first]++;
                break; // moving to the next player
            }
        }
    }
}
void Player::useYearOfPlenty()
{
    srand(static_cast<unsigned>(std::time(0)));

    for (int i = 0; i < 2; ++i)
    {
        // Randomly select a resource card to take from the bank
        int randomResource = rand() % 5;
        Card::ResourceCard resourceCard = static_cast<Card::ResourceCard>(randomResource);
        resourceCards[resourceCard]++;
        cout << name << " used Year of plenty" << endl;
    }
}

void Player::useKnight()
{
    knightCount++;
    if (knightCount == 3)
    {
        points = points + 2;
    }
}

void Player::useVictoryPoint()
{
    recivePoint();
}

void Player::tradeResource(Player &otherPlayer, Card::ResourceCard giveResource, Card::ResourceCard getResource)
{
    if (resourceCards[giveResource] > 0 && otherPlayer.resourceCards[getResource] > 0)
    {
        resourceCards[giveResource]--;
        otherPlayer.resourceCards[giveResource]++;
        resourceCards[getResource]++;
        otherPlayer.resourceCards[getResource]--;
        cout << "Trade succefuly " << endl;
    }
    else
    {
        cout << " Trade failed" << endl;
    }
}