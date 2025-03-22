#ifndef TILE_MANAGER_HPP
#define TILE_MANAGER_HPP

#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <vector>
#include <string>
#include "constants.hpp"
#include "texture_manager.hpp"
#include "bomb.hpp"

class Bomb;

class TileManager {
public:
    TileManager(SDL_Renderer* renderer);
    void LoadTexture();
    void Render(SDL_Renderer* renderer);
    bool CheckCollision(SDL_Rect& playerRect) const;
    bool IsWall(int col, int row) const;
    bool DestroyTile(int col, int row);
    bool GetRenderState() const;

    // For sound effect
    enum class TileType {
        GRASS,
        SNOW,
        WALL,
        BREAKABLE,
        FLOOR
    };
    TileType GetTileTypeAt(int x, int y);

private:
    bool isRendered;
    int map[MAP_ROWS][MAP_COLS];
    int floorTextureIndex[MAP_ROWS][MAP_COLS];
    int breakableTextureIndex[MAP_ROWS][MAP_COLS];
    SDL_Renderer* renderer;
    TextureManager* textureManager;
    std::vector<SDL_Texture*> floorTextures;
    std::vector<SDL_Texture*> breakableTextures;
    std::vector<SDL_Texture*> unbreakableTextures;
};
#endif
