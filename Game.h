#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Ship.h"
#include "Mine.h"
#include "Utils.h"

class Game {
private:
    std::vector<GameEntity*> entities;  // Store all game entities (ships and mines)

public:
    // Getter for entities
    std::vector<GameEntity*>& get_entities() {
        return entities;
    }

    // Setter for entities
    void set_entities(const std::vector<GameEntity*>& new_entities) {
        entities = new_entities;
    }

    // Initialize the game with ships and mines in random positions
    std::vector<GameEntity*> initGame(int numShips, int numMines, int gridWidth, int gridHeight) {
        // Create ships and store them in entities vector
        for (int i = 0; i < numShips; i++) {
            auto pos = Utils::generateRandomPos(gridWidth, gridHeight);
            entities.push_back(new Ship(std::get<0>(pos), std::get<1>(pos)));
        }
        // Create mines and store them in entities vector
        for (int i = 0; i < numMines; i++) {
            auto pos = Utils::generateRandomPos(gridWidth, gridHeight);
            entities.push_back(new Mine(std::get<0>(pos), std::get<1>(pos)));
        }
        return entities;
    }

    // Game loop simulating movement and interactions
    void gameLoop(int maxIterations, double mineDistanceThreshold) {
        for (int iteration = 0; iteration < maxIterations; iteration++) {
            bool explosionOccurred = false;  // Flag for explosion event

            // Move all ships
            for (auto entity : entities) {
                Ship* ship = dynamic_cast<Ship*>(entity);
                if (ship && ship->getPos() != std::make_tuple(-1, -1)) {
                    ship->move(1, 0);  // Move ship by (1, 0)
                }
            }

            // Check distance between ships and mines, handle explosion
            for (auto entity1 : entities) {
                Ship* ship = dynamic_cast<Ship*>(entity1);
                if (ship && ship->getPos() != std::make_tuple(-1, -1)) {
                    for (auto entity2 : entities) {
                        Mine* mine = dynamic_cast<Mine*>(entity2);
                        if (mine && mine->getType() != GameEntityType::NoneType) {
                            double distance = Utils::calculateDistance(ship->getPos(), mine->getPos());

                            if (distance <= mineDistanceThreshold) {
                                mine->explode();
                                ship->setPos(-1, -1);  // Mark ship as destroyed
                                explosionOccurred = true;
                                break;  // Stop checking further mines for this ship
                            }
                        }
                    }
                }
                if (explosionOccurred) break;  // Stop checking further ships if explosion occurred
            }

            // Check if all ships are destroyed
            bool allShipsDestroyed = true;
            for (auto entity : entities) {
                Ship* ship = dynamic_cast<Ship*>(entity);
                if (ship && ship->getPos() != std::make_tuple(-1, -1)) {
                    allShipsDestroyed = false;
                    break;
                }
            }

            // If all ships are destroyed, end the game
            if (allShipsDestroyed) {
                std::cout << "All ships destroyed. Game over!\n";
                return;  // Exit the game loop
            }
        }

        // If max iterations reached, game ends
        // No need to print anything extra here
    }
};

#endif // GAME_H