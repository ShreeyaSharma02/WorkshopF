#include <iostream>
#include "Game.h"

int main() {
    // Create a Game object
    Game game;

    // Initialize the game with 3 ships and 2 mines
    game.initGame(3, 2, 10, 10);

    // Run the game loop
    game.gameLoop(5, 2.0);

    return 0;
}