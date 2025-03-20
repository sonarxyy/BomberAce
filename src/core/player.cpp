#include "player.hpp"

Player::Player() {
    x = 48;
    y = 48;
    speed = 48;
    width = TILE_SIZE;
    height = TILE_SIZE;
    health = 3;
}

void Player::TakeDamage() {
    if (health > 0) {
        health--;
    }

    if (health == 0) {
        // Game over: handling
    }
}

void Player::HandleInput(SDL_Event& event, TileManager& map, std::vector<Bomb>& bombs) {
    int newX = x;
    int newY = y;

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_UP:
        case SDLK_w:
            newY -= speed; 
            break;
        case SDLK_DOWN:
        case SDLK_s:
            newY += speed; 
            break;
        case SDLK_LEFT:  
        case SDLK_a:
            newX -= speed;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            newX += speed; 
            break;
        case SDLK_SPACE:
            bombs.push_back(Bomb(x, y));
            break;
        }
    }

    SDL_Rect newRect = { newX, newY, width, height };

    // Check collision with the tile map
    if (!map.CheckCollision(newRect)) {
        x = newX;
        y = newY;
    }
}

void Player::Render(SDL_Renderer* renderer) {
    SDL_Rect rect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

SDL_Rect Player::GetRect() const {
    return { x, y , width, height};
}

int Player::GetHealth() const {
    return health;
}

void Player::SetPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Player::PlaceBomb(std::vector<Bomb>& bombs) {
    int bombX = (x / TILE_SIZE) * TILE_SIZE;
    int bombY = (y / TILE_SIZE) * TILE_SIZE;

    // Ensure no bomb exists at this location
    for (const auto& bomb : bombs) {
        if (bomb.GetRect().x == bombX && bomb.GetRect().y == bombY) {
            return; // Don't place bomb if one already exists
        }
    }

    // Place a new bomb only if there's no existing one
    bombs.push_back(Bomb(bombX, bombY));
}
