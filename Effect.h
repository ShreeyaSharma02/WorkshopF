#ifndef EFFECT_H
#define EFFECT_H

#include "GameEntity.h"

class Effect {
public:
    // Pure virtual function to apply effect on a GameEntity
    virtual void apply(GameEntity& entity) = 0;
};

#endif // EFFECT_H