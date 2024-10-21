#include <iostream>
#include "Game.h"

int main() {
    // Create a Game object
    Game game;

    // Initialize the game with 3 ships and 2 mines in a 10x10 grid
    game.initGame(3, 2, 10, 10);

    // Run the game loop with a max of 5 iterations and a mine distance threshold of 1.0
    game.gameLoop(5, 1.0);

    return 0;
}
