#ifndef SHIP_H
#define SHIP_H

#include "GameEntity.h"

// Ship class inheriting from GameEntity
class Ship : public GameEntity {
public:
    // Constructor that sets position and type to ShipType
    Ship(int x, int y)
        : GameEntity(x, y, GameEntityType::ShipType) {}

    // Move function to change ship's position
    void move(int dx, int dy) {
        auto [x, y] = getPos();
        setPos(x + dx, y + dy);
    }
};

#endif // SHIP_H