#include "enemy.hpp"
#include <cstdlib>  // For random movement
#include <cmath>    // For distance calculations

Enemy::Enemy(int startX, int startY) {
    x = startX;
    y = startY;
    speed = 24;
    width = TILE_SIZE;
    height = TILE_SIZE;
    alive = true;
    direction = rand() % 4; // Random initial direction
    moveTimer = 300; // Change direction every 150 frames
    bombCooldown = 0;
}

void Enemy::Update(TileManager& map, Player& player, std::vector<Bomb>& bombs, SDL_Renderer* renderer) {
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
        moveTimer = 300;
    }

    // Handle bomb placement
    if (bombCooldown > 0) {
        bombCooldown--;  // Reduce cooldown timer
    }
    else if (rand() % 100 < 2) {  // 2% chance to place bomb each frame
        PlaceBomb(bombs, renderer);
        bombCooldown = 300;  // Reset cooldown (e.g., 5 seconds)
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

void Enemy::PlaceBomb(std::vector<Bomb>& bombs, SDL_Renderer* renderer) {
    int bombX = (x / TILE_SIZE) * TILE_SIZE;
    int bombY = (y / TILE_SIZE) * TILE_SIZE;

    // Ensure no bomb already exists at this location
    for (const auto& bomb : bombs) {
        if (bomb.GetRect().x == bombX && bomb.GetRect().y == bombY) {
            return; // Don't place bomb if one already exists
        }
    }

    // Place a new bomb
    bombs.push_back(Bomb(bombX, bombY));
}

void Enemy::Render(SDL_Renderer* renderer) {
    if (!alive) return;

    SDL_Rect rect = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Enemy::Kill() {
    alive = false;
}

SDL_Rect Enemy::GetRect() const {
    return { x, y, width, height };
}
