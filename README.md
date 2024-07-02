# Catan project in C++
This project implements a simplified version of the board game Catan. The game allows three players to play the game and to make some actions in order to win the game. They can place settlements, build roads, draw development cards, and trade resources. The game logic includes rules for resource distribution, road building, and upgrading settlements to cities.

## Board
The board i created represented by vector of shared_ptr of Tiles. The board built from 19 tiles and each tile have 6 edges and 6 vertcies and a number on it, for the dice roll action. Ive declared that the tiles who have sharing edges and vertices points to the same place in the memory.
![catan vertcies pointers](https://github.com/maayansher/Catan/assets/72826364/a9307fc8-5f75-4d2f-adfb-9ed186e31979)

The board is hard-coded and represent by that:

                            Ore(6)          Sheep(5)             Ore(9)

                 Wheat(4)             Ore(3)           Wheat(8)           Brick(10)

            Sheep(6)            Wood(5)          Desert(-1)            Wood(9)            Wood(12)

                 Wheat(3)           Brick(2)           Wheat(10)           Brick(11)

                          Sheep(11)            Wood(4)           Sheep(8)
## Rules

1.**Setup**:
The game starts from player1 and go on to player 2 then 3. Each player places 2 initial settlements and 2 initial roads, after they place the 2 initial settlements they get the resources they stand on.

2.**Resource Distribution**:
When a player rolls the dice, resources are distributed based on the dice roll. The number the player rolled on the dice determine which tile is activate (which means the
player who owns settlement/city on the tile gets the resources).

3.**Turn**:
When a player rolled the dice now its his turn, he can choose to build a settlement, a road, upgrading a settelement to city, purchase development card and to trade with other player.
If the player doesnt have enough resources to make the payment, the turn skips to the next player.

4.**Development Cards**:
When a player purchase a development card, the cards he gets (if he can afford it) are used immediatly.

5.**Trade**:
You can trade with other players to change the resource, you can only change 1 resource you have for 1 other resource he have.

## Explanation for each class and their methods:
# Board:
The board as vector of shared_ptr of Tile, which represent the 19 tiles of the board. When we call the board
at the begging of the game, we call the initializeBoard method which create the whole board and calls also the to linkTiles methos which connect all the edges and vertcies who have sharing points.

- resourceToString: gets the resource type and change it to string.
- createEdge/createVertex: when the board is initialize, those functions creating the pointers to the edges and also give them unique id.
- getEdge/getVertex: returns the id of the wanted Edge/Vertex.
- getTile: returns the pointer to the tile.
- getTiles: returns the whole tiles of the board.
- getVertexId/getEdgeId: get the vertex/edge Id by the tile index and the vertex/edge position.
- distributeResources: the method gets the dice roll result and distrubte the resources to each player who have settelement/city on the tile with the roll number.

# Card:
The card class have two enums classes for resources card and for development card.
This class holds the development deck and responsible for initialize the deck with the desire amount of development cards.

- isResource: return if the card is resource or not.
- initializeDevelopmentDeck: responsible for creating the developement deck and shuffling it.
- drawDevelopmentCard: method to draw a development card.

# Player:
The player class represent the player, each player have their settelment and roads saved in unordered set.
They have their points saved,their knight count and resource cards they have.

- rollDice: method for the dice rolling, randomly generate a number between 2-12, the result passed to the distrbute resources method.
- placeInitialSettlement/Road: this method gets the board, a tile index and the vertex/edge where the player wants to place his first 2 Settlements/Roads.
- placeRoad/Settelment: this method is simmilar to initialSettelement/Road, the change is that in here the method checks first if a player can afford to buy a road or settelment, then calls the initialPlace to place it if he can afford it.
- placeCity: method to replace a settelement into a city, the method first checks if you can afford a city, then if theres a settelemnt where the player want to build it and that he own the settelement in that vertex.
- receivePoint: adds 1 point to a player. this method is used when a player place a settlement, building a city gets 3 knights or point from development card.
- useRoadBuilding: development card that gives the player 2 roads randomly, on a edge he is allowed to place a road.
- useYearOfPlenty: development card that gives the player 2 resources randomly from the bank.
- useMonopoly: development card that gives the player 1 resource randomly from each player.
- canAfford: checks if the player can afford a payment before he buys something. when the player wants to place a road or build a city , this method checks if the player have enough resources to build.
- purchaseDevelopmentCard: method for purchasing a development card, if the player can afford, he will draw randomly a development card from the deck and use it.
- addResource: add the resource to the players hand.
- addDevelopmentCard: add the development card the player draw to his hand.
- listResources: prints the list of resources the player have.
- tradeResource: trade a resource with other player. can trade only 1 resource for 1 resource (if the two players own that resource)

# Tile:
The tile class represent the pieces of the board, each tile have number, resource type and index.
Also each tile have their own 6 edges and 6 vertices to represent the places the player can build a road or settlements.
when the board is initialized, each tile get their own index in order to track each tile.

# How to run the project
Use the provided `makefile` to build and run the project:
    
   - To build main:
        ```bash
        make catan
        ```
  - To build tests:
      ```bash
      make test
      ```
  - To check for memory leaks using Valgrind:
      ```bash
      make valgrind
      ```
