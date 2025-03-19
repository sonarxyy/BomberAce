#include "enemy.hpp"
#include <cstdlib>  // For random movement
#include <cmath>    // For distance calculations

Enemy::Enemy(int startX, int startY) {
    x = startX;
    y = startY;
    speed = 2;
    width = 32;
    height = 32;
    alive = true;
    direction = rand() % 4; // Random initial direction
    moveTimer = 60; // Change direction every 60 frames
}

void Enemy::Update(TileManager& map, Player& player, std::vector<Bomb>& bombs) {
    if (!alive) return;

    ChooseDirection(map, player, bombs);

    int newX = x, newY = y;
    switch (direction) {
    case 0: newY -= speed; break; // UP
    case 1: newY += speed; break; // DOWN
    case 2: newX -= speed; break; // LEFT
    case 3: newX += speed; break; // RIGHT
    }

    SDL_Rect newRect = { newX, newY, width, height };
    if (!map.CheckCollision(newRect)) {
        x = newX;
        y = newY;
    }

    if (--moveTimer <= 0) {
        moveTimer = 60;
    }
}

void Enemy::ChooseDirection(TileManager& map, Player& player, std::vector<Bomb>& bombs) {
    // Avoid bombs
    for (const auto& bomb : bombs) {
        SDL_Rect bombRect = { bomb.GetRect().x, bomb.GetRect().y, TILE_SIZE, TILE_SIZE};
        SDL_Rect enemyRect = GetRect();

        if (SDL_HasIntersection(&bombRect, &enemyRect)) {
            direction = rand() % 4; // Pick a random direction to escape
            return;
        }
    }

    // Chase player if in range
    int playerX = player.GetRect().x;
    int playerY = player.GetRect().y;

    int distX = abs(playerX - x);
    int distY = abs(playerY - y);

    if (distX <= 128 && distY <= 128) {  // Chase if within range
        if (distX > distY) {
            direction = (playerX > x) ? 3 : 2; // Move right or left
        }
        else {
            direction = (playerY > y) ? 1 : 0; // Move down or up
        }
    }
    else {
        direction = rand() % 4; // Random movement if player is not close
    }
}

void Enemy::Render(SDL_Renderer* renderer) {
    if (!alive) return;

    SDL_Rect rect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Enemy::Kill() {
    alive = false;
}

SDL_Rect Enemy::GetRect() const {
    return { x, y, width, height };
}
