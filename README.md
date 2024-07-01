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

1.**Setup** :The game starts from player1 and go on to player 2 then 3. Each player places 2 initial settlements and 2 initial roads, after they place the 2 initial settlements they get the resources they stand on.
2.**Resource Distribution**: When a player rolls the dice, resources are distributed based on the dice roll. The number the player rolled on the dice determine which tile is activate (which means the
player who owns settlement/city on the tile gets the resources).
3.**Turn**: When a player rolled the dice now its his turn, he can choose to build a settlement, a road, upgrading a settelement to city, purchase development card and to trade with other player.
If the player doesnt have enough resources to make the payment, the turn skips to the next player.
4.**Development Cards**: When a player purchase a development card, the cards he gets (if he can afford it) are used immediatly.
5.**Trade**: You can trade with other players to change the resource, you can only change 1 resource you have for 1 other resource he have.

## Explanation for each file and their methods:
