#include "enemy.hpp"
#include <cstdlib>  // For random movement
#include <cmath>    // For distance calculations

Enemy::Enemy(int startX, int startY, SDL_Renderer* renderer) : renderer(renderer) {
    textureManager = new TextureManager(renderer);
    x = startX;
    y = startY;
    speed = TILE_SIZE / 12;
    width = TILE_SIZE;
    height = TILE_SIZE;
    alive = true;
    direction = static_cast<Direction>(rand() % 4); // Random initial direction
    enemy1 = textureManager->LoadTexture(ENEMY_1_SPRITESHEET);
    enemy2 = textureManager->LoadTexture(ENEMY_2_SPRITESHEET);
    enemy3 = textureManager->LoadTexture(ENEMY_3_SPRITESHEET);
    moveTimer = 120; // Change direction every 120 frames
    bombCooldown = 0;
    lastRetryTime = 0;

    srcRect = { x, y, width, height };
    destRect = { x, y, width, height };
    frame = 0;
    frameTime = 120; // 120 ms delay
    lastFrameTime = 0;
    state = State::IDLE;
    direction = Direction::FRONT;
}

void Enemy::Update(TileManager& map, std::vector<Bomb>& bombs, SDL_Renderer* renderer) {
    if (!alive) return;

    // Always check if in a bomb's explosion radius
    if (IsInBombRadius(x, y, bombs)) {
        EscapeFromBomb(map, bombs);
    }

    int newX = x, newY = y;
    bool moved = false;
    switch (direction) {
    case Direction::BACK: newY -= speed; break; // UP
    case Direction::FRONT: newY += speed; break; // DOWN
    case Direction::LEFT: newX -= speed; break; // LEFT
    case Direction::RIGHT: newX += speed; break; // RIGHT
    }

    SDL_Rect newRect = { newX, newY, width, height };
    if (!map.CheckCollision(newRect)) {
        x = newX;
        y = newY;
        moved = true;
    }
    else {
        // If movement fails, retry after 1000ms
        if (SDL_GetTicks() - lastRetryTime > 1000) {
            direction = static_cast<Direction>(rand() % 4);
            lastRetryTime = SDL_GetTicks();
        }
    }

    moved ? state = State::WALKING : state = State::IDLE;

    if (--moveTimer <= 0) {
        moveTimer = 120;
    }

    // Handle bomb placement
    if (bombCooldown > 0) {
        bombCooldown--;
    }
    else if (rand() % 100 < 10) {
        PlaceBomb(bombs, renderer, map);
        bombCooldown = 300;
    }
}

void Enemy::ChooseDirection(TileManager& map, std::vector<Bomb>& bombs) {
    if (IsInBombRadius(x, y, bombs)) {
        EscapeFromBomb(map, bombs);
        return;
    }

    // Move randomly but ensure moving at least 2 tiles in one direction
    static int moveCounter = 0;
    if (moveCounter < 2) {
        moveCounter++;
    }
    else {
        direction = static_cast<Direction>(rand() % 4);
        moveCounter = 0;
    }
}

void Enemy::PlaceBomb(std::vector<Bomb>& bombs, SDL_Renderer* renderer, TileManager& map) {
    int bombX = (x / TILE_SIZE) * TILE_SIZE;
    int bombY = (y / TILE_SIZE) * TILE_SIZE;

    // Ensure no bomb already exists at this location
    for (const auto& bomb : bombs) {
        if (bomb.GetRect().x == bombX && bomb.GetRect().y == bombY) {
            return; // Don't place bomb if one already exists
        }
    }

    bool nearBreakable = false;
    bool onFloorTile = (map.GetTileTypeAt(bombX, bombY) == TileManager::TileType::GRASS || map.GetTileTypeAt(bombX, bombY) == TileManager::TileType::SNOW);

    // Check adjacent tiles for breakable walls
    for (int i = 0; i < 4; i++) {
        int checkX = bombX / TILE_SIZE;
        int checkY = bombX / TILE_SIZE;

        switch (i) {
            case 0: checkY -= 1; break; // UP
            case 1: checkY += 1; break; // DOWN
            case 2: checkX -= 1; break; // LEFT
            case 3: checkX += 1; break; // RIGHT
        }

        TileManager::TileType tileType = map.GetTileTypeAt(checkX * TILE_SIZE, checkY * TILE_SIZE);

        if (tileType == TileManager::TileType::BREAKABLE) {
            nearBreakable = true;
            break;
        }
    }

    if ((nearBreakable && (rand() % 100 < 60)) || (onFloorTile && (rand() % 100 < 30))) {
        bombs.push_back(Bomb(bombX, bombY, renderer, map, Bomb::Entity::ENEMY));
    }
}

void Enemy::Render(SDL_Renderer* renderer) {
    if (!alive) return;
    UpdateAnimation();
    SDL_Rect destRect = { x, y, TILE_SIZE, TILE_SIZE };
    SDL_RenderCopy(renderer, enemy1, &srcRect, &destRect);
}

void Enemy::Kill() {
    alive = false;
}

SDL_Rect Enemy::GetRect() const {
    return { x, y, width, height };
}

bool Enemy::IsInBombRadius(int x, int y, std::vector<Bomb>& bombs) {
    for (const auto& bomb : bombs) {
        int bombX = bomb.GetRect().x / TILE_SIZE;
        int bombY = bomb.GetRect().y / TILE_SIZE;
        int radius = bomb.GetExplosionRadius();

        int enemyX = x / TILE_SIZE;
        int enemyY = y / TILE_SIZE;

        // Bomb explodes in 4 directions
        if (enemyX == bombX && abs(enemyY - bombY) <= radius) {
            return true; // In vertical explosion path
        }
        if (enemyY == bombY && abs(enemyX - bombX) <= radius) {
            return true; // In horizontal explosion path
        }
    }
    return false;
}

void Enemy::EscapeFromBomb(TileManager& map, std::vector<Bomb>& bombs) {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastRetryTime < 400) {
        return; // Try to escapse
    }
    lastRetryTime = currentTime;

    std::vector<int> safeDirections;

    for (int i = 0; i < 4; i++) {
        int newX = x, newY = y;
        switch (i) {
        case 0: newY -= TILE_SIZE; break; // UP
        case 1: newY += TILE_SIZE; break; // DOWN
        case 2: newX -= TILE_SIZE; break; // LEFT
        case 3: newX += TILE_SIZE; break; // RIGHT
        }

        SDL_Rect newRect = { newX, newY, width, height };
        if (!map.CheckCollision(newRect) && !IsInBombRadius(newX, newY, bombs)) {
            safeDirections.push_back(i); // Store safe movement options
        }
    }

    if (!safeDirections.empty()) {
        direction = static_cast<Direction>(safeDirections[rand() % safeDirections.size()]); // Pick a random safe direction
    }
    else {
        // If trapped, keep retrying
        direction = static_cast<Direction>(rand() % 4);
    }
}

void Enemy::UpdateAnimation() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastFrameTime >= frameTime) {
        frame = (frame + 1) % 4;
        lastFrameTime = currentTime;
    }

    int row = 0;
    int startCol = 0;

    if (direction == Direction::FRONT) startCol = 0;
    if (direction == Direction::RIGHT) startCol = 8;
    if (direction == Direction::BACK) startCol = 16;
    if (direction == Direction::LEFT) startCol = 24;

    if (state == State::IDLE) row = 0;
    if (state == State::WALKING) row = 1;

    srcRect = { (startCol + frame) * SPRITE_TILE, row * SPRITE_TILE, SPRITE_TILE, SPRITE_TILE };
}