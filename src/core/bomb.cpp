#include "bomb.hpp"


Bomb::Bomb(int px, int py) {
    x = (px / TILE_SIZE) * TILE_SIZE; // Align to grid
    y = (py / TILE_SIZE) * TILE_SIZE;
    timer = 3000; // 3 seconds before explosion
    startTime = SDL_GetTicks();
    active = true;
}

void Bomb::Update(TileManager& map) {
    if (!active) return;

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - startTime >= timer) {
        active = false;
        Explode(map);
    }
}

void Bomb::Explode(TileManager& map) {
    // Convert position to grid coordinates
    int gridX = x / TILE_SIZE;
    int gridY = y / TILE_SIZE;

    // Destroy obstacles in explosion range (cross pattern)
    int explosionRange = 2; // Default explosion radius

    for (int i = -explosionRange; i <= explosionRange; i++) {
        // Horizontal explosion
        if (map.DestroyTile(gridX + i, gridY)) break;
    }

    for (int i = -explosionRange; i <= explosionRange; i++) {
        // Vertical explosion
        if (map.DestroyTile(gridX, gridY + i)) break;
    }
}

void Bomb::Render(SDL_Renderer* renderer) {
    if (!active) return;

    SDL_Rect rect = { x, y, TILE_SIZE, TILE_SIZE };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect Bomb::GetRect() const {
    return { x, y };
}
