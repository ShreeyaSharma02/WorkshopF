#ifndef UTILS_H
#define UTILS_H

#include <tuple>
#include <cmath>
#include <cstdlib>
#include <ctime>

class Utils {
public:
    // Generate a random position within the grid size
    static std::tuple<int, int> generateRandomPos(int gridWidth, int gridHeight) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));  // Seed random generator
        int x = std::rand() % gridWidth;
        int y = std::rand() % gridHeight;
        return std::make_tuple(x, y);
    }

    // Calculate Euclidean distance between two points
    static double calculateDistance(std::tuple<int, int> pos1, std::tuple<int, int> pos2) {
        int x1, y1, x2, y2;
        std::tie(x1, y1) = pos1;
        std::tie(x2, y2) = pos2;
        return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
    }
};

#endif // UTILS_H