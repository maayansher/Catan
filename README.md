# Catan project in C++
This project implements a simplified version of the board game Catan. The game allows three players to play the game and to make some actions in order to win the game. They can place settlements, build roads, draw development cards, and trade resources. The game logic includes rules for resource distribution, road building, and upgrading settlements to cities.

## Board
The board i created represented by vector of shared_ptr of Tiles. The board built from 19 tiles and each tile have 6 edges and 6 vertcies. Ive declared that the tiles who have sharing edges and vertices points to the same place.
![catan vertcies pointers](https://github.com/maayansher/Catan/assets/72826364/a9307fc8-5f75-4d2f-adfb-9ed186e31979)

## Rules

1.**Setup** : Each player places 2 initial settlements and 2 roads, after they place the 2 initial settlements they get the resources they stand on.
2.**Resource Distribution**: When a player rolls the dice, resources are distributed based on the dice roll. The number the player rolled on the dice determine which tile is activate (which means the
player who owns settlement/city on the tile gets the resources).
