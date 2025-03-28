#include "level_manager.hpp"

LevelManager::LevelManager(const std::string& folderPath) {
    currentLevelIndex = 0;
    LoadAllLevels(folderPath);

    if (!levelFiles.empty()) {
        LoadLevel(levelFiles[currentLevelIndex]);
    }
}

void LevelManager::LoadAllLevels(const std::string& folderPath) {
    levelFiles.clear();

    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.path().extension() == ".txt") {
            levelFiles.push_back(entry.path().string());
        }
    }

    if (levelFiles.empty()) {
        std::cerr << "No level files found in folder: " << folderPath << std::endl;
    }
    else {
        std::sort(levelFiles.begin(), levelFiles.end()); 
    }
}

void LevelManager::LoadLevel(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open level file: " << filename << std::endl;
        return;
    }

    map.clear(); // Clear existing map before loading new one
    std::string line;
    int rowCount = 0;

    while (std::getline(file, line)) {
        int validCount = 0;
        std::vector<int> row;

        for (char c : line) {
            if (c != ' ') validCount++;

            switch (c) {
            case '0': 
                row.push_back(FLOOR); 
                break;
            case '1': 
                row.push_back(WALL);
                break;
            case '2': 
                row.push_back(BREAKABLE); 
                break;
            case 'U':
            case 'u':
                row.push_back(POWER_UP); 
                break;
            case ' ': break;
            default:
                std::cerr << "Error: Invalid character '" << c << "' in level file: " << filename << std::endl;
                file.close();
                return;
            }
        }

        if (validCount < MAP_COLS) {
            std::cerr << "Error: Level file '" << filename << "' contains a row with less than" <<  MAP_ROWS << "tiles!" << std::endl;
            file.close();
            return;
        }

        map.push_back(row);
        rowCount++;
    }

    if (rowCount < MAP_ROWS) {
        std::cerr << "Error: Level file '" << filename << "' contains less than" << MAP_ROWS << "rows!" << std::endl;
        return;
    }

    file.close();
    std::cout << "Loaded level: " << filename << std::endl;
}

void LevelManager::NextLevel() {
    if (currentLevelIndex >= levelFiles.size()) {
        std::cout << "All levels completed! No more levels to load." << std::endl;
        return;
    }

    currentLevelIndex++;
    LoadLevel(levelFiles[currentLevelIndex]);
}

const std::vector<std::vector<int>>& LevelManager::getMap() const {
    return map;
}

bool LevelManager::IsLastLevel() const {
    return currentLevelIndex >= levelFiles.size() - 1;
}

void LevelManager::ReloadLevel() {
    if (!levelFiles.empty()) {
        LoadLevel(levelFiles[currentLevelIndex]);
    }
    else {
        std::cerr << "Error: No levels available to reload!" << std::endl;
    }
}