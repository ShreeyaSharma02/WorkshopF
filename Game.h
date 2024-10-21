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
            std::cout << "Iteration: " << iteration + 1 << "\n";

            // Move all ships
            for (auto entity : entities) {
                Ship* ship = dynamic_cast<Ship*>(entity);
                if (ship && ship->getPos() != std::make_tuple(-1, -1)) {
                    ship->move(1, 0); // Move ship by (1, 0)
                }
            }

            // Check if any ship is close to a mine
            for (auto entity1 : entities) {
                Ship* ship = dynamic_cast<Ship*>(entity1);
                if (ship && ship->getPos() != std::make_tuple(-1, -1)) {
                    for (auto entity2 : entities) {
                        Mine* mine = dynamic_cast<Mine*>(entity2);
                        if (mine && mine->getType() == GameEntityType::MineType) {
                            double distance = Utils::calculateDistance(ship->getPos(), mine->getPos());
                            if (distance <= mineDistanceThreshold) {
                                std::cout << "Mine exploded near ship at distance: " << distance << "\n";
                                mine->explode(); // Explode mine
                                ship->setPos(-1, -1); // Mark ship as destroyed
                            }
                        }
                    }
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
                break;
            }
        }
    }
};

#endif // GAME_H