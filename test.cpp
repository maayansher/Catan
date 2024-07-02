//Maayan1sher@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "board.hpp"
#include "player.hpp"

using namespace std;

TEST_CASE("Place initial settlements and roads")
{
    auto p1 = make_shared<Player>("Player 1");
    auto p2 = make_shared<Player>("Player 2");
    Board board;

    // Player 1 places a settlement on tile 0, vertex 0
    CHECK(p1->placeInitialSettlement(board, 0, 0) == true);

    // Player 2 attempts to place a settlement on the same vertex
    CHECK(p2->placeInitialSettlement(board, 0, 0) == false);

    // Player 1 place a road on a edge with settlement nearby
    CHECK(p1->placeInitialRoad(board, 0, 5) == true);

    // Player 1 attempts to place a road on a edge with no settlement on adjacent vertex
    CHECK(p1->placeInitialRoad(board, 0, 1) == false);

    // Player 2 attempts to place a road on a edge with a road on it
    CHECK(p1->placeInitialRoad(board, 0, 5) == false);
}

TEST_CASE("Buying development card")
{
    auto p1 = make_shared<Player>("Player 1");
    auto p2 = make_shared<Player>("Player 2");
    Board board;
    vector<shared_ptr<Player>> players = {p1, p2};

    p1->addResourceCard(ResourceType::Ore);
    p1->addResourceCard(ResourceType::Sheep);
    // Player1 is trying to buy development card but he dont have wheat
    CHECK(p1->purchaseDevelopmentCard(board, players) == false);

    p1->addResourceCard(ResourceType::Wheat);
    CHECK(p1->purchaseDevelopmentCard(board, players) == true);
}

TEST_CASE("Resources usage")
{
    auto p1 = make_shared<Player>("Player 1");
    auto p2 = make_shared<Player>("Player 2");
    Board board;
    vector<shared_ptr<Player>> players = {p1, p2};

    // Player1 attempts to place settlement with no resources
    CHECK(p1->placeSettlement(board, 5, 5) == false);

    p1->addResourceCard(ResourceType::Brick);
    p1->addResourceCard(ResourceType::Sheep);
    p1->addResourceCard(ResourceType::Wood);
    p1->addResourceCard(ResourceType::Wheat);

    // Player 1 now have the resources to build settlement
    CHECK(p1->placeSettlement(board, 5, 5) == true);

    // Player1 attempts to place road with no resources
    CHECK(p1->placeRoad(board, 5, 5) == false);

    p1->addResourceCard(ResourceType::Brick);
    p1->addResourceCard(ResourceType::Wood);

    // Player1 can now afford placing a road
    CHECK(p1->placeRoad(board, 5, 5) == true);

    // Player1 attempets to place city on a place without a resources
    CHECK(p1->placeCity(board, 5, 5) == false);

    p1->addResourceCard(ResourceType::Ore);
    p1->addResourceCard(ResourceType::Ore);
    p1->addResourceCard(ResourceType::Ore);
    p1->addResourceCard(ResourceType::Wheat);
    p1->addResourceCard(ResourceType::Wheat);

    // Player1 can now afford city, but place it on a place without a settelement
    CHECK(p1->placeCity(board, 8, 5) == false);

    // Player1 now place the city on settelment he owns
    CHECK(p1->placeCity(board, 5, 5) == true);
}

TEST_CASE("Getting Points")
{
    auto p1 = make_shared<Player>("Player 1");
    Board board;
    p1->placeInitialSettlement(board, 5, 5);
    p1->placeInitialSettlement(board, 9, 3);

    p1->addResourceCard(ResourceType::Ore);
    p1->addResourceCard(ResourceType::Ore);
    p1->addResourceCard(ResourceType::Ore);
    p1->addResourceCard(ResourceType::Wheat);
    p1->addResourceCard(ResourceType::Wheat);

    p1->placeCity(board, 5, 5);
    // Player1 placed two settelements (got 2 points), the placed a city (another point)
    CHECK(p1->getPoints() == 3);
}

TEST_CASE("Resource list")
{
    auto p1 = make_shared<Player>("Player 1");
    p1->addResourceCard(ResourceType::Sheep);
    p1->addResourceCard(ResourceType::Ore);
    p1->addResourceCard(ResourceType::Ore);
    p1->addResourceCard(ResourceType::Wheat);
    p1->addResourceCard(ResourceType::Wheat);

    ostringstream oss;
    streambuf *old_cout = cout.rdbuf(oss.rdbuf());
    p1->listResources();
    cout.rdbuf(old_cout);

    string excpetedOutput = "Resources of Player 1:\nWheat: 2\nOre: 2\nSheep: 1\n";

    CHECK(oss.str() == excpetedOutput);
};

TEST_CASE("Development Cards")
{
    /**
     * Monopoly test:
     */
    auto p1 = make_shared<Player>("Player1");
    auto p2 = make_shared<Player>("Player2");
    auto p3 = make_shared<Player>("Player3");

    vector<shared_ptr<Player>> players = {p1, p2, p3};
    Board board;

    // add some resources to player 2 and 3
    p2->addResourceCard(ResourceType::Brick);
    p3->addResourceCard(ResourceType::Wood);

    // add monopolycard to player1 and use it
    Card monopolyCard(Card::SpecialCard::Monopoly);
    p1->addDevelopmentCard(monopolyCard);

    p1->useMonopoly(players);

    ostringstream oss;
    streambuf *old_cout = cout.rdbuf(oss.rdbuf());
    p1->listResources();
    cout.rdbuf(old_cout);

    // Player1 got the 2 resources from player 2 and 3
    string excpetedOutput = "Resources of Player1:\nWood: 1\nBrick: 1\n";

    CHECK(oss.str() == excpetedOutput);

    /**
     * VictoryPoint test:
     * adding VictoryPoint card to player1, now he have 1 point
     */

    Card victoryPoint(Card::SpecialCard::VictoryPoint);
    p1->addDevelopmentCard(victoryPoint);
    p1->useVictoryPoint();
    CHECK(p1->getPoints() == 1);

    /**
     * Knight test:
     * Adding 3 Knight card to player1, now he got 2 more points
     */

    Card knightCard(Card::SpecialCard::Knight);
    p1->addDevelopmentCard(knightCard);
    p1->addDevelopmentCard(knightCard);
    p1->addDevelopmentCard(knightCard);
    p1->useKnight();
    p1->useKnight();
    p1->useKnight();
    CHECK(p1->getPoints() == 3);
}

TEST_CASE("Trade cards")
{
    auto p1 = make_shared<Player>("Player1");
    auto p2 = make_shared<Player>("Player2");

    // Adding ore to player1 and wheat to player2
    p1->addResourceCard(ResourceType::Ore);
    p2->addResourceCard(ResourceType::Wheat);

    // Player1 is trading ore to get wheat from player 2
    p1->tradeResource(*p2, Card::ResourceCard::Ore, Card::ResourceCard::Wheat);

    ostringstream oss1;
    streambuf *old_cout1 = cout.rdbuf(oss1.rdbuf());
    p1->listResources();
    cout.rdbuf(old_cout1);

    // after the tradee, player 1 have 1 wheat and 0 ore, player 2 have 0 wheat and 1 ore.
    string excpetedOutput1 = "Resources of Player1:\nWheat: 1\nOre: 0\n";
    CHECK(oss1.str() == excpetedOutput1);
}
