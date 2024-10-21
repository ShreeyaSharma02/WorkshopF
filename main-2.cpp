#include <iostream>
#include "Ship.h"
#include "Mine.h"
#include "Explosion.h"

int main() {
    // Create Ship and Mine objects
    Ship ship(5, 5);
    Mine mine(8, 8);

    // Move the ship
    std::cout << "Ship position before moving: (" << std::get<0>(ship.getPos()) << ", " << std::get<1>(ship.getPos()) << ")\n";
    ship.move(3, -2);
    std::cout << "Ship position after moving: (" << std::get<0>(ship.getPos()) << ", " << std::get<1>(ship.getPos()) << ")\n";

    // Mine explodes and affects the ship
    Explosion explosion = mine.explode();
    explosion.apply(ship);
    std::cout << "Ship position after explosion: (" << std::get<0>(ship.getPos()) << ", " << std::get<1>(ship.getPos()) << ")\n";

    return 0;
}