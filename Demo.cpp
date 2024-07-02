// Maayan1sher@gmail.com

/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "player.hpp"
#include "board.hpp"
#include "card.hpp"
using namespace std;
//
/*The board:                Ore(6)          Sheep(5)             Ore(9)

                 Wheat(4)             Ore(3)           Wheat(8)           Brick(10)

            Sheep(6)            Wood(5)          Desert(-1)            Wood(9)            Wood(12)

                 Wheat(3)           Brick(2)           Wheat(10)           Brick(11)

                          Sheep(11)            Wood(4)           Sheep(8)
*/
int main()
{
    srand(static_cast<unsigned int>(time(0)));

    auto p1 = make_shared<Player>("Alon");
    auto p2 = make_shared<Player>("Ofir");
    auto p3 = make_shared<Player>("Maayan");

    vector<shared_ptr<Player>> players = {p1, p2, p3};
    Board board; // Creating the board
     /**
      * Each player place 2 settelements and 2 roads
      */
    p1->placeInitialSettlement(board, 16, 0); // Wheat(3) Brick(2) Sheep(11)
    p2->placeInitialSettlement(board, 10, 0); // Wood(9) Brick(10) Wheat(8)
    p3->placeInitialSettlement(board, 4, 0);  //   Ore(6)   Ore(3)  Sheep(5)

    p1->placeInitialSettlement(board, 18, 0); // Wheat(10) Brick(11) Sheep(8)
    p2->placeInitialSettlement(board, 14, 4); // Brick(2)  Wheat(10) Wood(4)
    p3->placeInitialSettlement(board, 8, 0);  //  Wheat(4)  Wood(5)  Ore(3)

    p1->placeInitialRoad(board, 16, 5);
    p1->placeInitialRoad(board, 16, 0);

    p2->placeInitialRoad(board, 14, 4);
    p2->placeInitialRoad(board, 14, 5);

    p3->placeInitialRoad(board, 4, 5);
    p3->placeInitialRoad(board, 4, 4);

    p1->rollDice(board, players);
    p2->rollDice(board, players);

     /**
      * List of resources is printed for player2, after he placed 2 roads the list is printed
      * again and the resources for 2 roads are being reduced from the list
      */
    p2->listResources();
    p2->placeRoad(board, 10, 5);
    p2->placeRoad(board, 10, 4);
    p2->listResources();
    p3->rollDice(board, players);

    p1->rollDice(board, players);
    p2->rollDice(board, players);
    p3->rollDice(board, players);
     /**
      * List of resources is printed for player3, after he placed a city on the settelement
      * he owns, the list is printed again and the cost for city was reduced from the list, and he got another point
      */
    p3->listResources();
    p3->placeCity(board, 8, 0);
    p3->listResources();
    
    
    p1->rollDice(board, players);
    p2->rollDice(board, players);
    p3->rollDice(board,players);

    p3->purchaseDevelopmentCard(board,players);

     /**
      * Player1 is trading brick for wood so he can place a settelment on the desired place on the board
      */
    p1->listResources();
    p1->tradeResource(*p3,Card::ResourceCard::Brick,Card::ResourceCard::Wood);
    p1->listResources();

    p1->placeSettlement(board,11,2);

     p1->getPoints();
     p2->getPoints();
     p3->getPoints();
}

