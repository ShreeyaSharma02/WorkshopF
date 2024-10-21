#ifndef MINE_H
#define MINE_H

#include "GameEntity.h"
#include "Explosion.h"

// Mine class inheriting from GameEntity
class Mine : public GameEntity {
public:
    // Constructor that sets position and type to MineType
    Mine(int x, int y)
        : GameEntity(x, y, GameEntityType::MineType) {}

    // Explode function returns an Explosion object
    Explosion explode() {
        setType(GameEntityType::NoneType);
        return Explosion(std::get<0>(getPos()), std::get<1>(getPos()));
    }
};

#endif // MINE_H