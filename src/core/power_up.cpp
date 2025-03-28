#include "power_up.hpp"

PowerUp::PowerUp(int x, int y, PowerUpType type, SDL_Renderer* renderer) : renderer(renderer) {
    this->x = x;
    this->y = y;
    this->type = type;
    rect = { x, y, POWER_UP_WIDTH, POWER_UP_HEIGHT };
    textureManager = new TextureManager(renderer);

    bombRangeTexture = textureManager->LoadTexture(BOMB_RANGE_FILE);
    speedTexture = textureManager->LoadTexture(SPEED_FILE);
    shieldTexture = textureManager->LoadTexture(SHIELD_FILE);
    extraBombTexture = textureManager->LoadTexture(EXTRA_BOMB_FILE);
}

void PowerUp::Render(SDL_Renderer* renderer) {
    SDL_Rect destRect = { x + 6, y + 6, TILE_SIZE * 3 / 4, TILE_SIZE * 3 / 4};
    switch (type) {
    case BOMB_RANGE: SDL_RenderCopy(renderer, bombRangeTexture, NULL, &destRect); break;
    case SPEED: SDL_RenderCopy(renderer, speedTexture, NULL, &destRect); break;
    case SHIELD: SDL_RenderCopy(renderer, shieldTexture, NULL, &destRect); break;
    case EXTRA_BOMBS: SDL_RenderCopy(renderer, extraBombTexture, NULL, &destRect); break;
    }
}

SDL_Rect PowerUp::GetRect() const {
    return rect;
}

PowerUpType PowerUp::GetType() const {
    return type;
}
