#include "bomb.hpp"

// initialize static variable
std::vector<SDL_Texture*> Bomb::sharedBombTextures;
int Bomb::nextExplosionId = 0;

Bomb::Bomb(int px, int py, SDL_Renderer* renderer, TileManager& map, const Entity& owner) : ownerType(owner) {
    textureManager = new TextureManager(renderer);
    x = (px / TILE_SIZE) * TILE_SIZE; // Align to grid
    y = (py / TILE_SIZE) * TILE_SIZE;
    timer = 3000; // 3 seconds before explosion
    frameDelay = 90; // For bomb animation
    startTime = SDL_GetTicks();
    lastFrameTime = SDL_GetTicks();
    active = true;
    currentFrame = 0;
    explosionRadius = 1;
    LoadTexture(renderer);

    playerOnBomb = true; // Player starts on the bomb
    enemyOnBomb = true;  // Any enemy starts on the bomb

    // For score calculation
    explosionId = nextExplosionId++;
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
        player.SetCanPlaceBomb();
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
    for (int i = 1; i <= explosionRadius; i++) {
        std::vector<std::pair<int, int>> explosionTiles = {
            {gridX + i, gridY}, // Right
            {gridX - i, gridY}, // Left
            {gridX, gridY + i}, // Down
            {gridX, gridY - i}  // Up
        };

        for (auto& tile : explosionTiles) {
            int ex = tile.first * TILE_SIZE;
            int ey = tile.second * TILE_SIZE;

            if (!map.IsWall(tile.first, tile.second)) {
                // Store for later destruction
                tilesToDestroy.push_back(tile);

                // Add explosion effect
                explosions.push_back(Explosion(ex, ey, renderer, explosionId));
                explosionRect = { ex, ey, TILE_SIZE, TILE_SIZE };

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
    }

    // **Delay destruction and kill enemy until update happens**
    enemyKilled = enemiesToKill;
    pendingDestroyedTiles = tilesToDestroy;
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
