#include "power_up.hpp"

PowerUp::PowerUp(int x, int y, PowerUpType type) {
    this->x = x;
    this->y = y;
    this->type = type;
    rect = { x, y, TILE_SIZE, TILE_SIZE };
}

void PowerUp::Render(SDL_Renderer* renderer) {
    switch (type) {
    case BOMB_RANGE: SDL_SetRenderDrawColor(renderer, 255, 69, 0, 255); break; // Orange
    case SPEED: SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); break; // Green
    case SHIELD: SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); break; // Yellow
    case EXTRA_BOMBS: SDL_SetRenderDrawColor(renderer, 255, 20, 147, 255); break; // Pink
    }
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect PowerUp::GetRect() const {
    return rect;
}

PowerUpType PowerUp::GetType() const {
    return type;
}
