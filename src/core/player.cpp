#include "player.hpp"
#include <iostream>

Player::Player() {
    x = 48;
    y = 48;
    speed = 48;
    width = 48;
    height = 48;
}

void Player::HandleInput(SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_UP:    y -= speed; break;
        case SDLK_DOWN:  y += speed; break;
        case SDLK_LEFT:  x -= speed; break;
        case SDLK_RIGHT: x += speed; break;
        }
    }

    SDL_Rect newRect = { x, y, width, height };

    // Check collision with the tile map
    /*if (!map.CheckCollision(newRect)) {
        x = newX;
        y = newY;
    }*/
}

void Player::Render(SDL_Renderer* renderer) {
    SDL_Rect rect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect Player::GetRect() const {
    return { x, y };
}
