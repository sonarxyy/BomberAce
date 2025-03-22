#include "level_manager.hpp"

LevelManager::LevelManager(const std::string& filename) {
    loadLevel(filename);
}

void LevelManager::loadLevel(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open level file!" << std::endl;
        return;
    }

    map.resize(MAP_SIZE, std::vector<int>(MAP_SIZE, FLOOR));
    std::string line;
    int index = 0;

    while (std::getline(file, line) && index < MAP_SIZE) {
        for (int i = 0, col = 0; col < MAP_SIZE && i < line.length(); i++) {
            if (line[i] == ' ') continue;
            switch (line[i]) {
            case '1': map[index][col] = WALL; break;
            case '2': map[index][col] = BREAKABLE; break;
            case 'P': map[index][col] = PLAYER; break;
            case 'E': map[index][col] = ENEMY; break;
            case 'U': map[index][col] = POWERUP; break;
            default: map[index][col] = FLOOR; break;
            }
            col++;
        }
        index++;
    }
    file.close();
}

const std::vector<std::vector<int>>& LevelManager::getMap() const {
    return map;
}
