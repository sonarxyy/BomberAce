#include "tile_manager.hpp"

TileManager::TileManager(SDL_Renderer* renderer) : renderer(renderer) {
    textureManager = new TextureManager(renderer);
    isRendered = false;
    /*
    * Map Layout
    * 0: Moveable
    * 1: Unbreakable
    * 2: Breakable
    */
    int level[MAP_ROWS][MAP_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 2, 0, 0, 2, 0, 0, 0, 2, 0, 2, 2, 0, 0, 2, 0, 0, 0, 1},
    {1, 0, 1, 0, 2, 1, 0, 2, 0, 0, 2, 0, 1, 0, 2, 1, 0, 2, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 2, 0, 0, 2, 0, 0, 1, 0, 0, 1, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 1, 2, 0, 2, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 2, 0, 0, 2, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 2, 0, 0, 0, 2, 0, 2, 2, 0, 0, 2, 0, 0, 0, 2, 0, 1},
    {1, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 1},
    {1, 1, 0, 2, 1, 2, 0, 1, 0, 2, 2, 0, 1, 0, 0, 0, 0, 2, 1, 1},
    {1, 0, 0, 2, 0, 0, 0, 2, 2, 0, 2, 0, 0, 2, 0, 0, 0, 2, 0, 1},
    {1, 0, 2, 0, 0, 2, 0, 0, 0, 2, 0, 2, 2, 0, 0, 2, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 2, 0, 1, 1, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 1, 2, 2, 0, 1, 0, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1, 0, 0, 1, 0, 2, 0, 2, 0, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 1, 0, 2, 1, 0, 2, 0, 0, 2, 0, 1, 0, 2, 1, 0, 2, 0, 1},
    {1, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 1},
    {1, 2, 0, 0, 2, 0, 2, 0, 2, 2, 2, 1, 0, 2, 0, 1, 2, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
    LoadTexture();
    for (int row = 0; row < MAP_ROWS; row++) {
        for (int col = 0; col < MAP_COLS; col++) {
            map[row][col] = level[row][col];

            // Store a consistent floor texture index for this tile
            floorTextureIndex[row][col] = rand() % floorTextures.size();

            // If breakable, store its texture choice
            if (map[row][col] == 2) {
                breakableTextureIndex[row][col] = rand() % breakableTextures.size();
            }
        }
    }
}

void TileManager::LoadTexture() {
    floorTextures.push_back(textureManager->LoadTexture("assets/image/floor1.png"));
    // floorTextures.push_back(textureManager->LoadTexture("assets/image/floor2.png"));
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
}


bool TileManager::CheckCollision(SDL_Rect& playerRect) const {
    for (int row = 0; row < MAP_ROWS; row++) {
        for (int col = 0; col < MAP_COLS; col++) {
            if (map[row][col] == 1 || map[row][col] == 2) {
                SDL_Rect tileRect = { col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                if (SDL_HasIntersection(&playerRect, &tileRect)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool TileManager::isWall(int col, int row) const {
    if (col < 0 || col >= MAP_COLS || row < 0 || row >= MAP_ROWS) { // Treat out-of-bounds as walls
        return true;
    }
    return map[row][col] == 1;
}

bool TileManager::DestroyTile(int col, int row) {
    if (col < 0 || col >= MAP_COLS || row < 0 || row >= MAP_ROWS) return true;

    if (map[row][col] == 2) {
        map[row][col] = 0; // Remove the destructible tile
        return false; // Continue explosion
    }

    return (map[row][col] == 1); // Stop explosion at walls
}

bool TileManager::getRenderState() const {
    return isRendered;
}

