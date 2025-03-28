#include "tile_manager.hpp"

TileManager::TileManager(SDL_Renderer* renderer, const LevelManager& levelManager) : renderer(renderer) {
    textureManager = new TextureManager(renderer);
    isRendered = false;
    LoadTexture();
    LoadLevel(levelManager);
}

void TileManager::LoadLevel(const LevelManager& levelManager) {
    const auto& level = levelManager.getMap();

    map.clear();
    floorTextureIndex.clear();
    breakableTextureIndex.clear();
    powerUps.clear();
    hiddenPowerUps.clear(); // Store hidden power-ups separately

    int rows = MAP_ROWS;
    int cols = MAP_COLS;

    map.resize(rows, std::vector<int>(cols, static_cast<int>(TileType::FLOOR)));
    floorTextureIndex.resize(rows, std::vector<int>(cols, 0));
    breakableTextureIndex.resize(rows, std::vector<int>(cols, 0));

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            map[row][col] = level[row][col];

            // Assign new textures for the new level
            floorTextureIndex[row][col] = rand() % floorTextures.size();

            if (map[row][col] == static_cast<int>(TileType::BREAKABLE)) {
                breakableTextureIndex[row][col] = rand() % breakableTextures.size();
            }

            if (map[row][col] == static_cast<int>(TileType::POWER_UP)) {
                // Instead of directly placing a power-up, hide it inside a breakable tile
                map[row][col] = static_cast<int>(TileType::BREAKABLE);
                PowerUpType type = static_cast<PowerUpType>(10 + rand() % 4);
                hiddenPowerUps[{col, row}] = type; // Store it for later reveal
            }
        }
    }
}

void TileManager::LoadTexture() {
    floorTextures.push_back(textureManager->LoadTexture("assets/image/floor1.png"));
    floorTextures.push_back(textureManager->LoadTexture("assets/image/floor2.png"));
    floorTextures.push_back(textureManager->LoadTexture("assets/image/floor3.png"));

    unbreakableTextures.push_back(textureManager->LoadTexture("assets/image/unbreakableObject.png"));

    breakableTextures.push_back(textureManager->LoadTexture("assets/image/breakableObject1.png"));
    breakableTextures.push_back(textureManager->LoadTexture("assets/image/breakableObject2.png"));
    breakableTextures.push_back(textureManager->LoadTexture("assets/image/breakableObject3.png"));
    breakableTextures.push_back(textureManager->LoadTexture("assets/image/breakableObject4.png"));
}

void TileManager::Render(SDL_Renderer* renderer) {
    for (int row = 0; row < MAP_ROWS; row++) {
        for (int col = 0; col < MAP_COLS; col++) {
            SDL_Rect tile = { col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE };

            // Render floor with precomputed texture
            SDL_RenderCopy(renderer, floorTextures[floorTextureIndex[row][col]], NULL, &tile);

            if (map[row][col] == 1) {
                SDL_RenderCopy(renderer, unbreakableTextures[0], NULL, &tile);
            }
            else if (map[row][col] == 2) {
                SDL_RenderCopy(renderer, breakableTextures[breakableTextureIndex[row][col]], NULL, &tile);
            }
        }
    }
    // Render power-ups
    for (auto& powerUp : powerUps) {
        powerUp.Render(renderer);
    }
}


bool TileManager::CheckCollision(SDL_Rect& objectRect) const {
    for (int row = 0; row < MAP_ROWS; row++) {
        for (int col = 0; col < MAP_COLS; col++) {
            if (map[row][col] == 1 || map[row][col] == 2 || map[row][col] == 5) {
                SDL_Rect tileRect = { col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                if (SDL_HasIntersection(&objectRect, &tileRect)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool TileManager::IsWall(int col, int row) const {
    if (col < 0 || col >= MAP_COLS || row < 0 || row >= MAP_ROWS) { // Treat out-of-bounds as walls
        return true;
    }
    return map[row][col] == 1;
}

bool TileManager::DestroyTile(int col, int row) {
    if (col < 0 || col >= MAP_COLS || row < 0 || row >= MAP_ROWS) return true;

    if (map[row][col] == 2) { // Breakable tile
        map[row][col] = 0; // Remove the destructible tile

        // Check if a power-up was hidden inside
        auto it = hiddenPowerUps.find({ col, row });
        if (it != hiddenPowerUps.end()) {
            PowerUpType type = it->second;
            powerUps.emplace_back(col * TILE_SIZE, row * TILE_SIZE, type, renderer);
            hiddenPowerUps.erase(it); // Remove from hidden list
            map[row][col] = static_cast<int>(TileType::POWER_UP); // Update tile type
        }

        return false; // Continue explosion
    }

    return (map[row][col] == 1); // Stop explosion at walls
}

TileManager::TileType TileManager::GetTileTypeAt(int x, int y) {
    int tileX = x / TILE_SIZE;
    int tileY = y / TILE_SIZE;

    if (tileX < 0 || tileX >= MAP_COLS || tileY < 0 || tileY >= MAP_ROWS) {
        return TileType::WALL; // Treat out-of-bounds as walls
    }

    if (map[tileY][tileX] == 1) {
        return TileType::WALL; // Unbreakable wall
    }

    if (map[tileY][tileX] == 2) {
        return TileType::BREAKABLE; // Breakable wall
    }

    if (map[tileY][tileX] == 9) {
        return TileType::POWER_UP;
    }

    // Use floorTextureIndex to determine GRASS or SNOW
    switch (floorTextureIndex[tileY][tileX]) {
    case 0: return TileType::GRASS;
    case 1: return TileType::SNOW;
    default: return TileType::GRASS;
    }
}

void TileManager::SetTile(int col, int row, TileType type) {
    if (col < 0 || col >= MAP_COLS || row < 0 || row >= MAP_ROWS) return;
    map[row][col] = static_cast<int>(type);
}

void TileManager::RemovePowerUpAt(int x, int y) {
    SDL_Rect temp = { x / TILE_SIZE * TILE_SIZE, y / TILE_SIZE * TILE_SIZE, TILE_SIZE, TILE_SIZE };
    auto it = std::remove_if(powerUps.begin(), powerUps.end(), [&](const PowerUp& p) {
        SDL_Rect temp2 = p.GetRect();
        return SDL_HasIntersection(&temp2, &temp);
    });

    if (it != powerUps.end()) {
        powerUps.erase(it, powerUps.end());
    }
}

std::vector<PowerUp> TileManager::GetPowerUps() {
    return powerUps;
}



