#ifndef TILE_MANAGER_HPP
#define TILE_MANAGER_HPP

#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <vector>
#include <string>
#include <algorithm>
#include "constants.hpp"
#include "texture_manager.hpp"
#include "bomb.hpp"
#include "power_up.hpp"
#include "level_manager.hpp"

class Bomb;

class TileManager {
public:
    TileManager(SDL_Renderer* renderer, const LevelManager& levelManager);
    void LoadLevel(const LevelManager& levelManager);
    void LoadTexture();
    void Render(SDL_Renderer* renderer);
    bool CheckCollision(SDL_Rect& playerRect) const;
    bool IsWall(int col, int row) const;
    bool DestroyTile(int col, int row);
    std::vector<PowerUp> GetPowerUps();

    // For sound effect
    enum class TileType {
        FLOOR,
        WALL,
        BREAKABLE,
        GRASS,
        SNOW,
        BOMB,
        POWER_UP = 9,
        BOMB_RANGE,
        SPEED,
        SHIELD,
        EXTRA_BOMBS
    };
    TileType GetTileTypeAt(int x, int y);
    void SetTile(int x, int y, TileType);
    void RemovePowerUpAt(int x, int y);

private:
    bool isRendered;
    std::vector<std::vector<int>> map;
    std::vector<std::vector<int>> floorTextureIndex;
    std::vector<std::vector<int>> breakableTextureIndex;
    SDL_Renderer* renderer;
    TextureManager* textureManager;
    std::vector<SDL_Texture*> floorTextures;
    std::vector<SDL_Texture*> breakableTextures;
    std::vector<SDL_Texture*> unbreakableTextures;
    std::vector<PowerUp> powerUps;
    std::map<std::pair<int, int>, PowerUpType> hiddenPowerUps;
};
#endif
