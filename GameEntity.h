#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <tuple>

enum GameEntityType { ExplosionType, MineType, NoneType, ShipType };

class GameEntity {
private:
    std::tuple<int, int> position;
    GameEntityType type;

public:
    // Constructor
    GameEntity(int x, int y, GameEntityType entityType)
        : position(std::make_tuple(x, y)), type(entityType) {}

    // Virtual destructor to enable polymorphism
    virtual ~GameEntity() {}

    // Getter for position
    std::tuple<int, int> getPos() const { return position; }

    // Setter for position
    void setPos(int x, int y) {
        position = std::make_tuple(x, y);
    }

    // Getter for type
    GameEntityType getType() const { return type; }

    // Setter for type
    void setType(GameEntityType newType) {
        type = newType;
    }
};

#endif // GAMEENTITY_H
