#ifndef LEVEL_MANAGER_HPP
#define LEVEL_MANAGER_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class LevelManager {
public:
    static const int MAP_SIZE = 20;
    enum TileType { FLOOR = 0, WALL = 1, BREAKABLE = 2, PLAYER, ENEMY, POWERUP };

    LevelManager(const std::string& filename);
    const std::vector<std::vector<int>>& getMap() const;

private:
    std::vector<std::vector<int>> map;
    void loadLevel(const std::string& filename);
};

#endif