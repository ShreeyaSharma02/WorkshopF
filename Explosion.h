#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "GameEntity.h"
#include "Effect.h"

// Explosion class inheriting from GameEntity and Effect
class Explosion : public GameEntity, public Effect {
public:
    // Constructor that sets position and type to ExplosionType
    Explosion(int x, int y)
        : GameEntity(x, y, GameEntityType::ExplosionType) {}

    // Apply effect, destroying the entity
    void apply(GameEntity& entity) override {
        entity.setPos(-1, -1);
        entity.setType(GameEntityType::NoneType);
    }
};

#endif // EXPLOSION_H