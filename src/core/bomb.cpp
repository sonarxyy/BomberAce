#include "bomb.hpp"

// initialize static variable
std::vector<SDL_Texture*> Bomb::sharedBombTextures;
int Bomb::nextExplosionId = 0;

Bomb::Bomb(int px, int py, SDL_Renderer* renderer, TileManager& map, Entity owner, int ownerExplosionRadius)
    : ownerType(owner), explosionRadius(ownerExplosionRadius) {
    textureManager = new TextureManager(renderer);
    x = (px / TILE_SIZE) * TILE_SIZE;
    y = (py / TILE_SIZE) * TILE_SIZE;
    timer = 3000;
    frameDelay = 90;
    startTime = SDL_GetTicks();
    lastFrameTime = SDL_GetTicks();
    active = true;
    currentFrame = 0;

    LoadTexture(renderer);
}

void Bomb::LoadTexture(SDL_Renderer* renderer) {
    if (!sharedBombTextures.empty()) {
        bombTextures = sharedBombTextures;
        return;
    }
    else {
        for (int i = 0; i < BOMB_FRAME; i++) {
            std::string path = "assets/animations/bomb/bomb" + std::to_string(i) + ".png";
            sharedBombTextures.push_back(textureManager->LoadTexture(path.c_str()));
        }
    }
    bombTextures = sharedBombTextures;
}

void Bomb::Update(TileManager& map, Player& player, std::vector<Enemy>& enemies, std::vector<Explosion>& explosions, SDL_Renderer* renderer) {
    if (!active) return;

    Uint32 currentTime = SDL_GetTicks();

    // Check if the player left the bomb tile
    int gridX = x / TILE_SIZE;
    int gridY = y / TILE_SIZE;
    SDL_Rect bombRect = { x, y, TILE_SIZE, TILE_SIZE };

    if (!CheckCollision(bombRect, player.GetRect())) {
        playerOnBomb = false;
    }

    // Check if any enemy left the bomb tile
    bool anyEnemyOnBomb = false;
    for (auto& enemy : enemies) {
        if (CheckCollision(bombRect, enemy.GetRect())) {
            anyEnemyOnBomb = true;
        }
    }
    enemyOnBomb = anyEnemyOnBomb;

    // If both the player and enemies have left
    if (!playerOnBomb && !enemyOnBomb) {
        map.SetTile(x / TILE_SIZE, y / TILE_SIZE, TileManager::TileType::BOMB);
    }

    if (currentTime - lastFrameTime >= frameDelay) {
        currentFrame = (currentFrame + 1) % BOMB_FRAME;
        lastFrameTime = currentTime;
    }

    if (currentTime - startTime >= timer) {
        active = false;
    }

    // Reset the bomb tile to be walkable
    if (!active) {
        Explode(map, player, enemies, explosions, renderer);
        map.SetTile(gridX, gridY, TileManager::TileType::FLOOR);
    }
}

void Bomb::Explode(TileManager& map, Player& player, std::vector<Enemy>& enemies, std::vector<Explosion>& explosions, SDL_Renderer* renderer) {
    int gridX = x / TILE_SIZE;
    int gridY = y / TILE_SIZE;

    // Track if the player has already been hit
    bool playerHit = false;

    // Create explosion center
    explosions.push_back(Explosion(x, y, renderer, explosionId));
    SDL_Rect explosionRect = { x, y, TILE_SIZE, TILE_SIZE };

    if (CheckCollision(explosionRect, player.GetRect()) && !playerHit) {
        player.TakeDamage();
        playerHit = true;
    }

    // Store tiles that need to be destroyed AFTER update
    std::vector<std::pair<int, int>> tilesToDestroy;
    std::vector<Enemy*> enemiesToKill;

    for (Enemy& enemy : enemies) {
        if (std::find(enemiesToKill.begin(), enemiesToKill.end(), &enemy) == enemiesToKill.end() && CheckCollision(explosionRect, enemy.GetRect())) {
            enemiesToKill.push_back(&enemy);
        }
    }

    // Create explosions in 4 directions
    bool stopRight = false, stopLeft = false, stopDown = false, stopUp = false;

    for (int i = 1; i <= explosionRadius; i++) {
        std::vector<std::pair<int, int>> explosionTiles = {
            {gridX + i, gridY}, // Right
            {gridX - i, gridY}, // Left
            {gridX, gridY + i}, // Down
            {gridX, gridY - i}  // Up
        };

        for (int dir = 0; dir < 4; dir++) {
            int ex = explosionTiles[dir].first * TILE_SIZE;
            int ey = explosionTiles[dir].second * TILE_SIZE;

            // Stop explosion if a wall is encountered
            if (dir == 0 && stopRight) continue;
            if (dir == 1 && stopLeft) continue;
            if (dir == 2 && stopDown) continue;
            if (dir == 3 && stopUp) continue;

            if (map.IsWall(explosionTiles[dir].first, explosionTiles[dir].second)) {
                if (dir == 0) stopRight = true;
                if (dir == 1) stopLeft = true;
                if (dir == 2) stopDown = true;
                if (dir == 3) stopUp = true;
                continue; // Do NOT create an explosion here
            }

            // Store for later destruction
            tilesToDestroy.push_back(explosionTiles[dir]);

            // Add explosion effect
            explosions.push_back(Explosion(ex, ey, renderer, explosionId));
            SDL_Rect explosionRect = { ex, ey, TILE_SIZE, TILE_SIZE };

            if (CheckCollision(explosionRect, player.GetRect()) && !playerHit) {
                player.TakeDamage();
                playerHit = true;
            }

            for (Enemy& enemy : enemies) {
                if (std::find(enemiesToKill.begin(), enemiesToKill.end(), &enemy) == enemiesToKill.end() && CheckCollision(explosionRect, enemy.GetRect())) {
                    enemiesToKill.push_back(&enemy);
                }
            }
        }
    }


    // Delay destruction and kill enemy until update happens
    enemyKilled = enemiesToKill;
    pendingDestroyedTiles = tilesToDestroy;

    player.OnBombExploded();
}


void Bomb::Render(SDL_Renderer* renderer) {
    if (!active) return;

    SDL_Rect rect = { x - TILE_SIZE / 8, y - TILE_SIZE / 4, 64, 64 };
    
    SDL_RenderCopy(renderer, bombTextures[currentFrame], NULL, &rect);
}

SDL_Rect Bomb::GetRect() const {
    return { x, y };
}

bool Bomb::CheckCollision(SDL_Rect explosionArea, SDL_Rect object) {
    return SDL_HasIntersection(&explosionArea, &object);
}

int Bomb::GetExplosionRadius() const {
    return explosionRadius;
}

int Bomb::GetExplosionId() const {
    return explosionId;
}

Bomb::Entity Bomb::GetOwnerType() const {
    return ownerType;
}
