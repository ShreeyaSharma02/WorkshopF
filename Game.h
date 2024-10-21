#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Ship.h"
#include "Mine.h"
#include "Utils.h"

class Game {
private:
    std::vector<GameEntity*> entities;

public:
    // Getter for entities
    std::vector<GameEntity*>& get_entities() { return entities; }

    // Setter for entities
    void set_entities(const std::vector<GameEntity*>& new_entities) { entities = new_entities; }

    // Initialize the game
    std::vector<GameEntity*> initGame(int numShips, int numMines, int gridWidth, int gridHeight) {
        for (int i = 0; i < numShips; i++) {
            auto pos = Utils::generateRandomPos(gridWidth, gridHeight);
            entities.push_back(new Ship(std::get<0>(pos), std::get<1>(pos)));
        }
        for (int i = 0; i < numMines; i++) {
            auto pos = Utils::generateRandomPos(gridWidth, gridHeight);
            entities.push_back(new Mine(std::get<0>(pos), std::get<1>(pos)));
        }
        return entities;
    }

    // Game loop
    void gameLoop(int maxIterations, double mineDistanceThreshold) {
    for (int iteration = 0; iteration < maxIterations; iteration++) {
        bool explosionOccurred = false;  // Track if an explosion occurred
        std::cout << "Iteration: " << iteration + 1 << "\n";

        // Move all Ship objects by (1, 0)
        for (auto entity : entities) {
            Ship* ship = dynamic_cast<Ship*>(entity);
            if (ship && ship->getPos() != std::make_tuple(-1, -1)) {
                ship->move(1, 0);  // Move the ship by (1, 0)
            }
        }

        // Check the distance between each ship and each mine
        for (auto entity1 : entities) {
            Ship* ship = dynamic_cast<Ship*>(entity1);
            if (ship && ship->getPos() != std::make_tuple(-1, -1)) {  // Check only if ship is not destroyed
                for (auto entity2 : entities) {
                    Mine* mine = dynamic_cast<Mine*>(entity2);
                    if (mine && mine->getType() != GameEntityType::NoneType) {  // Check if the mine hasn't exploded
                        double distance = Utils::calculateDistance(ship->getPos(), mine->getPos());

                        // If within threshold, call explode() and apply explosion to the ship
                        if (distance <= mineDistanceThreshold) {
                            std::cout << "Mine exploded near ship at distance: " << distance << "\n";
                            mine->explode();  // Mark the mine as exploded
                            ship->setPos(-1, -1);  // Mark the ship as destroyed
                            explosionOccurred = true;
                            break;  // Stop checking further mines once an explosion occurs
                        }
                    }
                }
            }
            if (explosionOccurred) {
                break;  // Stop checking further ships once an explosion occurs
            }
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

        if (allShipsDestroyed) {
            std::cout << "All ships destroyed. Game over!\n";
            std::cout << "Entity Type: " << GameEntityType::ShipType << "\n";  // Print only the ShipType
            return;  // Exit the game loop early if all ships are destroyed
        }
    }

    // Print "Max iterations reached" only if the loop runs fully
    std::cout << "Max iterations reached. Game over!\n";
}
};

#endif // GAME_H