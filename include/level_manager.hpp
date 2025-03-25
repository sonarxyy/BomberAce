#ifndef LEVEL_MANAGER_HPP
#define LEVEL_MANAGER_HPP

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <filesystem>
#include "constants.hpp"

class LevelManager {
public:
    enum TileType {
        FLOOR = 0,
        WALL = 1,
        BREAKABLE = 2,
    };

    LevelManager(const std::string& levelFolder);

    void LoadAllLevels(const std::string& folderPath);
    void LoadLevel(const std::string& filename);
    void NextLevel();

    const std::vector<std::vector<int>>& getMap() const;
    bool IsLastLevel() const;

private:
    std::vector<std::vector<int>> map;  // Current level map
    std::vector<std::string> levelFiles; // List of level file paths
    size_t currentLevelIndex; // Track current level index
};

#endif
